#include <iostream>
#include <string>
using namespace std;

// 加号运算符重载
class Person
{
public:
    int m_a;
    int m_b;
};

// =========== 只能用 全局函数重载<< ===============
ostream &operator<<(ostream &cout, Person &p)
{
    cout << "m_a = " << p.m_a << endl;
    cout << "m_b = " << p.m_b << endl;

    return cout;
}

void test1()
{
    Person p;
    p.m_a = 10;
    p.m_b = 50;

    cout << p << endl;
}

int main()
{
    test1();

    system("pause");
    return 0;
}