#include <iostream>
using namespace std;

// 这两个交换函数主题类似，我们可以使用函数模板
template <class T> // 声明一个模板，typename 可以替换成 class
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void func(){
    cout << "func 调用" << endl;
}


void test1()
{
    int a = 10;
    int b = 20;
    char c = 'c';
    // 1、自动类型推导， 必须推导一直的数据类型 T 才可以使用
    mySwap(a, b);
    // mySwap(a, c);    //错误！推导不出一致的 T 类型

    //2、模板必须要确定出T的数据类型， 才可以使用
    func<int>();    //确定数据类型
    // func();         //不确定数据类型
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

int main()
{

    test1();
    system("pause");
    return 0;
}