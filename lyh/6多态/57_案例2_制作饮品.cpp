#include <iostream>
#include <string>
using namespace std;

// 制作饮品
class AbstractDrinking
{
public:
    // 煮水
    virtual void Boil() = 0;

    // 冲泡
    virtual void Brew() = 0;

    // 倒入杯子中
    virtual void Pourcup() = 0;

    // 加入辅料
    virtual void PutSomething() = 0;

    // 制作饮品
    void makeDrink()
    {
        Boil();
        Brew();
        Pourcup();
        PutSomething();
    }
};

// 制作咖啡
class coffee : public AbstractDrinking
{
    // 煮水
    virtual void Boil()
    {
        cout << "煮水" << endl;
    };

    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡咖啡" << endl;
    };

    // 倒入杯子中
    virtual void Pourcup()
    {
        cout << "倒入杯子中" << endl;
    };

    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入糖和牛奶" << endl;
    };
};

// 制作茶
class tea : public AbstractDrinking
{
    // 煮水
    virtual void Boil()
    {
        cout << "煮山泉水" << endl;
    };

    // 冲泡
    virtual void Brew()
    {
        cout << "冲泡茶叶" << endl;
    };

    // 倒入杯子中
    virtual void Pourcup()
    {
        cout << "倒入杯子中" << endl;
    };

    // 加入辅料
    virtual void PutSomething()
    {
        cout << "加入红枣" << endl;
    };
};

// 制作函数
void doWork(AbstractDrinking *abs)
{
    abs->makeDrink(); // 一个接口有多种形态
    delete abs;       // 释放堆区数据
}

void test01()
{
    doWork(new coffee);

    // doWork(new tea);
}

int main()
{

    test01();

    system("pause");

    return 0;
}