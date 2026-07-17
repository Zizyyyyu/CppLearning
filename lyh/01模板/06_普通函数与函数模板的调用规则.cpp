#include <iostream>
using namespace std;

// 调用规则如下：

// 1. 如果函数模板和普通函数都可以实现，优先调用普通函数
// 2. 可以通过空模板参数列表来强制调用函数模板
// 3. 函数模板也可以发生重载
// 4. 如果函数模板可以产生更好的匹配, 优先调用函数模板
void myPrint(int a, int b)
{
    cout << "普通函数" << endl;
}

template <class T>
void myPrint(T a, T b)
{
    cout << "函数模板" << endl;
}

// 发生模板函数重载
template <class T>
void myPrint(T a, T b, T c)
{
    cout << "重载函数模板" << endl;
}

void test1()
{
    int a = 10;
    int b = 10;
    // 1. 如果函数模板和普通函数都可以实现，优先调用普通函数
    myPrint(a, b);

    // 2. 可以通过空模板参数列表来强制调用函数模板
    myPrint<>(a, b);

    // 3. 函数模板也可以发生重载
    myPrint<>(a, b, 100); // 调用重载的模板，模板函数仍然可以进行函数重载

    // 4. 如果函数模板可以产生更好的匹配, 优先调用函数模板
    char c = 'c';
    char d = 'd';
    myPrint(c, d); // 此时c、d都是字符，而普通函数的参数都是整型，所以无法调用普通函数，优先调用函数模板
}

int main()
{

    test1();
    system("pause");
    return 0;
}