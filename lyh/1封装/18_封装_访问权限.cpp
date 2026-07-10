#include <iostream>
using namespace std;

class Person
{
public:     //公共权限
    string m_name;    //姓名

protected:  //保护权限
    string m_car;     //汽车

private:    //私有权限
    int m_password;    //银行卡密码


public: 
    //类内可以访问公共权限、保护权限、私有权限内容
    void func()
    {
        m_name = "张三";
        m_car = "拖拉机";
        m_password = 123456;
    }
};
int main()
{

    //实例化具体对象
    Person p1;

    p1.m_name="李四";
    //p1.m_car = "奔驰";      // 类外访问不到保护权限内容
    //p1.m_password = 123;    //类外访问，访问不到私有权限内容

    system("pause");
    return 0;
}