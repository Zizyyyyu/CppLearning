#include <iostream>
#include <string>
using namespace std;

// 公共继承
class Base1
{
public:
    int m_a;

protected:
    int m_b;

private:
    int m_c;
};

class Son1 : public Base1
{

public:
    void func()
    {
        m_a = 10; // 父类的公共权限成员到子类中依然是公共权限
        m_b = 10; // 父类的保护权限成员到子类中依然是保护权限
        // m_c = 10;   // 父类的私有权限成员到子类中依然是私有权限
    }
};
class Son2:protected Base1
{
public:
    void func(){
        m_a = 100;      //父类中公有成员， 到子类中变为保护权限
        m_b = 100;      //父类中保护成员， 到子类中变为保护权限
        // m_c = 100;   //父类的私有权限成员到子类中依然是私有权限, 子类访问不到
    }
};

void test1()
{
    Son1 s1;
    s1.m_a = 100;
    // s1.m_b = 100;    //保护权限不可访问
}

void test2()
{
    Son2 s2;
    // s2.m_a = 100; // Son2 保护继承 Base1， 父类中公有成员， 到子类中变为保护权限，因此类外访问不到
    // s1.m_b = 100;    //保护权限不可访问
}
main()
{

    test1();

    system("pause");

    return 0;
}