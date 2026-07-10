#include <iostream>
using namespace std;

//struct 的默认权限是 公共权限 public
//class 的默认权限是 私有权限 private

class S1{
    int a;      // 私有权限 private
};

struct S2{
    int a;      //公共权限 public
};

int main()
{

    S1 s1;
    //s1.a = 100;    // 错误， 类外不能访问私有权限
    
    S2 s2;
    s2.a = 100;      //正确， 类外可以访问公有权限

    system("pause");
    return 0;
}