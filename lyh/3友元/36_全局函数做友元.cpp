#include <iostream>
#include <string>
using namespace std;

// 建筑物类
class Building
{

    /////////////////////////////////////////////////////////////////////////////////
    // goodGay全局函数是 Building 好朋友，可以访问 Building 中私有成员
    friend void goodGay(Building *building);
    /////////////////////////////////////////////////////////////////////////////////

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

// 全局函数goodGay
void goodGay(Building *building)
{
    // 可以访问公共属性
    cout << "好基友全局函数 正在访问：" << building->m_SittingRoom << endl;

    // 加入友元后，现在可以访问私有属性
    cout << "好基友全局函数 正在访问：" << building->m_BedRoom << endl;
}

void test01()
{
    Building b;  // 实例化一个 建筑对象p
    goodGay(&b); // 调用test1
}

int main()
{

    test01();

    system("pause");

    return 0;
}