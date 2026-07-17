#include <iostream>
using namespace std;

// 类模板与函数模板的区别
// 1、类模板没有自动类型推导使用方式
// 2、
template <class NameType, class AgeType = int>
class Person
{
public:
    Person(NameType name, AgeType age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }

    void showPerson()
    {
        cout << "name: " << m_Name << endl;
        cout << "age: " << m_Age << endl;
    }

    NameType m_Name;
    AgeType m_Age;
};

void test1()
{
    // 1、类模板没有自动类型推导使用方式, 以前不行，现在好像是可以了
    Person p("猪八戒", 888);

    // 利用类模板创建对象
    Person<string, int> p1("孙悟空", 999);
    p1.showPerson();
}

// 2、类模板在模板参数列表中可以有默认参数
void test2()
{
    Person<string> p("沙悟净", 1000);
}

int main()
{

    test1();
    system("pause");
    return 0;
}