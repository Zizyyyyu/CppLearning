#include <iostream>
#include <string>
using namespace std;
//**常函数：**
    //成员函数后加const后我们称为这个函数为  常函数 
    // 常函数内不可以修改成员属性
    // 成员属性声明时加关键字mutable后，在常函数中依然可以修改

//* *常对象： **

    //声明对象前加const称该对象为常对象 
    //常对象只能调用常函数


class Person
{
public:
    // this 指针的本质   是指针常量    指针的指向是不可以修改的
    // Person * const this;

    //在成员函数后面加上 const ，修饰的是 this 指向， 让指针指向的值也不可以修改，所以第22行代码无法修改
    void showPerson() const     //常函数
    {
        // /this->m_b = 100;
        this->m_b = 100;
        //this = NULL;  //this 指针不可以修改指针的指向的
    }

    void func() {      //普通函数

    };

    void showPersonAge()
    {
        cout << "age = " << this->m_a << endl;
    }
    int m_a;
    mutable int m_b;    //特殊变量，加上 mutable 就可以修改指针指向
};

void test01()
{
    const Person p{};     //在对象前加const， 变为常对象
    // p.m_a = 100;    //常对象所有属性均为只读，除非加上了mutable
    // p.m_b = 100;    //m_b 是 mutable ，可变的，所以虽然 p 是常对象，但是依然可以修改之

    //常对象只能调用常函数
    p.showPerson(); // showPerson()是常函数
    // p.func();       //func 不是常函数
}

int main()
{

    test01();

    system("pause");

    return 0;
}