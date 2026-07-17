#include <iostream>
using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }

    string m_Name;
    int m_Age;
};

// 对比两个数据是否相等的函数
template <class T>
bool myCompare(T &a, T &b) // 假如自定义对象和类，那么无法比较
{
    if (a == b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 利用具体化Person的版本实现代码，具体化优先调用
template <>
bool myCompare(Person &a, Person &b) // 假如自定义对象和类，那么无法比较
{
    if (a.m_Age == b.m_Age && a.m_Name == b.m_Name)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void test1()
{
    int a = 10;
    int b = 10;

    bool ret = myCompare(a, b);

    if (ret == true)
    {
        cout << "a = b" << endl;
    }
    else
    {
        cout << "a不等于b" << endl;
    }
}

void test2()
{
    Person p1("Tom", 10);
    Person p2("Tom", 10);

    bool ret = myCompare(p1, p2);

    if (ret == true)
    {
        cout << "p1 = p2" << endl;
    }
    else
    {
        cout << "p1不等于p2" << endl;
    }
}

int main()
{

    test1();
    test2();
    system("pause");
    return 0;
}