#pragma once//防止头文件重复包含
#include<iostream>
#include<string>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#include<algorithm>
#define FILENAME "test.txt"
using namespace std;//使用标准命名空间
class WorkerManager
{
public:
    //构造函数
    WorkerManager();
    //展示菜单
    void Show_Menu();
    //退出程序
    void ExitSystem();
    //记录职工人数
    int m_EmpNum;
    //职工数组指针
    Worker** m_EmpArray;
    //添加职工
    void AddEmp();
    //保存文件
    void SaveFile();
    //判断文件是否为空标志
    bool m_FileIsEmpty;
    //统计文件中的人数
    int Get_EmpNum();
    //初始化职工
    void Init_Emp();
    //显示职工
    void Show_Emp();
    //判断职工是否存在
    int IsExist(int id);
    //删除职工
    void Del_Emp();
    //修改职工
    void Mod_Emp();
    //查找职工
    void Find_Emp();
    //员工排序
    void Sort_Emp();
    //清空数据
    void Clean_File();
    //析构函数
    ~WorkerManager();
};