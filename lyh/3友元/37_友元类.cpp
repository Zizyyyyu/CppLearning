#include <iostream>
#include <string>
using namespace std;

// 建筑物类
class Building
{
    ////////////////////////////////////////////////////
    friend class GoodGay; // 友元类，是的 GoodGay类 可以访问 Building类 的私有权限
    ////////////////////////////////////////////////////

public:
    Building() // Building类 的构造函数
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }

public:
    string m_SittingRoom; // 客厅

private:
    string m_BedRoom; // 卧室
};

// 好朋友类
class GoodGay
{
public:
    // GoodGay的构造函数
    GoodGay()
    {
        // 创建建筑物对象
        building = new Building;
        // 你的理解完全正确：
        // 1、申请内存：在内存的堆区动态开辟空间。
        // 2、初始化对象：自动调用 Building 的构造函数。
        // 3、传递地址：new 返回首地址。
        // 4、指针接收：赋值给 building 指针。

        cout << "GoodGay的构造函数" << endl;
    }

    void visit()
    {
        cout << "好基友类正在访问：" << building->m_SittingRoom << endl;

        // 没加友元是访问不了卧室类的，因为卧室是 Building类 的私有权限
        cout << "好基友类正在访问：" << building->m_BedRoom << endl;
    }

    Building *building; // 类对象的指针作为类成员
    // GoodGay 对象内部只保存了一个 8 字节（或 4 字节）的地址。真正的 Building 房子在堆区，需要你手动 new 才会创建。
};

void test01()
{
    GoodGay gg; // 实例化对象
    gg.visit();
}

int main()
{
    test01();

    system("pause");
    return 0;
}