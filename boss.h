#pragma once
#include<iostream>
#include"worker.h"
#include<string>
using namespace std;
//老板类
class Boss :public Worker
{
public:
    //构造函数
    Boss(int id, string name, int deptid);
    //显示个人信息
    virtual void ShowInfo();
    //获取岗位名称
    virtual string GetDeptName();
};