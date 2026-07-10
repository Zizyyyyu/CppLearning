#include <iostream>
using namespace std;
//成员属性设置私有
//1、可以自己控制读写权限
//2、对于写可以检测数据有效性


//人类
class Person{
public:
    //有 setname() , 有 getname() ,说明可读可写
    void setname(string name){  //设置姓名
        m_name = name;
    }

    string getname(){       //获取姓名
        return m_name;
    }


    //读年龄
    int getage(){
        return m_age;       //获取年龄
    }

    //写年龄，并验证年龄的有效性
    void setage(int age){
        if(age<0||age>150){
            cout << "输入有误" << endl;
            return;
        }
        else{
            m_age = age;
        }
    }

    //设置偶像
    void setidol(string idol){
        m_idol = idol;
    }
    //有setidol(),没有getidol()，限制偶像只写

private:
    string m_name;  //姓名  可读可写

    int m_age;      //年龄  可读可写

    string m_idol;  //偶像  只写
};
int main()
{
    Person p;
    //姓名设置就不能类外执行了，可以在类内的公有权限进行姓名设置
    //p.m_name = "张三";    //错误

    p.setname("张三");

    p.setage(1000);     //设置年龄
    p.getage();         //读取年龄


    system("pause");
    return 0;
}