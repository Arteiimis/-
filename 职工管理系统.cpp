#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"   
#include"manager.h"
#include"boss.h"
using namespace std;
int main(void)
{
    //����
    /*Worker* worker = NULL;
    worker = new Employee(1, "sb", 1);
    worker->ShowInfo();
    delete worker;
    worker = new Manager(1, "sbb", 2);
    worker->ShowInfo();
    delete worker;*/

    //ʵ����һ�������ߵĶ���
    WorkerManager wm;
    int choice = 0;//�����洢�û���ѡ��
    while (1)
    {
        //��ʾ�˵�
        wm.Show_Menu();
        cout << "���������ѡ��" << endl;
        cin >> choice;

        switch (choice)
        {
        case 0://�˳�ϵͳ
            wm.ExitSystem();
            break;
        case 1://���ְ��
            wm.AddEmp();
            break;
        case 2://��ʾְ��
            wm.Show_Emp();
            break;
        case 3://ɾ��ְ��
            wm.Del_Emp();
            break;
        case 4://�޸�ְ��
            wm.Mod_Emp();
            break;
        case 5://����ְ��
            wm.Find_Emp();
            break;
        case 6://����ְ��
            wm.Sort_Emp();
            break;
        case 7://����ļ�
            wm.Clean_File();
            break;
        default:
            system("cls");//����
            break;
        }

    }
    system("pause");
    return 0;
}