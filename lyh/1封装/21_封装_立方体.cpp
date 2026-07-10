#include <iostream>
using namespace std;

class Cube
{
public:
    //属性
    int m_L;
    int m_H;
    int m_W;

    //行为
    int S(){
        return (m_L * m_H + m_L * m_W + m_W * m_H) * 2;
    }

    int V(){
        return m_L * m_W * m_L;
    }
};

int main()
{
    Cube C;
    C.m_H = 1;
    C.m_L = 1;
    C.m_W = 1;
    cout << C.S() << endl;
    cout << C.V() << endl;

    system("pause");
    return 0;
}