#pragma once
#include<iostream>
#include"worker.h"
using namespace std;


//��ְͨ����
class Employee :public Worker
{
public://������д������麯��or���麯��ʱ,ע����д���Ǻ������������Ǻ����Ķ���
    //���캯��
    Employee(int id, string name, int deptid);//���Գ�ʼ��
    //��ʾ������Ϣ
    virtual void ShowInfo();//������д������麯��or���麯��,virtual��ɾ�ɲ�ɾ
    //��ȡ��λ����
    virtual string GetDeptName();
};