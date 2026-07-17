#include <iostream>
using namespace std;

//类模板
template<class NameType, class AgeType>
class Person{
public : 
    Person(NameType name, AgeType age){
        this->m_Name = name;
        this->m_Age = age;
    }

    void showPerson(){
        cout << "name: " << m_Name << endl;
    }

    NameType m_Name;
    AgeType m_Age;
};

void test1()
{
    //利用类模板创建对象
    Person<string, int> p1("孙悟空", 999);
    p1.showPerson();
}

int main()
{

    test1();
    system("pause");
    return 0;
}