#include <fstream>
#include <string>
using namespace std;

class Person
{
public:
    char m_Name[64];
    int m_Age;
};

// 二进制文件  写文件
void test01()
{
    // 1、包含头文件

    // 2、创建输出流对象的时， 打开文件
    ofstream ofs("person.txt", ios::out | ios::binary);

    // 3、打开文件
    // ofs.open("person.txt", ios::out | ios::binary);

    Person p = {"张三", 18};

    // 4、写文件
    // &p 是 对象p 的地址，也就是一个指针指向了类
    // 但是 write 的第一个参数要求必须是 字节指针，就是一个指针指向一个字节
    // 所以需要用 (const char *) 强制将 对象指针 转换为 字节指针
    ofs.write((const char *)&p, sizeof(p));

    // 5、关闭文件
    ofs.close();
}

int main()
{

    test01();

    system("pause");

    return 0;
}