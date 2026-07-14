#include<iostream>
#include <string>
    using namespace std;

class Base
{ // 父类

public:
    Base(){
        cout << "Base 构造函数" << endl;
    }

    ~Base(){
        cout << "Base 析构函数" << endl;
    }
};

class Son : public Base
{

public:
    Son()
    {
        cout << "Son 构造函数" << endl;
    }

    ~Son()
    {
        cout << "Son 析构函数" << endl;
    }
};

void test1()
{
    // Base b;

    Son s;
}

int main()
{

    test1();

    system("pause");

    return 0;
}