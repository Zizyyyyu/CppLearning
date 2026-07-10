#include <iostream>
using namespace std;

//构造函数的调用规则
//1、创建一个类，C++编译器会给每一个类都添加至少3格函数
//默认构造      （空实现）
//析构函数      （空实现）
//拷贝构造      （值拷贝）

class Person{

public:
    int m_age;

    // Person(){
    //     cout << "Person 的默认构造函数调用" << endl;
    // }

    Person(int age)
    {
        m_age = age;
        cout << "Person 有参的默认构造函数调用" << endl;
    }

    Person(const Person &p)
    {
        m_age = p.m_age;
        cout << "Person 拷贝构造函数调用" << endl;
    }

    ~Person(){
        cout << "Person 的析构函数调用" << endl;
    }
};

// void test1(){
//     Person p;
//     p.m_age = 18;

//     Person p2(p);   //拷贝构造
//     cout << "p2的年龄为： " << p2.m_age << endl;
// }

void test2(){
    //Person p;
}
int main()
{

    // test1();
    test2();
    system("pause");
    return 0;
}