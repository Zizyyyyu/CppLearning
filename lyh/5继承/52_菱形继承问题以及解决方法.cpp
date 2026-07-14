#include <iostream>
#include <string>
using namespace std;

// 动物类
class Animal
{
public:
    int m_a;
};

// 羊类
class Sheep : public Animal
{
};

// 驼类
class Tuo : public Animal
{
};

// 羊驼类
class Sheeptuo : public Sheep, public Tuo
{
};

void test1()
{
    Sheeptuo st;

    st.Sheep::m_a = 18;
    st.Tuo::m_a = 28;

    // 当菱形继承，两个父类拥有相同数据，需要加以作用域区分
    //  cout << "st.m_a = " << st.m_a << endl;   //不明确
    cout << "st.Sheep::m_a = " << st.Sheep::m_a << endl;
    cout << "st.Tuo::m_a = " << st.Tuo::m_a << endl;
}

int main()
{

    test1();

    system("pause");

    return 0;
}