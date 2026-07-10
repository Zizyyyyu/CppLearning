#include <iostream>
using namespace std;

//拷贝构造函数调用时机

class Person
{
public:

    int m_age;

    Person()
    {
        cout << "Person 无参构造函数的调用" << endl;
    }

    Person(int a)
    {
        m_age = a;
        cout << "Person 有参构造函数的调用" << endl;
    }

    // 拷贝构造函数
    Person(const Person &p)
    {
        // 将传入的人身上的所有属性，拷贝到我身上
        m_age = p.m_age;
        cout << "Person 拷贝构造函数的调用" << endl;
    }

    ~Person()
    {
        cout << "Person 析构函数的调用" << endl;
    }
};
// 1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01()
{

    Person p1(100);      // p对象已经创建完毕
    Person p2(p1);   // 调用拷贝构造函数
    //Person newman2 = man; // 拷贝构造
    cout << "P2的年龄为：" << p2.m_age << endl;
    // Person newman3;
    // newman3 = man; //不是调用拷贝构造函数，这是赋值操作
}


// 2. 值传递的方式给函数参数传值
// 相当于Person p1 = p;
void doWork(Person p1) {}   //值传递，其本质就是复印，将实参p传入时，只是在函数内部临时赋值一份一模一样的副本，取名p1

void test02()
{
    Person p;       // 无参构造函数
    doWork(p);      // 值传递, 将实参p传入时，只是在函数内部临时赋值一份一模一样的副本，取名p1, 此时调用了 Person 的拷贝构造函数
}

// 3. 以值方式返回局部对象
Person doWork2()
{
    Person p1;
    return p1;
}

void test03()
{
    Person p = doWork2();
}

int main()
{

    // test01();
    // test02();
    test03();

    system("pause");
    return 0;
}