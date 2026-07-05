#include <iostream>
using namespace std;
//设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号

class Student{

public:     //公共权限

    //属性
    string m_name;  //姓名
    int m_id;       //学号


    //行为
    void showStudent(){
        cout << "姓名：" << m_name << endl;
        cout << "学号：" << m_id << endl;
    }
    
    //====通过行为对属性进行赋值操作====
    void setName(string name){
        m_name = name;
    }
};

int main()
{

    //创建一个具体学生——实例化对象
    Student s1;

    s1.setName("张三");     // 通过行为对属性进行赋值操作
    s1.m_id = 1;            // 给 s1 对象 进行属性赋值操作

    //显示学生信息
    s1.showStudent();


    system("pause");
    return 0;
}