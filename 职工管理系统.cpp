#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"   
#include"manager.h"
#include"boss.h"
using namespace std;
int main(void)
{
    //测试
    /*Worker* worker = NULL;
    worker = new Employee(1, "sb", 1);
    worker->ShowInfo();
    delete worker;
    worker = new Manager(1, "sbb", 2);
    worker->ShowInfo();
    delete worker;*/

    //实例化一个管理者的对象
    WorkerManager wm;
    int choice = 0;//用来存储用户的选择
    while (1)
    {
        //显示菜单
        wm.Show_Menu();
        cout << "请输入你的选择" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0://退出系统
            wm.ExitSystem();
            break;
        case 1://添加职工
            wm.AddEmp();
            break;
        case 2://显示职工
            wm.Show_Emp();
            break;
        case 3://删除职工
            wm.Del_Emp();
            break;
        case 4://修改职工
            wm.Mod_Emp();
            break;
        case 5://查找职工
            wm.Find_Emp();
            break;
        case 6://排序职工
            wm.Sort_Emp();
            break;
        case 7://清空文件
            wm.Clean_File();
            break;
        default:
            system("cls");//清屏
            break;
        }

    }
    system("pause");
    return 0;
}