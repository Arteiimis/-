#pragma once//��ֹͷ�ļ��ظ�����
#include<iostream>
#include<string>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#include<algorithm>
#define FILENAME "test.txt"
using namespace std;//ʹ�ñ�׼�����ռ�
class WorkerManager
{
public:
    //���캯��
    WorkerManager();
    //չʾ�˵�
    void Show_Menu();
    //�˳�����
    void ExitSystem();
    //��¼ְ������
    int m_EmpNum;
    //ְ������ָ��
    Worker** m_EmpArray;
    //���ְ��
    void AddEmp();
    //�����ļ�
    void SaveFile();
    //�ж��ļ��Ƿ�Ϊ�ձ�־
    bool m_FileIsEmpty;
    //ͳ���ļ��е�����
    int Get_EmpNum();
    //��ʼ��ְ��
    void Init_Emp();
    //��ʾְ��
    void Show_Emp();
    //�ж�ְ���Ƿ����
    int IsExist(int id);
    //ɾ��ְ��
    void Del_Emp();
    //�޸�ְ��
    void Mod_Emp();
    //����ְ��
    void Find_Emp();
    //Ա������
    void Sort_Emp();
    //�������
    void Clean_File();
    //��������
    ~WorkerManager();
};