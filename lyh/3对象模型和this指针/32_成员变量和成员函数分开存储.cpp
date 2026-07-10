#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
    int m_a;        //非静态成员变量  属于类的对象上

    static int m_b; //静态成员变量   不属于类对象上

    void func() {} // 非静态成员函数  不属于类对象上

    static void func2() {} // 非静态成员函数  不属于类对象上
};


void test01()
{
    Person p;
    //类中有四个成员，但是属于类对象的只有一个，其余分开存储
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{

    test01();

    system("pause");

    return 0;
}