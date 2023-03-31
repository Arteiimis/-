#include"manager.h"
//构造函数
Manager::Manager(int id, string name, int deptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = deptid;
}
//显示个人信息
void Manager::ShowInfo()
{
    cout << "职工编号:" << this->m_Id
        << "\t职工姓名:" << this->m_Name
        << "\t岗位:" << this->GetDeptName()
        << "\t岗位职责:完成老板交个任务，并且下发任务给普通员工" << endl;
}
//获取岗位名称
string Manager::GetDeptName()
{
    return string("经理");
}