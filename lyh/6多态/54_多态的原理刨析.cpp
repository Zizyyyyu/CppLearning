#include <iostream>
#include <string>
using namespace std;

//普通写法
class Calculator{
public:
    int getResult(string op){
        if(op=="+"){
            return m_n1 + m_n2;
        }
        else if(op=="-"){
            return m_n1 - m_n2;
        }
        else if (op == "*")
        {
            return m_n1 * m_n2;
        }
        else if (op == "/")
        {
            return m_n1 / m_n2;
        }
        //此时弊端就出现了
        //如果想要继续扩展新的操作，那么还需要修改源码，继续增加代码，这样不如多态好
        //在真实的开发中，我们提倡一种  开闭原则
        //开闭原则：对扩展进行开发，对修改进行关闭
    }

    int m_n1, m_n2;
};

//利用多态实现计算机
//实现计算机抽象类
class AbstractCaculator{
public:
    virtual int getResult(){
        return 0;
    }
    int m_n1, m_n2;
};

//加法计算器类
class AddCalculator:public AbstractCaculator{
public:
    int getResult(){
        return m_n1 + m_n2;
    }
};

//减法计算机类
class SubCalculator : public AbstractCaculator
{
public:
    int getResult()
    {
        return m_n1 - m_n2;
    }
};

class MulCalculator : public AbstractCaculator
{
public:
    int getResult()
    {
        return m_n1 * m_n2;
    }
};



void test1(){
    //创建一个计算机对象
    Calculator c;
    c.m_n1 = 10;
    c.m_n2 = 20;
    cout << c.m_n1 << " + " << c.m_n2 << " = " << c.getResult("+") << endl;
    cout << c.m_n1 << " - " << c.m_n2 << " = " << c.getResult("-") << endl;
    cout << c.m_n1 << " * " << c.m_n2 << " = " << c.getResult("*") << endl;
}

void test2(){
    //多态使用条件
    //父类指针或者引用指向子类对象
    AbstractCaculator *abs = new AddCalculator; //由父类指针abs指向子类加法对象
    abs->m_n1 = 10;
    abs->m_n2 = 10;

    cout << abs->m_n1 << " + " << abs->m_n2 << " = " << abs->getResult() << endl;
}

int main()
{
    // test1();
    test2();

    system("pause");

    return 0;
}