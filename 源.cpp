#include "workerManager.h"
#include <unordered_map>
#include <stack>
using namespace std;

// 红黑树存储员工信息及其查找
class fileSystem : public Worker
{
private:
    struct node
    {
        Worker* data;
        node* left;
        node* right;
        node* parent;
        int color;
        node() : data(NULL), left(NULL), right(NULL), parent(NULL), color(1) {};
        node(int id, string name, int deptid) : data(new Employee(id, name, deptid)), left(NULL), right(NULL), parent(NULL), color(1) {};
        node(int id, string name, int deptid, int color, node* parent, node* left, node* right) : data(new Employee(id, name, deptid)), left(left), right(right), parent(parent), color(color) {};
    };
    int size;
    node* root;

    fileSystem()
    {
        root = NULL;
        size = 0;
    }
    ~fileSystem()
    {
        delete root;
    }

    void init();
    void rightRotate(node* x);
    void leftRotate(node* x);
    void insertFixUp(node* x);
    void deleteFixUp(node* x);
    node* treeSuccessor(node* x);
    node* treeMinimum(node* x);

    void preOrder(node* x);
    void inOrder(node* x);
    void postOrder(node* x);

    node* search_name(node* x, string name);
    node* search_id(node* x, int id);

    void read();
    void write();

public:
    void insert(int id, string name, int deptid);
    void delete_by_id(int id);
    void delete_by_name(string name);
    void finder();
};

void fileSystem::read()
{
    ifstream in;
    in.open(FILENAME, ios::in);
    if (!in.is_open())
    {
        cout << "文件不存在" << endl;
        return;
    }
    int id;
    string name;
    int deptid;
    while (in >> id && in >> name && in >> deptid)
    {
        insert(id, name, deptid);
    }
    in.close();
}

void fileSystem::write()
{
    ofstream out;
    out.open(FILENAME, ios::out);
    if (!out.is_open())
    {
        cout << "文件不存在" << endl;
        return;
    }
    node* x = treeMinimum(root);
    while (x != NULL)
    {
        out << x->data->m_Id << " " << x->data->m_Name << " " << x->data->m_DeptId << endl;
        x = treeSuccessor(x);
    }
    out.close();
}

void fileSystem::init()
{
    read();
}

void fileSystem::rightRotate(node* x)
{
    node* y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fileSystem::leftRotate(node* x)
{
    node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void fileSystem::insertFixUp(node* x)
{
    while (x != root && x->parent->color == 1)
    {
        if (x->parent == x->parent->parent->left)
        {
            node* y = x->parent->parent->right;
            if (y != NULL && y->color == 1)
            {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->right)
                {
                    x = x->parent;
                    leftRotate(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            node* y = x->parent->parent->left;
            if (y != NULL && y->color == 1)
            {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            }
            else
            {
                if (x == x->parent->left)
                {
                    x = x->parent;
                    rightRotate(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                leftRotate(x->parent->parent);
            }
        }
    }
    root->color = 0;
}

void fileSystem::deleteFixUp(node* x)
{
    while (x != root && x->color == 0)
    {
        if (x == x->parent->left)
        {
            node* w = x->parent->right;
            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 1;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0)
            {
                w->color = 1;
                x = x->parent;
            }
            else
            {
                if (w->right->color == 0)
                {
                    w->left->color = 0;
                    w->color = 1;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            node* w = x->parent->left;
            if (w->color == 1)
            {
                w->color = 0;
                x->parent->color = 1;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0)
            {
                w->color = 1;
                x = x->parent;
            }
            else
            {
                if (w->left->color == 0)
                {
                    w->right->color = 0;
                    w->color = 1;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 0;
}

fileSystem::node* fileSystem::search_id(fileSystem::node* x, int id)
{
    if (x == nullptr || x->data->m_Id == id)
        return x;
    else if (id > x->data->m_Id)
        return search_id(x->right, id);
    else
        return search_id(x->left, id);
}

// 遍历红黑树将其插入哈希表查找
fileSystem::node* fileSystem::search_name(fileSystem::node* x, string name)
{
    unordered_map<string, fileSystem::node*> filter;
    stack<fileSystem::node*> cache;
    fileSystem::node* ans;
    if (nullptr == root)
        return nullptr;
    cache.emplace(root);
    while (!cache.empty())
    {
        fileSystem::node* node = cache.top();
        cache.pop();
        filter.emplace(node->data->m_Name, node);
        if (node->right)
            cache.emplace(node->right);
        if (node->left)
            cache.emplace(node->left);
    }

    ans = filter.find(name) == filter.end() ? nullptr : filter.find(name)->second;
    return ans;
}

void fileSystem::preOrder(node* x)
{
    if (x != NULL)
    {
        cout << x->data->m_Name << " ";
        preOrder(x->left);
        preOrder(x->right);
    }
}

void fileSystem::insert(int id, string name, int deptid)
{
    node* z = new node;
    z->data->m_Id = id;
    z->data->m_Name = name;
    z->data->m_DeptId = deptid;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = 1;
    node* y = NULL;
    node* x = root;
    while (x != NULL)
    {
        y = x;
        if (z->data->m_Id < x->data->m_Id)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        root = z;
    else if (z->data->m_Id < y->data->m_Id)
        y->left = z;
    else
        y->right = z;
    if (z->parent == NULL)
    {
        z->color = 0;
        return;
    }
    if (z->parent->parent == NULL)
        return;
    insertFixUp(z);
}

void fileSystem::delete_by_id(int id)
{
    node* z = search_id(root, id);
    if (z == NULL)
    {
        cout << "No such id" << endl;
        return;
    }
    node* x, * y;
    if (z->left == NULL || z->right == NULL)
        y = z;
    else
        y = treeSuccessor(z);
    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;
    if (x != NULL)
        x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    if (y != z)
        z->data = y->data;
    if (y->color == 0)
        deleteFixUp(x);
    delete y;
}

fileSystem::node* fileSystem::treeSuccessor(node* x)
{
    if (x->right != NULL)
        return treeMinimum(x->right);
    node* y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

fileSystem::node* fileSystem::treeMinimum(node* x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

void fileSystem::delete_by_name(string name)
{
    node* z = search_name(root, name);
    if (z == NULL)
    {
        cout << "No such name" << endl;
        return;
    }
    node* x, * y;
    if (z->left == NULL || z->right == NULL)
        y = z;
    else
        y = treeSuccessor(z);
    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;
    if (x != NULL)
        x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    if (y != z)
        z->data = y->data;
    if (y->color == 0)
        deleteFixUp(x);
    delete y;
}

void fileSystem::finder()
{
    cout << "Please input the id or name you want to find" << endl;
    string name;
    int id;
    cin >> name;
    if (name[0] >= '0' && name[0] <= '9')
    {
        id = stoi(name);
        node* ans = search_id(root, id);
        if (ans == NULL)
            cout << "No such id" << endl;
        else
            cout << "The name is " << ans->data->m_Name << endl;
    }
    else
    {
        node* ans = search_name(root, name);
        if (ans == NULL)
            cout << "No such name" << endl;
        else
            cout << "The id is " << ans->data->m_Id << endl;
    }
}

int main()
{
    fileSystem fs;


    return 0;
}