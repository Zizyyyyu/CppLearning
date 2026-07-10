#include <iostream>
using namespace std;

//对象的初始化和清理
//1、构造函数 进行初始化操作
class Person{

public:
    //1、构造函数
    //没有返回值， 不用写void
    //函数名与类名相同
    //构造函数可以有参数，可以发生重载
    //创建对象的时候，构造函数会自动调用，而且只调用一次
    Person(){
        cout << "Person 构造函数的调用" << endl;
    }

    //2、析构函数 进行清理的操作
    //没有返回值 不屑void
    //函数名和类名相同 在名称前加~
    //析构函数不可以有参数，不可以发生重载
    //对象在销毁前 会自动调用析构函数，而且只会调用一次
    ~Person(){
        cout << "Person 析构函数的调用" << endl;
    }

};

//构造函数和析构函数都是必须有的实现，如果我们自己不提供，编译器会提供一个空实现的构造和析构
void test1(){
    Person p;       //在栈上的数据，调用结束后会销毁
}

int main()
{

    test1();

    Person p;   //此时只执行了构造，main函数还没有销毁，所以还没有执行析构函数

    
    system("pause");
    return 0;
}