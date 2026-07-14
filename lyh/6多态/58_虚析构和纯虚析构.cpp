#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal 构造函数调用" << endl;
    }

    // 纯虚函数
    virtual void speak()
    {
        cout << "动物在说话" << endl;
    }

    // 利用虚析构可以解决 父类指针释放子类对象时不干净的问题
    //  virtual ~Animal()
    //  {
    //      cout << "Animal 虚析构函数调用" << endl;
    //  }

    // 纯虚析构  需要声明也需要实现
    // 有了纯虚析构之后，这个类也属于抽象类，无法实例化对象
    virtual ~Animal() = 0;
};
// 纯虚析构函数一定要在类外实现吗
Animal::~Animal()
{
    cout << "Animal 纯虚析构函数调用" << endl;
}

class cat : public Animal
{
public:
    cat(string name)
    {
        cout << "cat 构造函数调用" << endl;
        m_Name = new string(name);
    }

    // 子类可写可不写virtual
    virtual void speak()
    {
        cout << *m_Name << "小猫在说话" << endl;
    }

    ~cat()
    {
        if (m_Name != NULL)
        {
            cout << "cat 析构函数调用" << endl;
            delete m_Name;
            m_Name = NULL;
        }
    }

    string *m_Name;
};

void test01()
{
    Animal *ani = new cat("Tom");
    ani->speak();
    // 父类指针在析构时 不会调用子类中析构函数，导致子类如果有堆区属性，出现内存泄漏情况
    // 解决方法，将父类的析构改为虚析构
    delete ani;
}

int main()
{

    test01();

    system("pause");

    return 0;
}