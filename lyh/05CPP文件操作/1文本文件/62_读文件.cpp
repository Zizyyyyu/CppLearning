#include <iostream>
#include <fstream>
using namespace std;

// 文本文件 写文件
void test1()
{
    // 1、包含头文件 fstream

    // 2、创建流对象
    ifstream ifs;

    // 3、指定打开方式,并判断是否打开成功
    ifs.open("test.txt", ios::in);

    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }

    // 4、读内容
    // 法一
    // char buf[1024] = {0};
    // while(ifs>>buf){
    //     cout << buf << endl;
    // }

    // 法二
    // char buf[1024] = {0};
    // while (ifs.getline(buf, sizeof(buf)))
    // {
    //     cout << buf << endl;
    // }

    // 法三
    string buf;
    // 全局函数 getline(流对象, string对象)
    while (getline(ifs, buf))
    {
        cout << buf << endl;
    }
    // 5、关闭文件
    ifs.close();
}

int main()
{

    test1();

    system("pause");
    return 0;
}