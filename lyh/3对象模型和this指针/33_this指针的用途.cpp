#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
public:
    Person(int age){
        // 1、当形参和成员变量同名时，可用this指针来区分，当 p1对象 调用这个类，指针 this 指向 p1对象
        this->age = age; // 构造函数参数 `age` 与成员变量 `age` 同名
    }

    Person& PersonAddAge(Person &p){
        // 这个函数的作用是把另一个人的年龄，加到自己身上。

        //this->age 代表调用这个函数的对象（比如 p2）的年龄。
        //p.age 代表传进来的那个对象（比如 p1）的年龄。 
        //把 p1 的年龄加到 p2 身上
        
        this->age += p.age;

        //this 指向 p2 的指针，而 *this 指向的就是 p2 这个对象本体
        return *this;
    }

    int age;
};

void test01()
{
    Person p(18);
    cout << "p1 的年龄为：" << p.age << endl;
}

void test01(){
    Person p1(10);

    Person p2(10);

    p2.PersonAddAge(p1).PersonAddAge(p1); // 先执行前面的 p2.PersonAddAge(p1)，执行完后它返回了 p2 本身，接着代码就变成了 p2.PersonAddAge(p1)，实现了像链条一样连续调用。
    // 正确做法是，修改 PersonAddAge() 函数，增加返回值 return *this;

    cout << "p2 的年龄为：" << p2.age << endl;
}

    int main()
{

    test01();

    system("pause");

    return 0;
}