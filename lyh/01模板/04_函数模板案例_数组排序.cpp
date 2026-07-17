#include <iostream>
using namespace std;


//从大到小开始排序  选择排序

//交换函数模板
template<class T>
void mySwap(T &a, T&b){
    T temp = a;
    a = b;
    b = temp;
}

//排序算法
template <class T>
void mySort(T arr[], int len){
    for (int i = 0; i < len;i++){
        int max = i;    //认定最大值下标
        for (int j = i + 1; j < len;j++){
            if(arr[max]<arr[j]){
                //认定的最大值比遍历到的数值小，说明j下标的元素是真正的最大值
                max = j;    //更新最大值下标
            }
        }
        if(max!=i){
            //最大值下标发生移动，此时应该进行交换
            mySwap(arr[max], arr[i]);
        }
    }
}

//打印数组模板
template<class T>
void printArray(T arr[], int len){
    for (int i = 0; i < len;i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void test1(){
    //测试char数组
    char charArr[] = "badcfe";
    int num = sizeof(charArr) / sizeof(charArr[0])-1;
    mySort(charArr, num);
    printArray(charArr, num);


    //测试int 数组
    int intArr[] = {7, 5, 1, 3, 54, 5, 6, 7, 32, 3};
    int num1 = sizeof(intArr) / sizeof(intArr[0]);
    mySort(intArr, num1);
    printArray(intArr, num1);
}
int main(){

    test1();
    system("pause");
    return 0;
}