#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person
{
public:
    char m_Name[64];
    int m_Age;
};

void test01()
{

    // 2、创建输出流对象
    ifstream ifs("person.txt", ios::in | ios::binary);

    // 3、校验文件是否打开
    if (!ifs.is_open())
    {
        cout << "文件没打开喵" << endl;
    }

    // 4、准备空对象接收数据
    Person p;
    //(char *)是将 对象p 的地址强制转化为 字节指针
    ifs.read((char *)(&p), sizeof(p)); // 别管什么 Person 类了，从现在起，它就是一堆无意义的字节。你顺着这个字节指针，闭着眼睛往后数 sizeof(p) 个字节，全部给我读出来！

    //打印出来
    cout << "姓名是" << p.m_Name << endl;
    cout << "年龄是" << p.m_Age << endl;
}

int main()
{

    test01();

    system("pause");

    return 0;
}