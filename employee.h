#pragma once
#include<iostream>
#include"worker.h"
using namespace std;


//普通职工类
class Employee :public Worker
{
public://子类重写父类的虚函数or纯虚函数时,注意你写的是函数的声明还是函数的定义
    //构造函数
    Employee(int id, string name, int deptid);//属性初始化
    //显示个人信息
    virtual void ShowInfo();//子类重写父类的虚函数or纯虚函数,virtual可删可不删
    //获取岗位名称
    virtual string GetDeptName();
};