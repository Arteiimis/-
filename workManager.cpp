#include"workerManager.h"

//构造函数
WorkerManager::WorkerManager()
{
    //1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        //初始化属性
        //初始化记录人数为0
        this->m_EmpNum = 0;
        //初始化数组指针为空
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //2.文件存在 数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //初始化属性
        //初始化记录人数为0
        this->m_EmpNum = 0;
        //初始化数组指针为空
        this->m_EmpArray = NULL;
        //初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
    }
    //3.文件存在不为空
    int num = this->Get_EmpNum();
    this->m_EmpNum = num;
    //开辟空间，当文件中的数据存到数组中
    this->m_EmpArray = new Worker * [this->m_EmpNum];
    this->Init_Emp();

}
//展示菜单
void WorkerManager::Show_Menu()
{
    cout << "*****************************" << endl;
    cout << "*****欢迎使用职工管理系统*****" << endl;
    cout << "*******0-退出管理程序*********" << endl;
    cout << "*******1-增加职工信息*********" << endl;
    cout << "*******2-显示职工信息*********" << endl;
    cout << "*******3-删除离职职工*********" << endl;
    cout << "*******4-修改职工信息*********" << endl;
    cout << "*******5-查找职工信息*********" << endl;
    cout << "*******6-按照编号排序*********" << endl;
    cout << "*******7-清空所有文档*********" << endl;
    cout << "*****************************" << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
    cout << "欢迎下次使用" << endl;
    system("pause");
    exit(0);
}
//添加职工
void WorkerManager::AddEmp()
{
    cout << "请输入添加职工的数量" << endl;
    int addnum = 0;//保存用户输入的数量
    cin >> addnum;
    if (addnum > 0)
    {
        //计算添加所需新空间的大小
        int NewSize = this->m_EmpNum + addnum;//先在里面的人数等于原来的+新添加的
        //开辟新空间——动态数组
        Worker** NewSpace = new Worker * [NewSize];
        //将原来空间下的数据拷贝到新空间下
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                NewSpace[i] = this->m_EmpArray[i];
            }
        }
        //添加新的数据
        for (int i = 0; i < addnum; i++)
        {
            int id = 0;//职工编号
            string name;//职工姓名
            int dselect;//部门选择
            cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
            /*
                这里的判断输入重复是有缺陷的，例如我们要添加2个新员工，如果输入的第二个人和第一个人的编号一样，
                这样就判断不出来重复了,:(
            */
            while (cin >> id)
            {
                int adjust = 0;
                for (int j = 0; j < this->m_EmpNum; j++)
                {
                    if (id == this->m_EmpArray[j]->m_Id)
                    {
                        cout << "此编号已存在!请重新输入" << endl;
                        adjust = 1;
                    }
                }
                if (adjust == 0)
                {
                    break;
                }
            }
            cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
            cin >> name;
            cout << "请选择该职工的岗位" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> dselect;
            Worker* worker = NULL;
            switch (dselect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }

            //将创建的职工指针，保存到数组中
            NewSpace[this->m_EmpNum + i] = worker;
        }
        //释放原有的空间
        delete[] this->m_EmpArray;
        //更改新空间的指向
        this->m_EmpArray = NewSpace;
        //更新职工人数
        this->m_EmpNum = NewSize;
        //更新职工不为空的标志
        this->m_FileIsEmpty = false;
        //提示
        cout << "成功添加" << addnum << "个新职工" << endl;
        //保存数据到文件中
        this->SaveFile();
    }
    else
    {
        cout << "输入有误" << endl;
    }
    //按任意键后清屏
    system("pause");
    system("cls");
}
//保存文件
void WorkerManager::SaveFile()
{
    ofstream ofs;
    ofs.open("test.txt", ios::out);//用输出方式打开文件——写文件
    //将每个人的数据写入到文件
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << " "
            << this->m_EmpArray[i]->m_Name << " "
            << this->m_EmpArray[i]->m_DeptId << endl;
    }
}
//统计人数
int WorkerManager::Get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//打开文件
    int id;
    string name;
    int did;
    //计数器
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        num++;
    }
    return num;
}
//初始化职工
void WorkerManager::Init_Emp()
{
    //就是把文件里面的内容读进来
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int did;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        Worker* worker = NULL;
        if (did == 1)
        {
            worker = new Employee(id, name, did);
        }
        else if (did == 2)
        {
            worker = new Manager(id, name, did);
        }
        else
        {
            worker = new Boss(id, name, did);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}
//显示职工
void WorkerManager::Show_Emp()
{
    //判断文件是否为空
    if (this->m_FileIsEmpty)
    {
        cout << "文件为空或记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            //利用多条调用程序接口
            this->m_EmpArray[i]->ShowInfo();
        }
    }
    //按任意键后清屏
    system("pause");
    system("cls");
}
//判断职工是否存在
int WorkerManager::IsExist(int id)
{
    int index = -1;//一看是认定不存在
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            //找到职工
            index = i;
            break;
        }
    }
    return index;
}
//删除职工
void  WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或者记录为空" << endl;
    }
    else
    {
        //按照职工的编号来删除职工
        cout << "请输入要删除职工的编号" << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1)//存在-删除
        {
            //在数组中删除数据本质上就是数据前移
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            //更新数组中记录人员个数
            this->m_EmpNum--;
            //数据同步更新到文件中
            this->SaveFile();
            cout << "删除成功" << endl;
        }
        else
        {
            cout << "删除失败，未找到该员工" << endl;
        }
        //按任意键清屏
        system("pause");
        system("cls");
    }
}
//修改职工
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入要修改的职工编号" << endl;
        int id = 0;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            //查找到了
            delete this->m_EmpArray[ret];//删除旧的，创建新的
            int newid = 0;;
            string newname = " ";
            int newselect = 0;
            cout << "查找到了编号为" << id << "的这个职工," << "请输入新的职工号" << endl;
            cin >> newid;
            cout << "请输入新的姓名" << endl;
            cin >> newname;
            cout << "请输入新的岗位" << endl;
            cout << "1.普通职工" << endl;
            cout << "2.经理" << endl;
            cout << "3.老板" << endl;
            cin >> newselect;
            Worker* worker = NULL;
            switch (newselect)
            {
            case 1:
                worker = new Employee(newid, newname, newselect);
                break;
            case 2:
                worker = new Manager(newid, newname, newselect);
                break;
            case 3:
                worker = new Boss(newid, newname, newselect);
                break;
            default:
                break;
            }
            //更新数据到数组中
            this->m_EmpArray[ret] = worker;
            cout << "修改成功!" << endl;
            this->SaveFile();//保存到文件中
        }
        else
        {
            cout << "修改失败，查无此人。" << endl;
        }
    }
    system("pause");
    system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
    }
    else
    {
        cout << "请输入查找的方式" << endl;
        cout << "1.按职工编号查找" << endl;
        cout << "2.按职工姓名查找" << endl;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            //按照编号查
            int id;
            cout << "请输入查找的职工编号" << endl;
            cin >> id;
            int ret = this->IsExist(id);
            if (ret != -1)
            {
                cout << "查找成功！该职工的信息如下:" << endl;
                this->m_EmpArray[ret]->ShowInfo();
            }
            else
            {
                cout << "查找失败，查无此人!" << endl;
            }
        }
        else if (select == 2)
        {
            //按照姓名查找
            string name;
            cout << "请输入要查找的姓名" << endl;
            cin >> name;
            //加入判断是否查到的标志
            bool flag = false;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout << "查找成功,职工编号为" << this->m_EmpArray[i]->m_Id << "的职工，他的信息如下:" << endl;
                    this->m_EmpArray[i]->ShowInfo();
                    flag = true;
                }
            }
            if (flag == false)
            {
                cout << "查找失败，查无此人" << endl;
            }
        }
        else
        {
            cout << "输入选项有误" << endl;
        }
        //按任意键清屏
        system("pause");
        system("cls");
    }
}
//员工排序
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空" << endl;
        system("system");
        system("clsf");
    }
    else
    {
        cout << "请选择排序方式" << endl;
        cout << "1.按照职工号进行升序" << endl;
        cout << "2.按照职工号进行降序" << endl;
        int select = 0;
        cin >> select;
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int MinOrMax = i;//声明最大值或最小值下标
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1)
                {
                    //升序
                    if (this->m_EmpArray[MinOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        MinOrMax = j;
                    }
                }
                else
                {
                    //降序
                    if (this->m_EmpArray[MinOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        MinOrMax = j;
                    }
                }
            }
            //判断一开始认定的最大值或最小值是不是计算的最大值或最小值，如果不是就交换
            if (i != MinOrMax)
            {
                Worker* temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[MinOrMax];
                this->m_EmpArray[MinOrMax] = temp;
            }
        }
        cout << "排序成功！排序后的结果为:" << endl;
        this->SaveFile();//将排序后的结果保存到文件中
        this->Show_Emp();//展示所有职工
    }
}
//清空数据
void WorkerManager::Clean_File()
{
    cout << "确认清空吗?" << endl;
    cout << "1.确认" << endl;
    cout << "2.取消" << endl;
    int select = 0;;
    cin >> select;
    if (select == 1)
    {
        //清空文件
        ofstream ofs(FILENAME, ios::trunc);
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            //删除堆区的每个对象
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                delete this->m_EmpArray[i];
            }
            //删除堆区数组指针
            delete this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功！" << endl;

    }
    system("pause");
    system("cls");
}
//析构函数
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            delete this->m_EmpArray[i];
        }
        delete this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}