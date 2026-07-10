#include <iostream>
#include <string>
using namespace std;

// 加号运算符重载
class Person
{
public:
    // 1、成员函数重载+号
    // Person operator+(Person &p){
    //     Person temp;
    //     temp.m_a = this->m_a + p.m_a;
    //     temp.m_b = this->m_b + p.m_a;
    //     return temp;
    // }

    int m_a;
    int m_b;
};

// 2、全局函数重载+号
Person operator+(Person &p1, Person &p2)
{
    Person temp;
    temp.m_a = p1.m_a + p2.m_a;
    temp.m_b = p1.m_b + p2.m_b;

    return temp;
}

// 3、运算符重载也可以发生函数重载
Person operator+(Person &p1, int num)
{
    Person temp;
    temp.m_a = p1.m_a + num;
    temp.m_b = p1.m_b + num;

    return temp;
}

void test1()
{
    Person p1;
    p1.m_a = 10;
    p1.m_b = 50;

    Person p2;
    p2.m_a = 20;
    p2.m_b = 30;

    //成员函数重载本质调用
    // Person p3 = p1.operator+(p2);

    // 全局函数重载本质调用
    // Person p3 = operator+(p1, p2);

    //运算符重载也可以发生函数重载
    //比如：
    Person p3 = p1 + 10;

    Person p3 = p1 + p2;
    cout << "p3.m_a = " << p3.m_a << endl;
    cout << "p3.m_b = " << p3.m_b << endl;
}

int main()
{
    test1();

    system("pause");
    return 0;
}