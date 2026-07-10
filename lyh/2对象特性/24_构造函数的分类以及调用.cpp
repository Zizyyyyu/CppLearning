#include <iostream>
using namespace std;

//构造函数的分类
//按照参数分类：   无参构造（默认构造） 和   有参构造
//按照类型分类：   普通构造            和   拷贝构造
class Person
{
    int age;

public:
    Person()
    {
        cout << "Person 无参构造函数的调用" << endl;
    }

    Person(int a)
    {
        cout << "Person 有参构造函数的调用" << endl;
    }

    //拷贝构造函数
    Person(const Person&p){
        //将传入的人身上的所有属性，拷贝到我身上
        age = p.age;
        cout << "Person 拷贝构造函数的调用" << endl;
    }
    ~Person()
    {
        cout << "Person 析构函数的调用" << endl;
    }
};


void test1()
{
    //1、括号法
    Person p;       // 默认构造函数的调用
    Person p2(10);  //有参构造函数
    Person p3(p2);  //拷贝构造函数
    //2、显示法
}

int main()
{

    test1();

    system("pause");
    return 0;
}