#include <iostream>
#include <string>
using namespace std;

// 1. 先告诉编译器：有 Building 这么个类（向前声明）
class Building;

// 2. 定义 GoodGay 类，但【不要】在类内部实现函数体
class GoodGay
{
public:
    GoodGay();     // 只声明构造函数
    void visit();  // 只声明 visit
    void visit2(); // 只声明 visit2

    Building *building;
};

// 3. 此时 GoodGay 已经定义好了，编译器知道它有哪些成员函数了。
//    现在可以完整定义 Building 类，并绑定友元了。
class Building
{
    ////////////////////////////////////////////////////
    // 语法修正：必须带上括号 ()
    friend void GoodGay::visit();
    ////////////////////////////////////////////////////

public:
    Building()
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }

public:
    string m_SittingRoom; // 客厅

private:
    string m_BedRoom; // 卧室
};

// 4. 最后：在类外面，实现 GoodGay 的各个成员函数
//    因为此时 Building 的结构也完整了，可以自由访问它的成员了。

GoodGay::GoodGay()
{
    building = new Building; // 此时编译器知道 Building 如何 new 了
    cout << "GoodGay的构造函数" << endl;
}

void GoodGay::visit()
{
    cout << "visit 正在访问：" << building->m_SittingRoom << endl;
    // 因为是友元，成功访问私有成员！
    cout << "visit 正在访问（私有）：" << building->m_BedRoom << endl;
}

void GoodGay::visit2()
{
    cout << "visit2 正在访问：" << building->m_SittingRoom << endl;

    // 【注意】如果你取消下面这行的注释，编译器会立刻报错！
    // 因为 visit2 不是 Building 的友元，无法访问私有成员 m_BedRoom。
    // 这正好达到了你“让 visit2 无法访问私有成员”的目的。

    // cout << "visit2 正在访问：" << building->m_BedRoom << endl;
}

void test01()
{
    GoodGay gg;
    gg.visit();
    gg.visit2(); // 测试 visit2
}

int main()
{
    test01();
    system("pause");
    return 0;
}