#include <iostream>
#include <string>
using namespace std;

// 打印输出类
class MyPrint
{
public:
    // 重载函数调用运算符
    void operator()(string test)    //返回void
    {
        cout << test << endl;
    }
};

void test01()
{
    // 重载的（）操作符 也称为仿函数
    MyPrint myFunc;
    myFunc("hello world");  //hello world 传给了 string test
}

//仿函数非常灵活
class MyAdd
{
public:
    int operator()(int v1, int v2)  //返回int
    {
        return v1 + v2;
    }
};

void test02()
{
    MyAdd add;
    int ret = add(10, 10);
    cout << "ret = " << ret << endl;

    // 匿名对象调用， MyAdd()是匿名对象
    cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main()
{

    test01();
    test02();

    system("pause");

    return 0;
}