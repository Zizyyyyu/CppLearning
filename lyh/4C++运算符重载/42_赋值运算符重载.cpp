#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(int age)
    {
        // 深拷贝， 将年龄数据开辟到堆区，其中 m_Age 属于指针
        m_Age = new int(age);
    }

    // 重载赋值运算符，返回值应该是Person，而非void，这样可以实现链式
    Person &operator=(Person &p)
    {
        //应该先判断是否有属性在堆区，如果有应该先释放干净，然后再深拷贝
        if (m_Age != NULL)
        {
            delete m_Age;
            m_Age = NULL;
        }
        // 编译器提供的代码是浅拷贝
        // m_Age = p.m_Age;

        // 提供深拷贝 解决浅拷贝的问题
        m_Age = new int(*p.m_Age);

        // 返回自身
        return *this;
    }

    // 当一个 Person 对象生命周期结束要被销毁时，这个函数负责把 m_Age 指针在堆区（Heap）申请的内存释放掉。
    ~Person() // 析构函数的标志：波浪号 ~ 类名
    {
        if (m_Age != NULL) // 1. 检查指针是否为空
        {
            delete m_Age; // 2. 释放堆区内存，防止内存泄漏
            m_Age = NULL; // 3. 将指针置空，防止变成野指针
        }
    }

    // 年龄的指针
    int *m_Age;
};

void test01()
{
    Person p1(18);

    Person p2(20);

    Person p3(30);

    p3 = p2 = p1; // 赋值操作

    cout << "p1的年龄为：" << *p1.m_Age << endl;

    cout << "p2的年龄为：" << *p2.m_Age << endl;

    cout << "p3的年龄为：" << *p3.m_Age << endl;
}

int main()
{

    test01();

    // int a = 10;
    // int b = 20;
    // int c = 30;

    // c = b = a;
    // cout << "a = " << a << endl;
    // cout << "b = " << b << endl;
    // cout << "c = " << c << endl;

    system("pause");

    return 0;
}