#include <iostream>
#include <string>
using namespace std;

// 类对象作为类成员

// 手机类
class Phone{
public:

    Phone(string pName){    // 手机 类对象赋初值
        cout << "Phone 的构造函数调用" << endl;
        m_Pname = pName;
    }

    ~Phone()
    {
        cout << "Phone 的析构函数调用" << endl;
    }

    string m_Pname;
};

//人类
class Person{
public:
    Person(string name, string pName):m_name(name), m_phone(pName){
        // /m_phone(pName)代表对 “Phone” 类的对象 赋初值

        cout << "Person 的构造函数调用" << endl;
        }


    ~Person(){
        cout << "Person 的析构函数调用" << endl;
    }
    // 姓名
    string m_name;

    // 手机
    Phone m_phone; // 这是一个 “Phone” 类的对象
};

// 注意：当其他类对象作为本类成员，构造时候先构造类对象，再构造自身, 析构的顺序与构造相反

void test1(){
    Person p("张三", "苹果MAX");

    cout << p.m_name << " 使用" << p.m_phone.m_Pname << " 牌手机! " << endl;
}
int main()
{
    test1();
    system("pause");
    return 0;
}