#include<iostream>
using namespace std;

//两个整型交换函数
void swapInt(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

// 两个浮点型交换函数
void swapInt(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

//这两个交换函数主题类似，我们可以使用函数模板
template<typename T>    //声明一个模板，告诉编译器后面代码中紧跟着的T不要报错，T是一个通用的数据类型
void mySwap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}

void test1() {
    int a = 10;
    int b = 20;

    // swapInt(a, b);
    //使用函数模板
    //1、自动类型推导
    mySwap(a, b);


    //2、显示指定类型
    mySwap<int>(a, b);

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

int main(){

    test1();
    system("pause");
    return 0;
}