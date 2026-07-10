#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
public:
    void showClassName(){
        cout << "this is Person class" << endl;
    }

    void showPersonAge(){
        cout << "age = " << this->m_age << endl;
    }

    int m_age;
};

void test01()
{
    Person *p = NULL;
    p->showClassName();
    p->showPersonAge();
    //cout << "p1 的年龄为：" << p.age << endl;
}


int main()
{

    test01();

    system("pause");

    return 0;
}