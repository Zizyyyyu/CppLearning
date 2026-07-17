#include <iostream>
using namespace std;


class Person1
{
public:
    void showPerson1()
    {
        cout << "Person1 show" << endl;
    }
};

class Person2
{
public:
    void showPerson2()
    {
        cout << "Person2 show" << endl;
    }
};

template <class T>
class MyClass
{
public:
    T obj;

    // 类模板中的成员函数，并不是一开始就创建的，而是在模板调用时再生成

    //通过类模板，让类模板中的类调用其自己的成员函数
    void fun1() { obj.showPerson1(); }
    void fun2() { obj.showPerson2(); }
};

void test01()
{
    MyClass<Person1> m;
    // MyClass：这是一个类模板（模板蓝图）。它本身还不是一个真正的、可以直接使用的类，而是一个“外壳”。

    // <Person1>：这是你传给模板的实际类型（模板实参）。你告诉编译器：“请把 MyClass 蓝图里的那个虚拟类型 T，全部替换成具体的 Person1。”

    // m：这是你创建出来的对象名称。
    m.fun1();

    // m.fun2();//编译会出错，说明函数调用才会去创建成员函数
}

int main()
{

    test01();

    system("pause");

    return 0;
}