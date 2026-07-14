#include <iostream>
#include <string>
using namespace std;

class Base{ //父类

public:
    int m_a;

protected:
    int m_b;

private:
    int m_c;
};

class Son:public Base{

public:
    int m_d;
};

void test1(){
    //父类中所有非静态成员属性都会背子类继承下去
    //父类中私有成员属性  是被编译器给隐藏了， 因此是访问不到，但是确实被继承下去了
    cout << "size of Son = " << sizeof(Son) << endl;
}

int main()
{

    test1();

    system("pause");

    return 0;
}