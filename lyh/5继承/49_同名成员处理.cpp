#include <iostream>
#include <string>
using namespace std;

class Base
{ // 父类

public:
    int m_a;

    Base()
    {
        m_a = 100;
    }
    void func(){
        cout << "Base  func()调用" << endl;
    }
};

class Son : public Base
{

public:
    int m_a;

    Son(){
        m_a = 200;
    }

    void func()
    {
        cout << "Son  func()调用" << endl;
    }
};

void test1()
{
    Son s;
    cout << "Son 下的 m_a = " << s.m_a << endl;
    cout << "Base 下的 m_a = " << s.Base::m_a << endl;
}

void test2(){
    Son s2;
    s2.func();

    //如何调用到父类中同名成员函数
    s2.Base::func();
}

int main()
{

    // test1();
    test2();

    system("pause");

    return 0;
}