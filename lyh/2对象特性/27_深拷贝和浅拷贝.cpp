#include <iostream>
using namespace std;

// 深拷贝和浅拷贝

class Person
{

public:
    int m_age;     // 年龄
    int *m_height; // 身高
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }

    Person(int age, int height)
    {
        m_age = age;
        m_height = new int(height); // 在堆（自由存储区）上分配一个 int 类型的对象，并用 height 的值来初始化它，然后将这个对象的地址赋给指针 m_height
        cout << "Person的有参构造函数调用" << endl;
    }

    Person(const Person &p)
    {
        cout << "Person 拷贝构造函数调用" << endl;
        m_age = p.m_age;
        // m_height=p.m_height; //编译器默认实现浅拷贝，直接将堆区地址复制一份

        // 深拷贝
        m_height = new int(*p.m_height); // 在堆（自由存储区）上分配一个 int 类型的对象，并用 *p.m_height 的值来初始化它，然后将这个对象的地址赋给指针 m_height。
    }

    ~Person()
    {
        // 析构代码，将堆区开辟数据做释放操作
        // 当指针 m_height 指向的堆区数据被释放时，运行析构代码
        if (m_height != NULL)
        {
            delete m_height; // 释放指针 m_height 指向的地址空间
            m_height = NULL; // 避免野指针
        }
        cout << "Person的析构函数调用" << endl;
    }
};

void test1()
{
    Person p1(18, 160);
    cout << "p1的年龄为：" << p1.m_age << "身高为： " << *p1.m_height << endl;

    Person p2(p1); // 拷贝构造函数
    cout << "p2的年龄为：" << p2.m_age << "身高为： " << *p2.m_height << endl;
}

int main()
{

    test1();
    system("pause");
    return 0;
}