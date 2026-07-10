# C++核心编程

本阶段主要针对C++==面向对象==编程技术做详细讲解，探讨C++中的核心和精髓。



## 1 内存分区模型

C++程序在执行时，将内存大方向划分为**4个区域**

- 代码区：存放函数体的二进制代码，由操作系统进行管理的
- 全局区：存放全局变量和静态变量以及常量
- 栈区：由编译器自动分配释放, 存放函数的参数值,局部变量等
- 堆区：由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收

<img src="https://s2.51cto.com/oss/202606/25/34cce52143d66222e43883ae74cbc6f179628a.jpg" alt="图片" style="zoom:150%;" />



**内存四区意义：**

不同区域存放的数据，赋予不同的生命周期, 给我们更大的灵活编程





### 1.1 程序运行前

​	在程序编译后，生成了exe可执行程序，**未执行该程序前**分为两个区域

​	**代码区：**

​		存放 CPU 执行的机器指令

​		代码区是**共享**的，共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可

​		代码区是**只读**的，使其只读的原因是防止程序意外地修改了它的指令

​	**全局区：**

​		**全局变量**和**静态变量**存放在此.

​		全局区还包含了**常量区**, 字符串常量和其他常量也存放在此.

​		==该区域的数据在程序结束后由操作系统释放==.



**示例：**

```c++
//全局变量
int g_a = 10;
int g_b = 10;

//全局常量
const int c_g_a = 10;
const int c_g_b = 10;

int main() {

	//局部变量
	int a = 10;
	int b = 10;

	//打印地址
	cout << "局部变量a地址为： " << (int)&a << endl;
	cout << "局部变量b地址为： " << (int)&b << endl;

	cout << "全局变量g_a地址为： " <<  (int)&g_a << endl;
	cout << "全局变量g_b地址为： " <<  (int)&g_b << endl;

	//静态变量
	static int s_a = 10;
	static int s_b = 10;

	cout << "静态变量s_a地址为： " << (int)&s_a << endl;
	cout << "静态变量s_b地址为： " << (int)&s_b << endl;

	cout << "字符串常量地址为： " << (int)&"hello world" << endl;
	cout << "字符串常量地址为： " << (int)&"hello world1" << endl;

	cout << "全局常量c_g_a地址为： " << (int)&c_g_a << endl;
	cout << "全局常量c_g_b地址为： " << (int)&c_g_b << endl;

	const int c_l_a = 10;
	const int c_l_b = 10;
	cout << "局部常量c_l_a地址为： " << (int)&c_l_a << endl;
	cout << "局部常量c_l_b地址为： " << (int)&c_l_b << endl;

	system("pause");

	return 0;
}
```

打印结果：

![1545017602518](assets/1545017602518.png)



总结：

* C++中在程序运行前分为全局区和代码区
* 代码区特点是共享和只读
* 全局区中存放全局变量、静态变量、常量
* 常量区中存放 const修饰的全局常量  和 字符串常量






### 1.2 程序运行后



​	**栈区：**

​		由编译器自动分配释放, 存放函数的参数值,局部变量等

​		注意事项：不要返回局部变量的地址，栈区开辟的数据由编译器自动释放



**示例：**

```c++
int * func()
{
	int a = 10;
	return &a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;

	system("pause");

	return 0;
}
```







​	**堆区：**

​		由程序员分配释放,若程序员不释放,程序结束时由操作系统回收

​		在C++中主要利用new在堆区开辟内存

**示例：**

```c++
int* func()
{
	int* a = new int(10);
	return a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;
    
	system("pause");

	return 0;
}
```



**总结：**

堆区数据由程序员管理开辟和释放

堆区数据利用new关键字进行开辟内存









### 1.3 new操作符



​	C++中利用==new==操作符在堆区开辟数据

​	堆区开辟的数据，由程序员手动开辟，手动释放，释放利用操作符 ==delete==

​	语法：` new 数据类型`

​	利用new创建的数据，会返回该数据对应的类型的指针



**示例1： 基本语法**

```c++
int* func()
{
	int* a = new int(10);
	return a;
}

int main() {

	int *p = func();

	cout << *p << endl;
	cout << *p << endl;

	//利用delete释放堆区数据
	delete p;

	//cout << *p << endl; //报错，释放的空间不可访问

	system("pause");

	return 0;
}
```



**示例2：开辟数组**

```c++
//堆区开辟数组
int main() {

	int* arr = new int[10];

	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}

	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	//释放数组 delete 后加 []
	delete[] arr;

	system("pause");

	return 0;
}

```











## 2 引用

### 2.1 引用的基本使用

**作用： **给变量起别名

**语法：** `数据类型 &别名 = 原名`



**示例：**

```C++
int main() {

	int a = 10;
	int &b = a;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	b = 100;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

	system("pause");

	return 0;
}
```







### 2.2 引用注意事项

* 引用必须初始化
* 引用在初始化后，不可以改变

示例：

```C++
int main() {

	int a = 10;
	int b = 20;
	//int &c; //错误，引用必须初始化
	int &c = a; //一旦初始化后，就不可以更改
	c = b; //这是赋值操作，不是更改引用

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;

	system("pause");

	return 0;
}
```











### 2.3 引用做函数参数

**作用：**函数传参时，可以利用引用的技术让形参修饰实参

**优点：**可以简化指针修改实参



**示例：**

```C++
//1. 值传递
void mySwap01(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

//2. 地址传递
void mySwap02(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//3. 引用传递
void mySwap03(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main() {

	int a = 10;
	int b = 20;

	mySwap01(a, b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap02(&a, &b);
	cout << "a:" << a << " b:" << b << endl;

	mySwap03(a, b);
	cout << "a:" << a << " b:" << b << endl;

	system("pause");

	return 0;
}

```



> 总结：通过引用参数产生的效果同按地址传递是一样的。引用的语法更清楚简单













### 2.4 引用做函数返回值

作用：引用是可以作为函数的返回值存在的



注意：**不要返回局部变量引用**

用法：函数调用作为左值

**示例：**

```C++
//返回局部变量引用
int& test01() {
	int a = 10; //局部变量
	return a;
}

//返回静态变量引用
int& test02() {
	static int a = 20;
	return a;
}

int main() {

	//不能返回局部变量的引用
	int& ref = test01();
	cout << "ref = " << ref << endl;
	cout << "ref = " << ref << endl;

	//如果函数做左值，那么必须返回引用
	int& ref2 = test02();
    
    //1、test2() 执行，内部的静态变量 a 诞生（并在程序运行期间一直存活）。
	//2、test2() 结束并返回，它把 a 的引用交了出来。
	//3、int &ref = ... 承接了这个引用。
    //4、结果： ref 在这里正式成为了 a 的别名。它们俩现在指向同一块内存空间。
    
	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	test02() = 1000;		//在编译器眼中，这段代码等同于  a = 1000

	cout << "ref2 = " << ref2 << endl;
	cout << "ref2 = " << ref2 << endl;

	system("pause");

	return 0;
}
```



#### 2.4.1. 普通返回（传值）：`int test2()`

如果去掉 `&`，代码变成这样：

```C++
int test2() {
    static int a = 10;
    return a; 
}
```

当你 `return a;` 时，系统会临时开辟一个匿名的内存空间，把 `a` 的值（10）**复制**一份丢出来。你外面拿到的只是一个“复印件”，改动它不会影响到原件 `a`。

#### 2.4.2. 引用返回（传引用）：`int& test2()`

```C++
int& test2() {
    static int a = 10;
    return a; 
}
```

当函数的返回类型是 `int&` 时，C++ 编译器在幕后做了一件事：它不再复制 `a` 的值，而是直接把 `a` 的内存地址（控制权）交了出去。此时，**函数调用表达式 `test2()` 本身，就变成了 `a` 的一个临时别名**。

​	









### 2.5 引用的本质

本质：**引用的本质在c++内部实现是一个指针常量.**

讲解示例：

```C++
//发现是引用，转换为 int* const ref = &a;
void func(int& ref){
	ref = 100; // ref是引用，转换为*ref = 100
}
int main(){
	int a = 10;
    
    //自动转换为 int* const ref = &a; 指针常量是指针指向不可改，也说明为什么引用不可更改
	int& ref = a; 
	ref = 20; //内部发现ref是引用，自动帮我们转换为: *ref = 20;
    
	cout << "a:" << a << endl;
	cout << "ref:" << ref << endl;
    
	func(a);
	return 0;
}
```

结论：C++推荐用引用技术，因为语法方便，引用本质是指针常量，但是所有的指针操作编译器都帮我们做了





#### 2.5.1 什么是“指针常量”

```c++
int a = 10;
int b = 20;

int * const p = &a; // 这就是一个指针常量
```

特点

- **指向不能变（引用一旦初始化就不能更改）：** `const` 紧跟在指针名 `p` 前面，意味着 `p` 内部存的地址一旦初始化就**死死锁定了**，你不能再让 `p = &b;`。
- **指向的内容可变：** 虽然不能换房，但你可以换房里的家具。你可以通过 `*p = 100;` 来修改 `a` 的值。









### 2.6 常量引用



**作用：**常量引用主要用来修饰形参，防止误操作



在函数形参列表中，可以加==const修饰形参==，防止形参改变实参



**示例：**

==const未修饰==

```C++
#include <iostream>
using namespace std;
//常量引用
//使用场景：用来修饰形参，防止误操作

//打印操作
void showValue(int &val)
{
    val = 1000;     //误操作修改形参
    cout << "val = " << val << endl;
}


int main()
{
    int a = 10;
    showValue(a);		//由于第 7 行误操作，会导致打印错误

    system("pause");
    return 0;
}
```



==const修饰==

```C++
#include <iostream>
using namespace std;
//常量引用
//使用场景：用来修饰形参，防止误操作，在引用形参前加上const
void showValue(const int &val)
{
    //val = 1000;     //误操作修改形参
    cout << "val = " << val << endl;
}


int main()
{

    int a = 10;
    showValue(a);	

    system("pause");
    return 0;
}
```







## 3 函数提高

### 3.1 函数默认参数



在C++中，函数的形参列表中的形参是可以有默认值的。

语法：` 返回值类型  函数名 （参数= 默认值）{}`



**示例：**

```C++
#include <iostream>
using namespace std;

// 函数默认参数
int func(int a, int b = 20, int c = 30)
{
    return a + b + c;
}

int main()
{

    //自己传入数据，就用自己的数据，如果没有，那么用默认值

    cout << "传入一个参数：" << endl;
    cout << func(10) << endl;

    cout << "传入两个参数：" << endl;
    cout << func(10, 30) << endl;

    system("pause");
    return 0;
}
```





> [!CAUTION]
>
> 注意：如果某个位置已经有了默认参数，那么从这个位置往后，从左到右都必须有默认值
>

```c++
//报错！因为 b 有默认参数，但是 c 没有默认参数
int func(int a, int b = 10, int c)
{
	return a + b + c;
}
```





> [!CAUTION]
>
> 注意：如果函数声明有默认参数，函数实现就不能有默认参数

```C++
以下代码会报错

//2、函数声明有默认参数，函数实现就不能有默认参数
//声明和实现只能有一个有默认参数

//函数声明，有默认参数
int func2(int a = 10, int b = 10);

//函数实现，有默认参数
int func2(int a = 10, int b = 10)
{
    return a + b;
}
```



### 3.2 函数占位参数



C++中函数的形参列表里可以有占位参数，用来做占位，调用函数时必须填补该位置



**语法：** `返回值类型 函数名 (数据类型){}`



在现阶段函数的占位参数存在意义不大，但是后面的课程中会用到该技术



**示例：**

```C++
//函数占位参数 ，占位参数也可以有默认参数
//第二个参数就是占位参数
void func(int a, int) {
	cout << "this is func" << endl;
}

int main() {

	func(10,10); //占位参数必须填补

	system("pause");

	return 0;
}

```



> [!IMPORTANT]
>
> 占位参数也可以有默认参数





### 3.3 函数重载

#### 3.3.1 函数重载概述



**作用：**函数名可以相同，提高复用性



**函数重载满足条件：**

* 同一个作用域下
* 函数名称相同
* 函数参数**类型不同**  或者 **个数不同** 或者 **顺序不同**



**示例：**

```C++
//函数重载需要函数都在同一个作用域下
void func()
{
	cout << "func 的调用！" << endl;
}
void func(int a)
{
	cout << "func (int a) 的调用！" << endl;
}
void func(double a)
{
	cout << "func (double a)的调用！" << endl;
}
void func(int a ,double b)
{
	cout << "func (int a ,double b) 的调用！" << endl;
}
void func(double a ,int b)
{
	cout << "func (double a ,int b)的调用！" << endl;
}


int main() {

	func();
	func(10);
	func(3.14);
	func(10,3.14);
	func(3.14 , 10);
	
	system("pause");

	return 0;
}
```



> [!CAUTION]
>
> **注意:**  函数的返回值不可以作为函数重载的条件

```c++
//函数返回值不可以作为函数重载条件
//根本原因：编译器在调用函数时，无法仅仅根据返回值类型来决定调用哪个版本。 这会产生歧义。

//如果出现以下代码，参数列表相同但是返回值类型不同，这是错误的函数重载

int func(double a, int b)
{
	cout << "func (double a ,int b)的调用！" << endl;
}

void func(double a ,int b)
{
	cout << "func (double a ,int b)的调用！" << endl;
}
```





#### 3.3.2 函数重载注意事项



* 引用作为重载条件
* 函数重载碰到函数默认参数



1. 引用作为重载条件

```c++
//函数重载注意事项
//1、引用作为重载条件

void func(int &a)
{
	cout << "func (int &a) 调用 " << endl;
}

void func(const int &a)
{
	cout << "func (const int &a) 调用 " << endl;
}

int main() {
	
	int a = 10;
	func(a); //调用无const
	func(10);//调用有const
    //因为 int &a = 10 不合法
    //const int &a = 10 合法

	system("pause");

	return 0;
}
```





函数重载碰到函数默认参数

```C++
//2、函数重载碰到函数默认参数
void func2(int a, int b = 10)
{
	cout << "func2(int a, int b = 10) 调用" << endl;
}

void func2(int a)
{
	cout << "func2(int a) 调用" << endl;
}

int main() {
	
    //第一个 func2 和 第二个 func2 都可以调用
	func2(10); //碰到默认参数产生歧义，需要避免

	system("pause");

	return 0;
}
```







## **4** 类和对象



C++面向对象的三大特性为：==封装、继承、多态==



C++认为==万事万物都皆为对象==，对象上有其属性和行为





类的组成概念

- 类是由**属性**（数据）和**行为**（功能）组成的，把它们统称为**成员**；
- 属性对应的具体项叫**成员变量/成员属性**
- 行为对应的具体项叫**成员方法/成员函数**





**例如：**

​	人可以作为对象，属性有姓名、年龄、身高、体重...，行为有走、跑、跳、吃饭、唱歌...

​	车也可以作为对象，属性有轮胎、方向盘、车灯...,行为有载人、放音乐、放空调...

​	具有相同性质的==对象==，我们可以抽象称为==类==，人属于人类，车属于车类

### 4.1 封装

#### 4.1.1  封装的意义

封装是C++面向对象三大特性之一

封装的意义：

* 将属性和行为作为一个整体，表现生活中的事物
* 将属性和行为加以权限控制



**封装意义一：**

​	在设计类的时候，属性和行为写在一起，表现事物

**语法：** `class 类名{   访问权限： 属性  / 行为  };`



**示例1：**设计一个圆类，求圆的周长

**示例代码：**

```C++
//圆周率
const double PI = 3.14;

//1、封装的意义
//将属性和行为作为一个整体，用来表现生活中的事物

//封装一个圆类，求圆的周长
//class代表设计一个类，后面跟着的是类名
class Circle
{
public:  //访问权限  公共的权限

	//属性
	int m_r;//半径

	//行为
	//获取到圆的周长
	double calculateZC()
	{
		//2 * pi  * r
		//获取圆的周长
		return  2 * PI * m_r;
	}
};

int main() {

	//通过圆类，创建圆的对象
	// c1就是一个具体的圆
	Circle c1;
	c1.m_r = 10; //给圆对象的半径 进行赋值操作

	//2 * pi * 10 = = 62.8
	cout << "圆的周长为： " << c1.calculateZC() << endl;

	system("pause");

	return 0;
}
```





**示例2：**设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号



**示例2代码：**

```C++
#include <iostream>
using namespace std;
//设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号

class Student{
public:     //公共权限

    //属性
    string m_name;  //姓名
    int m_id;       //学号


    //行为
    void showStudent(){
        cout << "姓名：" << m_name << endl;
        cout << "学号：" << m_id << endl;
    }
    
};

int main()
{

    //创建一个具体学生——实例化对象
    Student s1;

    //给 s1 对象 进行属性赋值操作
    s1.m_name = "张三";
    s1.m_id = 1;

    //显示学生信息
    s1.showStudent();

    //////////////////////////////////////////////////////
    // 创建一个具体学生——实例化对象
    Student s2;

    // 给 s2 对象 进行属性赋值操作
    s2.m_name = "李四";
    s2.m_id = 2;

    // 显示学生信息
    s2.showStudent();

    system("pause");
    return 0;
}
```





==行为可以给属性赋值==

```C++
#include <iostream>
using namespace std;
//设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓名和学号

class Student{

public:     //公共权限

    //属性
    string m_name;  //姓名
    int m_id;       //学号


    //行为
    void showStudent(){		//打印出所有属性
        cout << "姓名：" << m_name << endl;
        cout << "学号：" << m_id << endl;
    }
    
    //====通过行为对属性进行赋值操作====
    void setName(string name){
        m_name = name;
    }
};

int main()
{

    //创建一个具体学生——实例化对象
    Student s1;

    s1.setName("张三");     // 通过行为对属性进行赋值操作
    s1.m_id = 1;            // 给 s1 对象 进行属性赋值操作

    //显示学生信息
    s1.showStudent();


    system("pause");
    return 0;
}
```







📝 C++ 三大访问修饰符（Access Specifiers）

在 C++ 中，`public`、`protected` 和 `private` 是用来控制类成员（属性和函数）**访问权限**的关键字。它们决定了谁可以直接使用这些数据，谁被拒之门外，是实现面向对象编程中**封装性**的核心。

##### 一、 三大修饰符详解

###### 1. 🌐 public（公有权限）

- **权限级别**：完全公开。
- **访问范围**：
  - 类内部的成员函数：✅ 可以访问
  - 子类（派生类）内部：✅ 可以访问
  - 类外部（如 `main` 函数中通过对象名）：✅ 可以访问
- **核心用途**：用于提供类的**外部接口**。通常把供外部调用的方法（如构造函数、Getter/Setter 函数）设为 `public`。

###### 2. 🛡️ protected（保护权限）

- **权限级别**：定向对子类公开。
- **访问范围**：
  - 类内部的成员函数：✅ 可以访问
  - 子类（派生类）内部：✅ 可以访问
  - 类外部（通过对象名）：❌ **无法访问**
- **核心用途**：专门为**继承**设计。当你希望某些核心数据或底层工具函数对外部隐藏，但允许自己的“后代”继承并使用时，就使用 `protected`。

###### 3. 🔒 private（私有权限）

- **权限级别**：最高机密，严格限制。
- **访问范围**：
  - 类内部的成员函数：✅ 可以访问
  - 子类（派生类）内部：❌ **无法访问**
  - 类外部（通过对象名）：❌ **无法访问**
- **核心用途**：用于隐藏类的内部实现细节和核心属性。**在 C++ 规范中，通常建议将所有的成员变量（属性）都设为 `private`**，以防止外部代码无意间修改数据。

##### 二、 权限可见性矩阵

在 C++ 中，权限的判断非常纯粹，**只看类与类的关系**（是不是父子类、是不是内部成员），与文件放在哪里没有任何关系。

| **访问修饰符**  | **本类内部成员 (Class)** | **子类内部成员 (Derived)** | **类外部 / 对象直接调用 (Outside)** |
| --------------- | ------------------------ | -------------------------- | ----------------------------------- |
| **`public`**    | ✅ 能访问                 | ✅ 能访问                   | ✅ 能访问                            |
| **`protected`** | ✅ 能访问                 | ✅ 能访问                   | ❌ **不能访问**                      |
| **`private`**   | ✅ 能访问                 | ❌ **不能访问**             | ❌ **不能访问**                      |

##### 三、 C++ 进阶：继承方式对权限的影响（特有考点）

这是 C++ 区别于其他语言（如 Java/C#）的一个重要特性：**C++ 在继承时也可以指定权限**（如 `class Dog : public Animal`）。不同的继承方式会改变基类成员在子类中的最终权限：

- **公有继承 (`public`)**：保持原样。基类的 `public` 在子类还是 `public`，`protected` 还是 `protected`。
- **保护继承 (`protected`)**：降级收紧。基类的 `public` 和 `protected` 在子类中**全部变成 `protected`**。
- **私有继承 (`private`)**：降级闭锁。基类的 `public` 和 `protected` 在子类中**全部变成 `private`**。

> ⚠️ **注意**：无论以什么方式继承，基类中的 `private` 成员在子类中永远是**不可见（无法直接访问）**的。

##### 四、 核心避坑指南与小彩蛋

1. **后门：友元（`friend`）**：
   - 如果你在类内部把某个外部函数或另一个类声明为 `friend`，那么它就获得了最高通行证，可以无视上面的所有规则，直接访问该类的 `private` 和 `protected` 成员。

**示例：**

```C++
//三种权限
//公共权限  public     类内可以访问  类外可以访问
//保护权限  protected  类内可以访问  类外不可以访问
//私有权限  private    类内可以访问  类外不可以访问

class Person
{
	//姓名  公共权限
public:
	string m_Name;

	//汽车  保护权限
protected:
	string m_Car;

	//银行卡密码  私有权限
private:
	int m_Password;

public:
	void func()
	{
		m_Name = "张三";
		m_Car = "拖拉机";
		m_Password = 123456;
	}
};

int main() {

	Person p;
	p.m_Name = "李四";
	//p.m_Car = "奔驰";  //保护权限类外访问不到
	//p.m_Password = 123; //私有权限类外访问不到

	system("pause");

	return 0;
}
```







#### 4.1.2 struct和class区别



**`struct` 与 `class` 的唯一区别**：

- 在 C++ 中，如果你用 `class` 定义类，**默认权限是 private(`私有权限`)**。
- 如果你用 `struct` 定义类，**默认权限是public**（`公有权限`）。



```C++
class C1
{
	int  m_A; //默认是私有权限
};

struct C2
{
	int m_A;  //默认是公共权限
};

int main() {

	C1 c1;
	c1.m_A = 10; //错误，访问权限是私有

	C2 c2;
	c2.m_A = 10; //正确，访问权限是公共

	system("pause");

	return 0;
}
```













#### 4.1.3 成员属性设置为私有

在 C++ 面向对象编程中，将类内部的成员属性（变量）设置为 `private`（私有），是**封装性**的标准实践。外部无法直接访问私有属性，必须通过类提供的 `public` 接口（通常称为 Getter 和 Setter 函数）进行间接操作。



💡 核心优点

1. **精准控制读写权限**：可以自由决定某个属性是“可读可写”、“只读”还是“只写”，对外部隐藏不必要的细节。
2. **保证数据的有效性与安全性（数据过滤）**：在外部尝试修改属性（写权限）时，可以在类内部进行逻辑检测，防止非法数据破坏程序运行。



💻 规范代码示例

```C++
#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    // ==========================================
    // 1. 姓名属性：设置 [可读可写]
    // ==========================================
    // 写权限 (Setter)
    void setName(string name) {
        m_Name = name;
    }
    // 读权限 (Getter)
    string getName() {
        return m_Name;
    }

    // ==========================================
    // 2. 年龄属性：设置 [可读可写 + 过滤验证]
    // ==========================================
    // 读权限 (Getter)
    int getAge() {
        return m_Age;
    }
    // 写权限 (Setter) - 带有有效性检测
    void setAge(int age) {
        if (age < 0 || age > 150) {
            cout << "提示：你个老妖精！输入年龄不合法。" << endl;
            return; // 拦截非法输入，直接退出函数
        }
        m_Age = age;
    }

    // ==========================================
    // 3. 情人属性：设置 [只写]
    // ==========================================
    // 写权限 (Setter) - 不提供 Getter，外部便无法读取
    void setLover(string lover) {
        m_Lover = lover;
    }

private:
    string m_Name;   // 可读可写
    int m_Age;       // 可读可写（带有效性检测）
    string m_Lover;  // 只写
};

int main() {
    Person p;

    // 1. 测试：可读可写（姓名）
    p.setName("张三");
    cout << "姓名： " << p.getName() << endl;

    // 2. 测试：有效性检测（年龄）
    p.setAge(180);   // 触发拦截逻辑
    p.setAge(25);    // 正常赋值
    cout << "年龄： " << p.getAge() << endl;

    // 3. 测试：只写权限（情人）
    p.setLover("系统内置秘密"); 
    // cout << p.m_Lover << endl;  // ❌ 编译报错！无法直接访问 private 成员
    // cout << p.getLover() << endl; // ❌ 编译报错！未定义该类的读函数

    system("pause");
    return 0;
}
```



1. 读写权限的实现公式

在 C++ 中，私有属性的读写完全取决于**公共函数（API）的开放程度**：

- **可读可写**：同时提供 `get函数` 和 `set函数`（如 `m_Name`）。
- **只读（Read-Only）**：**仅**提供 `get函数`，不写 `set函数`。
- **只写（Write-Only）**：**仅**提供 `set函数`，不写 `get函数`（如 `m_Lover`）。





**练习案例1：设计立方体类**

设计立方体类(Cube)

求出立方体的面积和体积

分别用全局函数和成员函数判断两个立方体是否相等。



![1545533548532](assets/1545533548532.png)











**练习案例2：点和圆的关系**

设计一个圆形类（Circle），和一个点类（Point），计算点和圆的关系。



![1545533829184](assets/1545533829184.png)







### 4.2 对象的初始化和清理



*  生活中我们买的电子产品都基本会有出厂设置，在某一天我们不用时候也会删除一些自己信息数据保证安全
*  C++中的面向对象来源于生活，每个对象也都会有初始设置以及 对象销毁前的清理数据的设置。





#### 4.2.1 构造函数和析构函数

对象的**初始化和清理**也是两个非常重要的安全问题

​	一个对象或者变量没有初始状态，对其使用后果是未知

​	同样的使用完一个对象或变量，没有及时清理，也会造成一定的安全问题



c++利用了**构造函数**和**析构函数**解决上述问题，这两个函数将会被编译器自动调用，完成对象初始化和清理工作。

对象的初始化和清理工作是编译器强制要我们做的事情，因此如果**我们不提供构造和析构，编译器会提供**

**编译器提供的构造函数和析构函数是空实现。**



* 构造函数：主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。
* 析构函数：主要作用在于对象**销毁前**系统自动调用，执行一些清理工作。





**构造函数语法：**`类名(){}`

1. 构造函数，没有返回值也不写void
2. 函数名称与类名相同
3. 构造函数可以有参数，因此可以发生重载
4. 程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次





**析构函数语法：** `~类名(){}`

1. 析构函数，没有返回值也不写void
2. 函数名称与类名相同,在名称前加上符号  ~
3. 析构函数不可以有参数，因此不可以发生重载
4. 程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次





```C++
class Person
{
public:
	//构造函数
	Person()
	{
		cout << "Person的构造函数调用" << endl;
	}
	//析构函数
	~Person()
	{
		cout << "Person的析构函数调用" << endl;
	}

};

void test01()
{
	Person p;
}

int main() {
	
	test01();

	system("pause");

	return 0;
}
```











#### 4.2.2 构造函数的分类及调用

两种分类方式：

​	按参数分为： 有参构造和无参构造

​	按类型分为： 普通构造和拷贝构造

三种调用方式：

​	括号法

​	显示法

​	隐式转换法



**示例：**

```C++
//1、构造函数分类
// 按照参数分类分为 有参和无参构造   无参又称为默认构造函数
// 按照类型分类分为 普通构造和拷贝构造

class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
	//有参构造函数
	Person(int a) {
		age = a;
		cout << "有参构造函数!" << endl;
	}
	//拷贝构造函数
	Person(const Person& p) {
		age = p.age;
		cout << "拷贝构造函数!" << endl;
	}
	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int age;
};

//2、构造函数的调用
//调用无参构造函数
void test01() {
	Person p; //调用无参构造函数
}

//调用有参的构造函数
void test02() {

	//2.1  括号法，常用
	Person p1(10);
	//注意1：调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
	//Person p2();

	//2.2 显式法
	Person p2 = Person(10); 
	Person p3 = Person(p2);
	//Person(10)单独写就是匿名对象  当前行结束之后，马上析构

	//2.3 隐式转换法
	Person p4 = 10; // Person p4 = Person(10); 
	Person p5 = p4; // Person p5 = Person(p4); 

	//注意2：不能利用 拷贝构造函数 初始化匿名对象 编译器认为是对象声明
	//Person p5(p4);
}

int main() {

	test01();
	//test02();

	system("pause");

	return 0;
}
```









#### 4.2.3 拷贝构造函数调用时机

在 C++ 中，拷贝构造函数（Copy Constructor）是一种特殊的构造函数，它的语法形式为 `Person(const Person& p)`。它的核心核心任务是：**用一个已经存在的对象，去克隆初始化一个即将诞生新对象**。

通常情况下，拷贝构造函数会在以下 **三种经典场景** 下被触发。下面我们将代码拆散，为你逐一深度解析。

##### 🛠️ 准备工作：基础类定义

这是我们用于测试的 `Person` 类结构：

```C++
class Person {
public:
	Person() { cout << "无参构造函数!" << endl; mAge = 0; }
	Person(int age) { cout << "有参构造函数!" << endl; mAge = age; }
	Person(const Person& p) { cout << "拷贝构造函数!" << endl; mAge = p.mAge; }
	~Person() { cout << "析构函数!" << endl; }
	int mAge;
};
```



##### 🔍 三大调用时机详细拆解

###### 时机一：使用一个已经创建完毕的对象来初始化一个新对象

这是最直观、最显式的调用方式。当你创造一个新生命时，明确指定要按照某个现有的“模具”来刻画。

###### 💻 代码拆解：

```C++
void test01() {
	Person man(100);      // 1. 触发有参构造，创建一个已经完毕的对象 man
	Person newman(man);   // 2. 括号法：显式调用拷贝构造函数，创建 newman
	Person newman2 = man; // 3. 显式初始化法：同样调用拷贝构造函数，创建 newman2

	// 【⚠️ 核心避坑点】
	Person newman3;       // 这里触发的是 [无参构造函数]！
	newman3 = man;        // ❌ 注意：这里是“赋值操作”，而不是“初始化”！不会调用拷贝构造。
}
```

> **💡 笔记划重点**
>
> 拷贝构造函数的触发，**必须伴随着“新对象的诞生”**。
>
> - `Person newman2 = man;` 中 `newman2` 之前并不存在，这叫**初始化** $\rightarrow$ 触发拷贝构造。
> - `newman3 = man;` 中 `newman3` 早就诞生了，这叫**对象赋值** $\rightarrow$ 触发的是重载的赋值运算符（`operator=`），不走拷贝构造。



###### 时机二：以值传递的方式给函数参数传值

当对象作为函数的形参，且函数调用时采用**值传递**（不带指针 `*`，也不带引用 `&`）时，系统会自动在函数内部克隆一个副本。



###### 💻 代码拆解：

```C++
// 函数形参是 Person p1，属于值传递
void doWork(Person p1) {} 

void test02() {
	Person p;   // 1. 触发 [无参构造函数]，创建本体 p
	doWork(p);  // 2. 隐式触发 [拷贝构造函数]！
}               // 3. doWork 结束时，临时副本 p1 触发 [析构函数]
                // 4. test02 结束时，本体 p 触发 [析构函数]
```

> **🕵️ 编译器幕后翻译**
>
> 当你执行 `doWork(p)` 时，编译器在跨入函数大门的一瞬间，隐式地在后台执行了：
>
> `Person p1 = p;` （即拿外面的本体 `p` 去初始化里面的形参 `p1`），因此必然触发拷贝构造。



###### 时机三：以值方式返回局部对象（🚨 现代 C++ 必看考点）

在传统的 C++ 理论中，当一个函数返回一个局部对象时，由于局部对象在函数结束时会被销毁，系统必须在后台调用拷贝构造函数，把这个局部对象复制一份“临时对象”传给外面。



###### 💻 代码拆解：

```C++
Person doWork2() {
	Person p1; // 1. 触发 [无参构造函数]
	cout << "函数内 p1 的地址: " << (int *)&p1 << endl;
	return p1; // 2. 理论上：通过拷贝构造，将 p1 克隆给外部的一个临时对象
}

void test03() {
	Person p = doWork2(); // 3. 理论上：再通过一次拷贝构造，把临时对象克隆给 p
	cout << "外部 p 的地址:   " << (int *)&p << endl;
}
```





###### 🚨 现实与理论的冲突：为什么我运行代码没有看到“拷贝构造函数”？

如果你在现代编译器（如 VS2019/VS2022、GCC 7.0 及以上）中直接运行 `test03()`，你会非常震惊地发现：

1. **控制台根本没有打印出“拷贝构造函数！”**
2. **函数内 `p1` 的内存地址和外部 `p` 的内存地址一模一样！**

> **🌟 深度解析：返回值优化（RVO / NRVO）**
>
> 现代 C++ 编译器非常聪明。它发现“在函数里创建 `p1` $\rightarrow$ 拷贝出来 $\rightarrow$ 销毁 `p1`”太浪费性能了。
>
> 于是编译器玩了个魔术：**它直接在 `main` 函数（或 `test03`）中存放 `p` 的那块内存上，去创建函数内部的 `p1`**。它们两个其实共享了同一块内存！
>
> 这种技术叫做 **NRVO（具名返回值优化）**。因为没有发生真正的数据克隆，所以拷贝构造函数被编译器**优化省略（Elide）**了。
>
> - **如何强制看理论效果？** >   如果你使用的是 Linux GCC，可以在编译时加上参数 `-fno-elide-constructors`（关闭返回值优化），此时你就能完美看到拷贝构造函数的调用以及不同的内存地址了。

###### 📊 拷贝构造触发场景总结表

| **触发时机**      | **典型代码示例**                         | **幕后本质**                                                 |
| ----------------- | ---------------------------------------- | ------------------------------------------------------------ |
| **1. 显式初始化** | `Person p2(p1);` `Person p3 = p1;`       | 明确地用旧对象去作为新对象的克隆蓝本。                       |
| **2. 函数值传递** | `void func(Person p)` 调用：`func(obj);` | 隐式在函数栈中执行了 `Person p = obj;` 的克隆操作。          |
| **3. 函数值返回** | `Person func() { return obj; }`          | 传统编译器用于跨函数传递临时数据。（现代编译器多被 RVO 优化省略） |



**示例：**

```C++
class Person {
public:
	Person() {
		cout << "无参构造函数!" << endl;
		mAge = 0;
	}
	Person(int age) {
		cout << "有参构造函数!" << endl;
		mAge = age;
	}
	Person(const Person& p) {
		cout << "拷贝构造函数!" << endl;
		mAge = p.mAge;
	}
	//析构函数在释放内存之前调用
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int mAge;
};

//1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01() {

	Person man(100); //p对象已经创建完毕
	Person newman(man); //调用拷贝构造函数
	Person newman2 = man; //拷贝构造

	//Person newman3;
	//newman3 = man; //不是调用拷贝构造函数，赋值操作
}

//2. 值传递的方式给函数参数传值
//相当于Person p1 = p;
void doWork(Person p1) {}
void test02() {
	Person p; //无参构造函数
	doWork(p);
}

//3. 以值方式返回局部对象
Person doWork2()
{
	Person p1;
	cout << (int *)&p1 << endl;
	return p1;
}

void test03()
{
	Person p = doWork2();
	cout << (int *)&p << endl;
}


int main() {

	//test01();
	//test02();
	test03();

	system("pause");

	return 0;
}
```





#### 4.2.4 构造函数调用规则

默认情况下，c++编译器至少给一个类添加3个函数

1．默认构造函数(无参，函数体为空)

2．默认析构函数(无参，函数体为空)

3．默认拷贝构造函数，对属性进行值拷贝

示例：

```C++
class Person {
public:
	//无参（默认）构造函数
	Person() {
		cout << "无参构造函数!" << endl;
	}
    
	//有参构造函数
	Person(int a) {
		age = a;
		cout << "有参构造函数!" << endl;
	}
    
	//拷贝构造函数
    //如果注释拷贝构造函数，编译器仍然会执行 age=p.age 赋值操作，即仍然 默认拷贝
	//Person(const Person& p) {
	//	age = p.age;
	//	cout << "拷贝构造函数!" << endl;
	//}
    
	//析构函数
	~Person() {
		cout << "析构函数!" << endl;
	}
public:
	int age;
};

void test01()
{
	Person p1(18);
	//如果不写拷贝构造，编译器会自动添加拷贝构造，并且做浅拷贝操作，这是因为“默认情况下，c++编译器至少给一个类添加3个函数”
	Person p2(p1);

	cout << "p2的年龄为： " << p2.age << endl;
}

int main() {

	test01();

	system("pause");
	return 0;
}
```



构造函数调用规则如下：

> [!IMPORTANT]
>
> 等级：
>
> 默认无参构造 < 有参构造 <  拷贝构造
>
> ==自己写的高级构造函数会屏蔽编译器提供的低级构造函数==

> 如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造

```c++
#include <iostream>
using namespace std;

//构造函数的调用规则

class Person{

public:
    int m_age;
	
    //默认构造函数
    // Person(){
    //     cout << "Person 的默认构造函数调用" << endl;
    // }

    //有参构造函数
    Person(int age)
    {
        m_age = age;
        cout << "Person 有参的默认构造函数调用" << endl;
    }
	
    //拷贝构造函数
    Person(const Person &p)
    {
        m_age = p.m_age;
        cout << "Person 拷贝构造函数调用" << endl;
    }
	
    //析构函数调用
    ~Person(){
        cout << "Person 的析构函数调用" << endl;
    }
};


void test2()
{
    Person p;		//无默认构造报错，为什么？因为 如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
}

int main()
{

    // test1();
    test2();
    system("pause");
    return 0;
}
```




* 如果用户定义拷贝构造函数，c++不会再提供其他构造函数



#### 4.2.5 深拷贝与浅拷贝



深浅拷贝是面试经典问题，也是常见的一个坑

```C++
#include <iostream>
using namespace std;

// 深拷贝和浅拷贝

class Person
{

public:
    int m_age;     // 年龄
    int *m_height; // 身高
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }

    Person(int age, int height)
    {
        m_age = age;
        m_height = new int(height); // 在堆（自由存储区）上分配一个 int 类型的对象，并用 height 的值来初始化它，然后将这个对象的地址赋给指针 m_height
        cout << "Person的有参构造函数调用" << endl;
    }

    ~Person()
    {
        // 析构代码，将堆区开辟数据做释放操作
        // 当指针 m_height 指向的堆区数据被释放时，运行析构代码
        if (m_height != NULL)
        {
            delete m_height; // 释放指针 m_height 指向的地址空间
            m_height = NULL; // 避免野指针
        }
        cout << "Person的析构函数调用" << endl;
    }
};

void test1()
{
    Person p1(18, 160);
    cout << "p1的年龄为：" << p1.m_age << "身高为： " << *p1.m_height << endl;

    Person p2(p1); // 拷贝构造函数
    cout << "p2的年龄为：" << p2.m_age << "身高为： " << *p2.m_height << endl;
}

int main()
{

    test1();
    system("pause");
    return 0;
}系统默认提供的拷贝构造函数是**浅拷贝（Shallow Copy）**。它只是简单地把指针的地址复制了一份。
```

在这个例子中：

1. `Person p1(18, 160);`：在堆区开辟了一块内存（假设地址是 `0x0011`），`p1.m_height` 指向 `0x0011`。
2. `Person p2(p1);`：调用默认拷贝构造函数，把 `p1.m_height` 的地址**直接复制**给 `p2.m_height`。此时 `p2.m_height` 也指向 `0x0011`。
3. **析构阶段（先进后出原则）**：
   - `p2` 先被销毁，调用析构函数，执行 `delete p2.m_height;`（即释放了 `0x0011`）。
   - `p1` 随后被销毁，调用析构函数，执行 `delete p1.m_height;`。由于 `p1.m_height` 仍然存着 `0x0011` 这个地址，它试图再次释放一块已经被释放的内存！这就是 Double Free。



系统默认的浅拷贝只是机械地复制指针地址

- `p1.m_height` ───> **【堆区地址 0x0011 ：160】** <─── `p2.m_height`
- **后果**：两个人共用一把钥匙（指针）锁同一扇门。析构时 `p2` 把门拆了，`p1` 还要去拆，就会引发 Double Free 崩溃。

![image-20260706154917194](./C++核心编程.assets/image-20260706154917194.png)



深拷贝：在堆区重新申请空间，进行拷贝操作



**示例：**

```C++
#include <iostream>
using namespace std;

// 深拷贝和浅拷贝

class Person
{

public:
    int m_age;     // 年龄
    int *m_height; // 身高
    Person()
    {
        cout << "Person的默认构造函数调用" << endl;
    }

    Person(int age, int height)
    {
        m_age = age;
        m_height = new int(height); // 在堆（自由存储区）上分配一个 int 类型的对象，并用 height 的值来初始化它，然后将这个对象的地址赋给指针 m_height
        cout << "Person的有参构造函数调用" << endl;
    }

    Person(const Person &p)
    {
        cout << "Person 拷贝构造函数调用" << endl;
        m_age = p.m_age;
        // m_height=p.m_height; //编译器默认实现浅拷贝，直接将堆区地址复制一份

        // 深拷贝
        m_height = new int(*p.m_height); // 在堆（自由存储区）上分配一个 int 类型的对象，并用 *p.m_height 的值来初始化它，然后将这个对象的地址赋给指针 m_height。
    }

    ~Person()
    {
        // 析构代码，将堆区开辟数据做释放操作
        // 当指针 m_height 指向的堆区数据被释放时，运行析构代码
        if (m_height != NULL)
        {
            delete m_height; // 释放指针 m_height 指向的地址空间
            m_height = NULL; // 避免野指针
        }
        cout << "Person的析构函数调用" << endl;
    }
};

void test1()
{
    Person p1(18, 160);
    cout << "p1的年龄为：" << p1.m_age << "身高为： " << *p1.m_height << endl;

    Person p2(p1); // 拷贝构造函数
    cout << "p2的年龄为：" << p2.m_age << "身高为： " << *p2.m_height << endl;
}

int main()
{

    test1();
    system("pause");
    return 0;
}
```



==核心代码==

```C++
m_height = new int(*p.m_height);
```

这一行代码在 CPU 眼里，其实被拆分成了两步：

1. **解引用取值（`*p.m_height`）**：顺着旧对象 `p1` 的指针，找到它在堆区存储的实际数值（也就是 `160`）。
2. **开辟新内存（`new int(...)`）**：在堆区申请一块**全新的、独立**的内存空间，把 `160` 填进去，然后让新对象 `p2.m_height` 指向这个新地址。



通过 `new` 关键字，在堆区克隆了一个一模一样但完全独立的“新房子”。

- `p1.m_height` ───> **【堆区地址 0x0011 ：160】**
- `p2.m_height` ───> **【堆区地址 0x0022 ：160】**
- **结果**：虽然两人的身高数值都是 160，但它们存在于堆区不同的格子里，互不相干。

------

现在我们再来模拟一遍 `test1()` 函数执行完毕、对象准备销毁时的**析构现场**：

1. **`p2` 先析构**：调用析构函数，执行 `delete m_height;`。系统成功释放了 `0x0022` 这块内存，并将其置为 `NULL`。
2. **`p1` 后析构**：调用析构函数，执行 `delete m_height;`。系统成功释放了 `0x0011` 这块内存，并将其置为 `NULL`。



> 总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题









#### 4.2.6 初始化列表



**作用：**

C++提供了初始化列表语法，用来初始化属性



**语法：**`构造函数()：属性1(值1),属性2（值2）... {}`



**示例：**

```C++
class Person {
public:

	////传统方式初始化
	//Person(int a, int b, int c) {
	//	m_A = a;
	//	m_B = b;
	//	m_C = c;
	//}

	//初始化列表方式初始化
	Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c) {}
	void PrintPerson() {
		cout << "mA:" << m_A << endl;
		cout << "mB:" << m_B << endl;
		cout << "mC:" << m_C << endl;
	}
private:
	int m_A;
	int m_B;
	int m_C;
};

int main() {

	Person p(1, 2, 3);
	p.PrintPerson();


	system("pause");

	return 0;
}
```





#### 4.2.7 类对象作为类成员



C++类中的成员可以是另一个类的对象，我们称该成员为 对象成员



例如：

```C++
class A {}
class B
{
    A a；
}
```



B类中有对象A作为成员，A为对象成员



那么当创建B对象时，A与B的构造和析构的顺序是谁先谁后？

> 注意：当其他类对象作为本类成员，构造时候先构造类对象，再构造自身, 析构的顺序与构造相反
>
> 
>
> 类对象作为 `砖块`，应该先构造，析构相反



**示例：**

```C++
#include <iostream>
#include <string>
using namespace std;

// 类对象作为类成员

// 手机类
class Phone{
public:

    Phone(string pName){    // 手机 类对象赋初值
        cout << "Phone 的构造函数调用" << endl;
        m_Pname = pName;
    }

    ~Phone()
    {
        cout << "Phone 的析构函数调用" << endl;
    }

    string m_Pname;
};

//人类
class Person{
public:
    Person(string name, string pName):m_name(name), m_phone(pName){
        // /m_phone(pName)代表对 “Phone” 类的对象 赋初值

        cout << "Person 的构造函数调用" << endl;
        }


    ~Person(){
        cout << "Person 的析构函数调用" << endl;
    }
    // 姓名
    string m_name;

    // 手机
    Phone m_phone; // 这是一个 “Phone” 类的对象
};

// 注意：当其他类对象作为本类成员，构造时候先构造类对象，再构造自身, 析构的顺序与构造相反

void test1(){
    Person p("张三", "苹果MAX");

    cout << p.m_name << " 使用" << p.m_phone.m_Pname << " 牌手机! " << endl;
}
int main()
{
    test1();
    system("pause");
    return 0;
}
```



==注意==

```C++
cout << p.m_name << " 使用" << p.m_phone.m_Pname << " 牌手机! " << endl;
```

- `p.m_name` 是一个 `string` 类型，`cout` 认识它，可以正常打印。
- **`p.m_phone` 是一个 `Phone` 类的“对象”**。C++ 的 `cout` 默认只认识基础类型（如 `int`, `float`, `string` 等）。面对你亲手创造的 `Phone` 类，`cout` 是一头雾水的——它不知道你是想打印手机的名字、手机的型号，还是打印它的内存地址。







#### 4.2.8 静态成员

静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为：



*  静态成员变量
   *  所有对象共享同一份数据
   *  在编译阶段分配内存
   *  类内声明，类外初始化
*  静态成员函数
   *  所有对象共享同一个函数
   *  静态成员函数只能访问静态成员变量



###### 类内声明，类外初始化

```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
public:
    // 1、所有对象都共享同一份数据
    // 2、编译阶段就分配内存
    // 3、类内声明，类外初始化操作

    static int m_a; // 静态成员变量，类内声明
};

int Person::m_a = 100; // 类外初始化

void test1()
{
    Person p;
    cout << p.m_a << endl;
}

int main()
{
    test1();
    
    system("pause");
    return 0;
}
```



###### 所有对象共享同一份数据

```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
public:
    // 1、所有对象都共享同一份数据
    // 2、编译阶段就分配内存
    // 3、类内声明，类外初始化操作

    static int m_a; // 静态成员变量，类内声明
};

int Person::m_a = 100; // 类外初始化

void test1()
{
    ///////////////////////////////////////////////////////////
    // 两次打印出的数据不相同，说明 p2.m_a = 200; 会修改m_a
    // 说明所有对象都共享同一份静态成员数据
    ///////////////////////////////////////////////////////////
    Person p;
    cout << p.m_a << endl;

    Person p2;
    p2.m_a = 200;   
    cout << p.m_a << endl;
}

int main()
{
    test1();

    system("pause");
    return 0;
}
```





静态成员变量不属于某个对象上，所有对象都共享同一份数据

因此静态成员变量有两种访问方式：

1. 通过对象进行访问

2. 通过类名进行访问

```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
public:
    // 1、所有对象都共享同一份数据
    // 2、编译阶段就分配内存
    // 3、类内声明，类外初始化操作

    static int m_a; // 静态成员变量，类内声明
};

int Person::m_a = 100; // 类外初始化

void test2(){
    //静态成员变量不属于某个对象上，所有对象都共享同一份数据
    //因此静态成员变量有两种访问方式
    //1、通过对象进行访问
    // Person p;
    // cout << p.m_a << endl;      //因为类外初始化时为100

    //2、通过类名进行访问
    cout << Person::m_a << endl;    //不同创建类，直接通过类名访问
}

int main()
{
    // test1();
    test2();
    system("pause");
    return 0;
}
```



###### 私有权限访问不到

```C++
class Person
{
	
public:

	static int m_A; //静态成员变量

	//静态成员变量特点：
	//1 在编译阶段分配内存
	//2 类内声明，类外初始化
	//3 所有对象共享同一份数据

private:
	static int m_B; //静态成员变量也是有访问权限的
};
int Person::m_A = 10;
int Person::m_B = 10;

void test01()
{
	//cout << "m_B = " << Person::m_B << endl; //私有权限访问不到
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**示例2：**静态成员函数

```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{

public:     //公有
    // 静态成员函数特点：
    // 1 程序共享一个函数
    // 2 静态成员函数只能访问静态成员变量

    static void func()  //静态成员函数
    {
        cout << "func调用" << endl;
        m_A = 100; // 正确， 静态成员函数只能访问静态成员变量
        //m_B = 100; //错误，静态成员函数只能访问静态成员变量，不可以访问非静态成员变量
    }

    static int m_A; // 静态成员变量
    int m_B;        // 非静态成员变量

private:    //私有
    // 静态成员函数也是有访问权限的
    static void func2()
    {
        cout << "func2调用" << endl;
    }
};
int Person::m_A = 10;       //类外初始化

void test01()
{
    // 静态成员变量两种访问方式

    // 1、通过对象
    Person p1;
    p1.func();

    // 2、通过类名
    Person::func();

    // Person::func2(); //私有权限访问不到
}

int main()
{

    test01();

    system("pause");

    return 0;
}
```









### 4.3 C++对象模型和this指针



#### 4.3.1 成员变量和成员函数分开存储



```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{


};


void test01()
{
    Person p;
    //空对象占用内存空间为：1   字节
    //C++编译器会给每个空对象分配一个字节空间，是为了区分空对象占内存的位置
    //每个空对象也应该有一个独一无二的内存地址
    cout << "size of p = " << sizeof(p) << endl;
}


int main()
{

    test01();

    system("pause");

    return 0;
}
```



```C++
#include <iostream>
#include <string>
using namespace std;

// 静态成员变量
class Person
{
    int m_a;    //非静态成员变量  属于类的对象上

    static int m_b; //静态成员变量
};


void test01()
{
    Person p;
    cout << "size of p = " << sizeof(p) << endl;
}

int main()
{

    test01();

    system("pause");

    return 0;
}
```

在C++中，类内的成员变量和成员函数分开存储

只有非静态成员变量才属于类的对象上



```C++
class Person {
public:
	Person() {
		mA = 0;
	}
	//非静态成员变量占对象空间
	int mA;
	//静态成员变量不占对象空间
	static int mB; 
	//函数也不占对象空间，所有函数共享一个函数实例
	void func() {
		cout << "mA:" << this->mA << endl;
	}
	//静态成员函数也不占对象空间
	static void sfunc() {
	}
};

int main() {

	cout << sizeof(Person) << endl;

	system("pause");

	return 0;
}
```







#### 4.3.2 this指针概念

通过4.3.1我们知道在C++中成员变量和成员函数是分开存储的

每一个非静态成员函数只会诞生一份函数实例，也就是说多个同类型的对象会共用一块代码

那么问题是：这一块代码是如何区分那个对象调用自己的呢？



c++通过提供特殊的对象指针，this指针，解决上述问题。**this指针指向被调用的成员函数所属的对象**



this指针是隐含每一个非静态成员函数内的一种指针

this指针不需要定义，直接使用即可



this指针的用途：

*  当形参和成员变量同名时，可用this指针来区分
*  在类的非静态成员函数中返回对象本身，可使用return *this



```C++
// 静态成员变量
class Person
{
public:
    Person(int age){
        age = age;
    }

    int age;
};
```

> ==错误==
>
> **构造函数中的名称遮蔽（自赋值）**
>
> 构造函数参数 `age` 与成员变量 `age` 同名。在函数体内 `age = age;` 左右两边的 `age` 都指代**参数**，相当于参数自己给自己赋值
>
> 可以用 `this` 指针区分



```C++
class Person
{
public:

	Person(int age)
	{
		//1、当形参和成员变量同名时，可用this指针来区分，当 p1对象 调用这个类，指针 this 指向 p1对象
		this->age = age;
	}

	Person& PersonAddPerson(Person p)
	{
		this->age += p.age;
		//返回对象本身
		return *this;
	}

	int age;
};

void test01()
{
	Person p1(10);
	cout << "p1.age = " << p1.age << endl;

	Person p2(10);
	p2.PersonAddPerson(p1).PersonAddPerson(p1).PersonAddPerson(p1);
	cout << "p2.age = " << p2.age << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```







```C++
Person& PersonAddPerson(Person p)
{
    this->age += p.age;
    //返回对象本身
    return *this;
}
```

##### 核心问题：为什么返回 `Person&`（引用），而不是 `Person`（值）？

这是值传递和引用传递的本质区别。我们可以写出两种设计，看看它们在执行 `p2.PersonAddAge(p1).PersonAddAge(p1);` 时分别会发生什么：

###### 情况 A：如果返回的是 `Person`（按值返回）

如果不加 `&`，C++ 在函数返回时，会偷偷做一件事情：**复制**。

> **当返回 `Person` 时，底层发生的过程：**
>
> 1. `p2.PersonAddAge(p1)` 执行：`p2` 的年龄从 10 变成了 20。
> 2. 准备返回：因为是按值返回，编译器会克隆一个全新的临时对象（假设叫 `p2_克隆体`），它的年龄也是 20。
> 3. 后半段执行：点部分 `.PersonAddAge(p1)` 作用在了谁身上？作用在了**`p2_克隆体`**身上！
> 4. `p2_克隆体` 的年龄变成了 30，但原本的 **`p2` 的年龄依然停留在 20**。
> 5. 语句结束，这个临时创建的 `p2_克隆体` 被销毁。

**结果：** 打印 `p2.age`，依然是 **20**。第二次加年龄的操作加到“替身”身上去了，本体没享受到。



###### 情况 B：如果返回的是 `Person&`（按引用返回）

加了 `&`，代表返回的是一个**别名（引用）**，不会发生任何复制。

> **当返回 `Person&` 时，底层发生的过程：**
>
> 1. `p2.PersonAddAge(p1)` 执行：`p2` 的年龄从 10 变成了 20。
> 2. 准备返回：返回的是 `*this` 的引用，也就是直接把 `p2` 本尊的原件递了出去。
> 3. 后半段执行：点部分 `.PersonAddAge(p1)` 依然实打实地作用在 **`p2` 本尊** 身上。
> 4. `p2` 本尊的年龄顺利变成了 30。

**结果：** 打印 `p2.age`，成功变成了 **30**。





#### 4.3.3 空指针访问成员函数



C++中空指针也是可以调用成员函数的，但是也要注意有没有用到this指针



如果用到this指针，需要加以判断保证代码的健壮性



**示例：**

```C++
//空指针访问成员函数
class Person {
public:

	void ShowClassName() {
		cout << "我是Person类!" << endl;
	}

	void ShowPerson() {
		if (this == NULL) {
			return;
		}
		cout << mAge << endl;
	}

public:
	int mAge;
};

void test01()
{
	Person * p = NULL;
	p->ShowClassName(); //空指针，可以调用成员函数
	p->ShowPerson();  //但是如果成员函数中用到了this指针，就不可以了
}

int main() {

	test01();

	system("pause");

	return 0;
}
```









#### 4.3.4 const修饰成员函数



**常函数：**

* 成员函数后加const后我们称为这个函数为**常函数**
* 常函数内不可以修改成员属性
* 成员属性声明时加关键字mutable后，在常函数中依然可以修改



**常对象：**

* 声明对象前加const称该对象为常对象
* 常对象只能调用常函数







**示例：**

```C++
#include <iostream>
#include <string>
using namespace std;
//**常函数：**
    //成员函数后加const后我们称为这个函数为  常函数 
    // 常函数内不可以修改成员属性
    // 成员属性声明时加关键字mutable后，在常函数中依然可以修改

//* *常对象： **

    //声明对象前加const称该对象为常对象 
    //常对象只能调用常函数


class Person
{
public:
    // this 指针的本质   是指针常量    指针的指向是不可以修改的
    // Person * const this;

    //在成员函数后面加上 const ，修饰的是 this 指向， 让指针指向的值也不可以修改，所以第22行代码无法修改
    void showPerson() const     //常函数
    {
        // /this->m_b = 100;
        this->m_b = 100;
        //this = NULL;  //this 指针不可以修改指针的指向的
    }

    void func() {      //普通函数

    };

    void showPersonAge()
    {
        cout << "age = " << this->m_a << endl;
    }
    int m_a;
    mutable int m_b;    //特殊变量，加上 mutable 就可以修改指针指向
};

void test01()
{
    const Person p{};     //在对象前加const， 变为常对象
    // p.m_a = 100;    //常对象所有属性均为只读，除非加上了mutable
    // p.m_b = 100;    //m_b 是 mutable ，可变的，所以虽然 p 是常对象，但是依然可以修改之

    //常对象只能调用常函数
    p.showPerson(); // showPerson()是常函数
    // p.func();       //func 不是常函数
}

int main()
{

    test01();

    system("pause");

    return 0;
}
```

# 

##### 1. `this` 指针的“套娃”本质

在 C++ 内部，普通的成员函数里都隐藏着一个 `this` 指针，它的底层本质是一个**指针常量**：

```C++
类名 * const this;
```

这意味着：**`this` 指针的指向雷打不动**，你不能让它指向别人（比如代码里写的 `this = NULL;` 是绝对违法的）。但是，你**可以**通过它去修改它指向的那个对象的属性（如 `this->m_a = 100;`）。

##### 2. 常函数 (Const Member Function)

###### 什么是常函数？

在成员函数的**大括号前面**加上 `const` 修饰的函数。

```C++
void showPerson() const { ... }
```

###### 底层原理

这个 `const` 实际上修饰的是那个隐藏的 `this` 指针。它把指针的类型升级成了：

```C++
const 类名 * const this;
```

这下厉害了：**不仅指针的指向不能改，连指针指向的属性值（成员变量）也变成只读的了！**

##### 3. `mutable` 关键字（特权开后门）

有些时候，我们希望函数整体是“只读”的（常函数），但偏偏有那么一两个变量（比如：调用次数计数器、缓存锁），即使在常函数里也必须能修改。

这时候就要用到 `mutable`（可变的）：

- **作用：** 被 `mutable` 修饰的成员变量，在常函数中依然可以被修改。
- *注意修正你的注释：* `mutable` 改变的是**变量本身的可变性**，而不是改变“指针的指向”。

##### 4. 常对象 (Const Object)

在声明对象前加上 `const`，这个对象就成了常对象。

```C++
const Person p;
```

- **特点：** 常对象的所有属性都是只读的（除非属性加了 `mutable`）。
- **核心规则：** **常对象只能调用常函数。** 因为普通函数有修改属性的风险，C++ 编译器为了安全，直接一刀切，不让常对象调用普通函数。

##### 💡 总结对比表

| **概念**         | **语法形式**        | **this 的本质**             | **成员变量能否修改？**                 |
| ---------------- | ------------------- | --------------------------- | -------------------------------------- |
| **普通成员函数** | `void func()`       | `Person * const this`       | 可以修改                               |
| **常函数**       | `void func() const` | `const Person * const this` | **不能修改**（除非变量加了 `mutable`） |






### 4.4 友元



生活中你的家有客厅(Public)，有你的卧室(Private)

客厅所有来的客人都可以进去，但是你的卧室是私有的，也就是说只有你能进去

但是呢，你也可以允许你的好闺蜜好基友进去。



在程序里，有些私有属性 也想让类外特殊的一些函数或者类进行访问，就需要用到友元的技术



友元的目的就是让一个函数或者类 访问另一个类中私有成员



友元的关键字为  ==friend==



友元的三种实现

* 全局函数做友元
* 类做友元
* 成员函数做友元





#### 4.4.1 全局函数做友元

没有友元的情况下，全局函数`goodGay()`是访问不到私有权限

```C++
#include <iostream>
#include <string>
using namespace std;

// 建筑物类
class Building
{

public:
    Building()
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }

public:
    string m_SittingRoom; // 客厅

private:
    string m_BedRoom; // 卧室
};

// 全局函数goodGay
void goodGay(Building *building)
{
    // 可以访问公共属性
    cout << "好基友全局函数 正在访问：" << building->m_SittingRoom << endl;

    // 不能访问私有属性
    // cout << "好基友全局函数 正在访问：" << building->m_BedRoom << endl;
}

void test01()
{
    Building b;  // 实例化一个 建筑对象p
    goodGay(&b); // 调用test1
}

int main()
{

    test01();

    system("pause");

    return 0;
}
```



加入友元

```C++
class Building
{
	//告诉编译器 goodGay全局函数 是 Building类的好朋友，可以访问类中的私有内容
	friend void goodGay(Building * building);

public:

	Building()
	{
		this->m_SittingRoom = "客厅";
		this->m_BedRoom = "卧室";
	}


public:
	string m_SittingRoom; //客厅

private:
	string m_BedRoom; //卧室
};


void goodGay(Building * building)
{
	cout << "好基友正在访问： " << building->m_SittingRoom << endl;
	cout << "好基友正在访问： " << building->m_BedRoom << endl;
}


void test01()
{
	Building b;
	goodGay(&b);
}

int main(){

	test01();

	system("pause");
	return 0;
}
```



#### 4.4.2 类做友元

```C++
#include <iostream>
#include <string>
using namespace std;

// 建筑物类
class Building
{
    ////////////////////////////////////////////////////
    friend class GoodGay; // 友元类，是的 GoodGay类 可以访问 Building类 的私有权限
    ////////////////////////////////////////////////////

public:
    Building() // Building类 的构造函数
    {
        m_SittingRoom = "客厅";
        m_BedRoom = "卧室";
    }

public:
    string m_SittingRoom; // 客厅

private:
    string m_BedRoom; // 卧室
};

// 好朋友类
class GoodGay
{
public:
    // GoodGay的构造函数
    GoodGay()
    {
        // 创建建筑物对象
        building = new Building;
        // 你的理解完全正确：
        // 1、申请内存：在内存的堆区动态开辟空间。
        // 2、初始化对象：自动调用 Building 的构造函数。
        // 3、传递地址：new 返回首地址。
        // 4、指针接收：赋值给 building 指针。

        cout << "GoodGay的构造函数" << endl;
    }

    void visit()
    {
        cout << "好基友类正在访问：" << building->m_SittingRoom << endl;

        // 没加友元是访问不了卧室类的，因为卧室是 Building类 的私有权限
        cout << "好基友类正在访问：" << building->m_BedRoom << endl;
    }

    Building *building; // 类对象的指针作为类成员
    // GoodGay 对象内部只保存了一个 8 字节（或 4 字节）的地址。真正的 Building 房子在堆区，需要你手动 new 才会创建。
};

void test01()
{
    GoodGay gg; // 实例化对象
    gg.visit();
}

int main()
{
    test01();

    system("pause");
    return 0;
}
```





#### 4.4.3 成员函数做友元



```C++

class Building;
class goodGay
{
public:

	goodGay();
	void visit(); //只让visit函数作为Building的好朋友，可以发访问Building中私有内容
	void visit2(); 

private:
	Building *building;
};


class Building
{
	//告诉编译器  goodGay类中的visit成员函数 是Building好朋友，可以访问私有内容
	friend void goodGay::visit();

public:
	Building();

public:
	string m_SittingRoom; //客厅
private:
	string m_BedRoom;//卧室
};

Building::Building()
{
	this->m_SittingRoom = "客厅";
	this->m_BedRoom = "卧室";
}

goodGay::goodGay()
{
	building = new Building;
}

void goodGay::visit()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void goodGay::visit2()
{
	cout << "好基友正在访问" << building->m_SittingRoom << endl;
	//cout << "好基友正在访问" << building->m_BedRoom << endl;
}

void test01()
{
	goodGay  gg;
	gg.visit();

}

int main(){
    
	test01();

	system("pause");
	return 0;
}
```









### 4.5 运算符重载



运算符重载概念：对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型



#### 4.5.1 加号运算符重载



作用：实现两个自定义数据类型相加的运算



```C++
class Person {
public:
	Person() {};
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
	//成员函数实现 + 号运算符重载
	Person operator+(const Person& p) {
		Person temp;
		temp.m_A = this->m_A + p.m_A;
		temp.m_B = this->m_B + p.m_B;
		return temp;
	}


public:
	int m_A;
	int m_B;
};

//全局函数实现 + 号运算符重载
//Person operator+(const Person& p1, const Person& p2) {
//	Person temp(0, 0);
//	temp.m_A = p1.m_A + p2.m_A;
//	temp.m_B = p1.m_B + p2.m_B;
//	return temp;
//}

//运算符重载 可以发生函数重载 
Person operator+(const Person& p2, int val)  
{
	Person temp;
	temp.m_A = p2.m_A + val;
	temp.m_B = p2.m_B + val;
	return temp;
}

void test() {

	Person p1(10, 10);
	Person p2(20, 20);

	//成员函数方式
	Person p3 = p2 + p1;  //相当于 p2.operaor+(p1)
	cout << "mA:" << p3.m_A << " mB:" << p3.m_B << endl;


	Person p4 = p3 + 10; //相当于 operator+(p3,10)
	cout << "mA:" << p4.m_A << " mB:" << p4.m_B << endl;

}

int main() {

	test();

	system("pause");

	return 0;
}
```

> 总结1：对于内置的数据类型的表达式的的运算符是不可能改变的

> 总结2：不要滥用运算符重载



##### 1. 成员函数重载 `+` 号

###### 代码标准写法

这种方式是将重载函数写在类的内部，作为类的一个成员。

```c++
class Person {
public:
    int m_a;
    int m_b;

    // 成员函数重载+号
    Person operator+(const Person &p) {
        Person temp;
        temp.m_a = this->m_a + p.m_a;
        temp.m_b = this->m_b + p.m_b;
        return temp;
    }
};
```

###### 核心要点

- **隐式传递与参数个数**：在类内部重载双目运算符（需要两个操作数）时，函数的参数列表只需要**一个**参数。因为左操作数会通过隐藏的 `this` 指针隐式传递给函数，而参数列表里的 `p` 代表的是右操作数。

- **调用的本质**：当你写下 `Person p3 = p1 + p2;` 时，编译器在底层实际将其转换为：

  ```C++
  Person p3 = p1.operator+(p2);
  ```

  即：`p1` 对象调用了它自己的成员函数，并把 `p2` 当作实参传了进去。

##### 2. 全局函数重载 `+` 号

这种方式是将重载函数写在类的外部，作为一个独立的全局函数。

###### 代码标准写法

```C++
// 全局函数重载+号
Person operator+(const Person &p1, const Person &p2) {
    Person temp;
    temp.m_a = p1.m_a + p2.m_a;
    temp.m_b = p1.m_b + p2.m_b;
    return temp;
}
```

###### 核心要点

- **显式传递与参数个数**：因为是全局函数，没有 `this` 指针，所以需要将参与运算的两个操作数**都显式地**作为参数传进来。左边的参数 `p1` 代表左操作数，右边的参数 `p2` 代表右操作数。

- **调用的本质**：当你写下 `Person p3 = p1 + p2;` 时，编译器在底层实际将其转换为：

  ```C++
  Person p3 = operator+(p1, p2);
  ```

##### 两种方式的对比与选择

为了方便复习，可以用下面这张表来总结它们的关键区别：

| **特性**         | **成员函数重载**                                             | **全局函数重载**                                             |
| ---------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **参数数量**     | 比运算符实际需要的操作数**少一个**（左操作数由 `this` 代替） | 数量与运算符实际需要的操作数**一致**                         |
| **底层调用本质** | `p1.operator+(p2)`                                           | `operator+(p1, p2)`                                          |
| **私有成员访问** | 可以直接访问类的 `private` 成员                              | 不能直接访问。如果类属性是私有的，需要配合 `friend`（友元函数） |
| **典型适用场景** | 绝大多数常规运算符（如 `+`, `-`, `*`, `/`, `=`）             | **必须**由其他类型作为左操作数的场景（如重载 `<<` 输出流运算符） |

> ### 📝 进阶高分笔记：为什么要用 `const &`（常引用）？
>
> 你可能会注意到，我在上面的标准写法中加上了 `const Person &p`。在写正式的 C++ 代码或应对面试时，这是非常重要的好习惯：
>
> 1. **使用引用 `&`**：避免了在函数传参时拷贝整个对象，提升了代码运行效率。
> 2. **使用 `const`**：防止函数内部不小心修改了原本输入的对象（比如不小心把 `p1.m_a` 改了），确保了数据安全。



##### 运算符重载也可以发生函数重载

```c++
#include <iostream>
#include <string>
using namespace std;

// 加号运算符重载
class Person
{
public:
    int m_a;
    int m_b;
};


// 3、运算符重载也可以发生函数重载
Person operator+(Person &p1, int num)
{
    Person temp;
    temp.m_a = p1.m_a + num;
    temp.m_b = p1.m_b + num;

    return temp;
}

void test1()
{
    Person p1;
    p1.m_a = 10;
    p1.m_b = 50;

    Person p2;
    p2.m_a = 20;
    p2.m_b = 30;

    //运算符重载也可以发生函数重载
    //比如：
    Person p3 = p1 + 10;

    cout << "p3.m_a = " << p3.m_a << endl;
    cout << "p3.m_b = " << p3.m_b << endl;
}

int main()
{
    test1();

    system("pause");
    return 0;
}
```



#### 4.5.2 左移运算符重载



作用：可以输出自定义数据类型



```C++
#include <iostream>
#include <string>
using namespace std;

// 加号运算符重载
class Person
{
public:
    int m_a;
    int m_b;
};

// =========== 只能用 全局函数重载<< ===============
ostream &operator<<(ostream &cout, Person &p)
{
    cout << "m_a = " << p.m_a << endl;
    cout << "m_b = " << p.m_b << endl;

    return cout;
}

void test1()
{
    Person p;
    p.m_a = 10;
    p.m_b = 50;

    cout << p << endl;
}

int main()
{
    test1();

    system("pause");
    return 0;
}
```



##### 1. 如果尝试用【成员函数】重载（错误尝试）

如果写在类内部，它的形式会是这样：

```C++
// 成员函数重载（不推荐/不符合习惯）
void operator<<(ostream &cout) { ... }
```

还记得上一篇笔记的“底层调用本质”吗？如果这样写，左操作数必须是 `Person` 对象。 那我们在调用时就必须写成：

```C++
p << cout;  // 底层本质：p.operator<<(cout);
```

这完全颠倒了我们平时使用 `cout << p` 的直观习惯，代码看起来非常别扭。

##### 2. 使用【全局函数】重载（正确解法）

为了让 `cout` 站在左边，`p` 站在右边，我们必须使用全局函数。

```C++
ostream& operator<<(ostream &cout, Person &p)
```

这时，编译器底层的转换就变成了：

```C++
operator<<(cout, p); // 完美匹配 cout << p 的顺序！
```

##### 🔍 代码关键细节拆解

仔细观察你的函数签名：`ostream& operator<<(ostream &cout, Person &p)`，这里面有两个极其关键的设计：

###### ① 为什么要返回 `ostream&`（返回引用）？

**为了实现“链式编程”（连续输出）。** 在 `test1` 中，你写了 `cout << p << endl;`。

- 编译器先执行 `cout << p`，这会调用你的重载函数。
- 函数执行完后，把 `cout` 对象本身给**返回**了出来。
- 此时整行代码缩减为：`返回的cout << endl;`，从而能够继续打印后面的内容。

> **💡 笔记提醒：** 如果把返回值改成 `void`，代码写 `cout << p;` 没问题，但一旦写 `cout << p << endl;` 就会直接报错。

###### ② 为什么参数和返回值都要加引用 `&`？

在整个 C++ 程序中，**`ostream`（输出流对象）是全局唯一的，并且它是不允许被复制的**。如果不加 `&`，就会触发对象拷贝，编译器会直接抛出巨量报错。

##### 🚀 进阶高分笔记：实际开发中的“标准完全体”

在实际的 C++ 项目中，你的这份代码通常需要做两处升级，建议一并记录在笔记中：

###### 1. 加上 `const` 修饰

打印对象只是为了读取数据，不应该修改对象。所以右操作数应该加上 `const`。

###### 2. 配合 `friend`（友元）使用

实际开发中，类的属性（如 `m_a`, `m_b`）通常是 `private`（私有的）。全局函数无法直接访问私有属性，这就需要把这个全局函数在类内部声明为**友元函数**。



> 总结：重载左移运算符配合友元可以实现输出自定义数据类型













#### 4.5.3 递增运算符重载



作用： 通过重载递增运算符，实现自己的整型数据



```C++

class MyInteger {

	friend ostream& operator<<(ostream& out, MyInteger myint);

public:
	MyInteger() {
		m_Num = 0;
	}
	//前置++
	MyInteger& operator++() {
		//先++
		m_Num++;
		//再返回
		return *this;
	}

	//后置++
	MyInteger operator++(int) {
		//先返回
		MyInteger temp = *this; //记录当前本身的值，然后让本身的值加1，但是返回的是以前的值，达到先返回后++；
		m_Num++;
		return temp;
	}

private:
	int m_Num;
};


ostream& operator<<(ostream& out, MyInteger myint) {
	out << myint.m_Num;
	return out;
}


//前置++ 先++ 再返回
void test01() {
	MyInteger myInt;
	cout << ++myInt << endl;
	cout << myInt << endl;
}

//后置++ 先返回 再++
void test02() {

	MyInteger myInt;
	cout << myInt++ << endl;
	cout << myInt << endl;
}

int main() {

	test01();
	//test02();

	system("pause");

	return 0;
}
```



> 总结： 前置递增返回引用，后置递增返回值

##### 🧩 核心机制：编译器如何区分前置与后置？

前置 `++myInt` 和后置 `myInt++` 的函数名都是 `operator++`。为了区分它们，C++ 编译器引入了一个语法糖：

- **前置 `++`**：不带任何参数。
- **后置 `++`**：带一个 `int` 类型的**占位参数**（如你代码中的 `operator++(int)`）。这个 `int` 没有任何实际意义，纯粹是为了让函数形成**重载**，告诉编译器：“我是后置版本”。

##### 1. 前置 `++` 详细拆解（先++，再返回）

###### 📌 代码实现与本质

```C++
MyInteger& operator++() {
    m_Num++;        // 1. 先让内部属性自增
    return *this;   // 2. 返回对象本身
}
```

- **调用本质**：`++myInt` 相当于 `myInt.operator++()`。

- **返回值为什么是引用 (`MyInteger&`)？**

  因为前置 `++` 返回的是**改变之后的完好的对象本身**。返回引用可以支持**链式编程**（连续递增），例如在原生 C++ 中 `++++a` 是合法的，返回引用能确保后续的 `++` 依然作用在同一个对象上。

##### 2. 后置 `++` 详细拆解（先返回旧值局，再++）

###### 📌 代码实现与本质

```C++
MyInteger operator++(int) {
    MyInteger temp = *this; // 1. 拿一个临时变量，记录当前未改变的旧值
    m_Num++;                // 2. 让原本的对象属性自增
    return temp;            // 3. 返回刚刚记录的旧值
}
```

- **调用本质**：`myInt++` 相当于 `myInt.operator++(0)`（编译器自动传个0进去）。

- ==**返回值为什么是值（`MyInteger`）而不是引用？**==

  **这是笔记中最重要的避坑点！** 因为 `temp` 是一个**局部临时对象**，当后置 `++` 函数执行完毕后，`temp` 就会被系统销毁释放。如果返回引用（`MyInteger&`），外部拿到的就是一个失效的内存地址（野引用/悬空引用），会导致程序崩溃。因此必须**按值返回**，拷贝一份副本出去。

##### 📊 前置 `++` 与 后置 `++` 关键对比表

| **特性**         | **前置 ++ (++a)**                 | **后置 ++ (a++)**                                |
| ---------------- | --------------------------------- | ------------------------------------------------ |
| **函数签名**     | `operator++()`                    | `operator++(int)` *(int仅作占位区分)*            |
| **执行逻辑**     | 先自增，再返回新值                | 先记录旧值，再自增，最后返回旧值                 |
| **返回值类型**   | **`MyInteger&`** (引用)           | **`MyInteger`** (临时对象/值)                    |
| **是否支持链式** | 支持 (如 `++++a`)                 | 不支持 (如 `a++++` 报错，因为不能对临时对象递增) |
| **效率高低**     | **高** (直接操作本身，无额外开销) | **低** (涉及局部对象的创建、拷贝与销毁)          |









#### 代码解析

```c++
//前置++
MyInteger& operator++() {
    //先++
    m_Num++;
    //再返回
    return *this;
}
```

##### 1. 为什么返回值类型要加上 `&`（返回引用）？

**一句话总结：为了返回“对象本身”，而不是“对象的复制品”。**

在 C++ 中，如果不加 `&`，返回值类型就是 `MyInteger`（值传递）。这意味着函数在执行到 `return` 时，系统会偷偷在内存里**创建一个临时的副本**（复制品）返回出去。

这会带来两个严重问题：

1. **无法支持链式编程（连续递增）**： 原生的 `int` 变量是允许连续前置递增的，比如 `++++a`。
   - **如果加了 `&`**：第一次 `++` 改变了 `myInt` 并返回了 `myInt` 本身。第二次 `++` 就能继续作用在 `myInt` 上。最终 `myInt` 的值增加了 2。
   - **如果不加 `&`**：第一次 `++` 确实让 `myInt` 变成了 1。但它返回的是一个**临时复制品**（假设叫 `temp`）。接下来的第二个 `++` 实际上加在了 `temp` 身上，原本的 `myInt` 依然只有 1。这就脱离了我们对 `++` 的认知。
2. **性能开销**：不加 `&` 会触发拷贝构造函数，白白浪费内存和 CPU 去复制一个新对象，而返回引用只是起个“别名”，零开销。

##### 2. 为什么 return 的时候要对 `this` 解引用（`*this`）？

**一句话总结：因为函数要的是“对象”，而 `this` 是“指针”，必须用 `*` 转化一下。**

这是 C++ 固定的语法规则，我们可以看它们的类型匹配：

- **`this` 是什么？** 在类成员函数内部，`this` 是一个**指针**。它的类型是 `MyInteger*`，里面存放的是当前对象的**内存地址**。
- **函数的返回值是什么？** 你已经声明了函数的返回值类型是 `MyInteger&`（即一个 `MyInteger` 类型的**对象引用**）。

如果你直接写 `return this;`，相当于你把一个“地址（指针）”抛给了一个需要“对象”的函数，编译器会直接报错：`无法从 MyInteger* 转换为 MyInteger&`。

所以，必须在 `this` 前面加上解引用符 `*`：

- `this` ＝ 对象的地址
- `*this` ＝ **对象本身**

当系统看到你 `return *this;`（返回了对象本身），而函数的返回值类型又是 `MyInteger&` 时，它就会完美匹配，自动把这个对象以引用的形式传递出去。

##### 总结

> - 函数名开头的 **`&`**：是为了**留住自己**（拒绝产生临时复制品，支持 `++++a`）。
> - return 后面的 **`*`**：是因为 `this` 是**指针**（必须解引用变成对象，才能满足返回类型）。







#### 4.5.4 赋值运算符重载



c++编译器至少给一个类添加4个函数

1. 默认构造函数(无参，函数体为空)
2. 默认析构函数(无参，函数体为空)
3. 默认拷贝构造函数，对属性进行值拷贝
4. 赋值运算符 operator=, 对属性进行值拷贝





如果类中有属性指向堆区，做赋值操作时也会出现深浅拷贝问题





**示例：**

```C++
class Person
{
public:

	Person(int age)
	{
		//将年龄数据开辟到堆区
		m_Age = new int(age);
	}

	//重载赋值运算符 
	Person& operator=(Person &p)
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
		//编译器提供的代码是浅拷贝
		//m_Age = p.m_Age;

		//提供深拷贝 解决浅拷贝的问题
		m_Age = new int(*p.m_Age);

		//返回自身
		return *this;
	}


	~Person()
	{
		if (m_Age != NULL)
		{
			delete m_Age;
			m_Age = NULL;
		}
	}

	//年龄的指针
	int *m_Age;

};


void test01()
{
	Person p1(18);

	Person p2(20);

	Person p3(30);

	p3 = p2 = p1; //赋值操作

	cout << "p1的年龄为：" << *p1.m_Age << endl;

	cout << "p2的年龄为：" << *p2.m_Age << endl;

	cout << "p3的年龄为：" << *p3.m_Age << endl;
}

int main() {

	test01();

	//int a = 10;
	//int b = 20;
	//int c = 30;

	//c = b = a;
	//cout << "a = " << a << endl;
	//cout << "b = " << b << endl;
	//cout << "c = " << c << endl;

	system("pause");

	return 0;
}
```



##### 为什么需要重载赋值运算符？

在 C++ 中，如果你不写 `operator=`，编译器会默认赠送一个。但默认的赋值运算符执行的是**浅拷贝**（值拷贝/逐字节拷贝）。

对于内部有堆区内存（用 `new` 开辟）的对象来说，浅拷贝会导致两个毁灭性的后果：

1. **内存泄漏**：被赋值的对象原本指向的堆区内存还没释放，指针就被覆盖了，导致那块内存永远无法回收。
2. **非法内存访问（崩溃）**：两个对象的指针指向了同一块堆内存。当它们析构时，这块内存会被 `delete` 两次，直接引发程序崩溃。

因此，只要类里有属性开辟到了堆区，就**必须**手动重载赋值运算符，提供**深拷贝**。

##### 🛠️ 深拷贝赋值运算符的标配流程

编写一个安全的赋值运算符重载，标准的执行逻辑可以用以下步骤来拆解：

**1.自我赋值检查：**最容易遗漏的黄金一步。

先判断传入的对象是不是自己（`this == &p`）。如果是，直接返回 `*this`，防止后面误杀自己的数据。

**2.释放原有堆内存：**斩断过去，防止泄漏。

判断当前对象自己的堆区指针是否为空，如果不为空，先用 `delete` 释放掉，再置为 `NULL`。

**3.开辟新内存并复制值：**深拷贝的核心。

在堆区申请一块全新且独立的内存空间，然后把目标对象的数据解引用（`*p.m_Age`）后复制进来。

**4.返回对象自身：**支持连续赋值。

返回 `*this`（即当前对象的引用），这样才能完美支持类似 `p3 = p2 = p1;` 的链式编程。



##### 🚨 致命高频面试坑：自我赋值（Self-Assignment）

你的代码逻辑整体很棒，但里面隐藏着一个 C++ 经典的“自杀陷阱”。如果有人在写代码时不小心写了这句：

```C++
p1 = p1; // 自我赋值
```

**你的代码会发生什么？**

1. 函数进来，先检查 `m_Age != NULL`。因为 `p1` 有年龄，条件成立。
2. 执行 `delete m_Age;`。注意！因为是自我赋值，`p1` 的 `m_Age` 被当场销毁了！
3. 接着执行 `m_Age = new int(*p.m_Age);`。此时去取 `*p.m_Age`，由于它已经被删了，代码会直接在这里**由于访问非法内存而崩溃**。

##### 📝 完美规范的“完全体”标准代码

建议把下面这段加入了**自我赋值检查**和 **`const` 常引用修饰**的代码作为最终模板写入笔记：

```C++
// 重载赋值运算符（完全体模板）
Person& operator=(const Person &p)
{
    // 1. 核心防御：如果是自我赋值（如 p1 = p1），直接返回自身，后面什么都不做
    if (this == &p)
    {
        return *this;
    }

    // 2. 清理自己原有的旧堆内存
    if (m_Age != NULL)
    {
        delete m_Age;
        m_Age = NULL;
    }

    // 3. 深拷贝：在堆区申请新家，把人家的值搬过来
    m_Age = new int(*p.m_Age);

    // 4. 返回自身引用，支持 p3 = p2 = p1
    return *this;
}
```

> ### 📌 考试/面试必背结论
>
> 在 C++ 中，如果一个类实现了析构函数来释放动态内存，那么它几乎必然需要**手动实现拷贝构造函数**和**赋值运算符重载**。这在 C++ 编程中被称为 **“C++ 三法则（Rule of Three）”**。





#### 4.5.5 关系运算符重载



**作用：**重载关系运算符，可以让两个自定义类型对象进行对比操作



**示例：**

```C++
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	};

	bool operator==(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(Person & p)
	{
		if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	string m_Name;
	int m_Age;
};

void test01()
{
	//int a = 0;
	//int b = 0;

	Person a("孙悟空", 18);
	Person b("孙悟空", 18);

	if (a == b)
	{
		cout << "a和b相等" << endl;
	}
	else
	{
		cout << "a和b不相等" << endl;
	}

	if (a != b)
	{
		cout << "a和b不相等" << endl;
	}
	else
	{
		cout << "a和b相等" << endl;
	}
}


int main() {

	test01();

	system("pause");

	return 0;
}
```





#### 4.5.6 函数调用运算符重载



* 函数调用运算符 ()  也可以重载
* 由于重载后使用的方式非常像函数的调用，因此称为仿函数
* 仿函数没有固定写法，非常灵活



**示例：**

```C++
class MyPrint
{
public:
	void operator()(string text)
	{
		cout << text << endl;
	}

};
void test01()
{
	//重载的（）操作符 也称为仿函数
	MyPrint myFunc;
	myFunc("hello world");
}


class MyAdd
{
public:
	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

void test02()
{
	MyAdd add;
	int ret = add(10, 10);
	cout << "ret = " << ret << endl;

	//匿名对象调用  
	cout << "MyAdd()(100,100) = " << MyAdd()(100, 100) << endl;
}

int main() {

	test01();
	test02();

	system("pause");

	return 0;
}
```









### 4.6  继承

**继承是面向对象三大特性之一**

有些类与类之间存在特殊的关系，例如下图中：

![1544861202252](assets/1544861202252.png)

我们发现，定义这些类时，下级别的成员除了拥有上一级的共性，还有自己的特性。

这个时候我们就可以考虑利用继承的技术，减少重复代码



#### 4.6.1 继承的基本语法



例如我们看到很多网站中，都有公共的头部，公共的底部，甚至公共的左侧列表，只有中心内容不同

接下来我们分别利用普通写法和继承的写法来实现网页中的内容，看一下继承存在的意义以及好处



**普通实现：**

```C++
//Java页面
class Java 
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "JAVA学科视频" << endl;
	}
};
//Python页面
class Python
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "Python学科视频" << endl;
	}
};
//C++页面
class CPP 
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}
	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}
	void content()
	{
		cout << "C++学科视频" << endl;
	}
};

void test01()
{
	//Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	//Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	//C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();

}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**继承实现：**

```C++
//公共页面
class BasePage
{
public:
	void header()
	{
		cout << "首页、公开课、登录、注册...（公共头部）" << endl;
	}

	void footer()
	{
		cout << "帮助中心、交流合作、站内地图...(公共底部)" << endl;
	}
	void left()
	{
		cout << "Java,Python,C++...(公共分类列表)" << endl;
	}

};

//Java页面
class Java : public BasePage
{
public:
	void content()
	{
		cout << "JAVA学科视频" << endl;
	}
};
//Python页面
class Python : public BasePage
{
public:
	void content()
	{
		cout << "Python学科视频" << endl;
	}
};
//C++页面
class CPP : public BasePage
{
public:
	void content()
	{
		cout << "C++学科视频" << endl;
	}
};

void test01()
{
	//Java页面
	cout << "Java下载视频页面如下： " << endl;
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	cout << "--------------------" << endl;

	//Python页面
	cout << "Python下载视频页面如下： " << endl;
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	cout << "--------------------" << endl;

	//C++页面
	cout << "C++下载视频页面如下： " << endl;
	CPP cp;
	cp.header();
	cp.footer();
	cp.left();
	cp.content();


}

int main() {

	test01();

	system("pause");

	return 0;
}
```



**总结：**

继承的好处：==可以减少重复的代码==

class A : public B; 

A 类称为子类 或 派生类

B 类称为父类 或 基类



**派生类中的成员，包含两大部分**：

一类是从基类继承过来的，一类是自己增加的成员。

从基类继承过过来的表现其共性，而新增的成员体现了其个性。









#### 4.6.2 继承方式



继承的语法：`class 子类 : 继承方式  父类`



**继承方式一共有三种：**

* 公共继承
* 保护继承
* 私有继承





![img](assets/clip_image002.png)





**示例：**

```C++
class Base1
{
public: 
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

//公共继承
class Son1 :public Base1
{
public:
	void func()
	{
		m_A; //可访问 public权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};

void myClass()
{
	Son1 s1;
	s1.m_A; //其他类只能访问到公共权限
}

//保护继承
class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2:protected Base2
{
public:
	void func()
	{
		m_A; //可访问 protected权限
		m_B; //可访问 protected权限
		//m_C; //不可访问
	}
};
void myClass2()
{
	Son2 s;
	//s.m_A; //不可访问
}

//私有继承
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3:private Base3
{
public:
	void func()
	{
		m_A; //可访问 private权限
		m_B; //可访问 private权限
		//m_C; //不可访问
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//Son3是私有继承，所以继承Son3的属性在GrandSon3中都无法访问到
		//m_A;
		//m_B;
		//m_C;
	}
};
```









#### 4.6.3 继承中的对象模型



**问题：**从父类继承过来的成员，哪些属于子类对象中？



**示例：**

```C++
class Base
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C; //私有成员只是被隐藏了，但是还是会继承下去
};

//公共继承
class Son :public Base
{
public:
	int m_D;
};

void test01()
{
	cout << "sizeof Son = " << sizeof(Son) << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```





利用工具查看：



![1545881904150](assets/1545881904150.png)



打开工具窗口后，定位到当前CPP文件的盘符

然后输入： cl /d1 reportSingleClassLayout查看的类名   所属文件名



效果如下图：



![1545882158050](assets/1545882158050.png)



> 结论： 父类中私有成员也是被子类继承下去了，只是由编译器给隐藏后访问不到



















#### 4.6.4 继承中构造和析构顺序



子类继承父类后，当创建子类对象，也会调用父类的构造函数



问题：父类和子类的构造和析构顺序是谁先谁后？



**示例：**

```C++
class Base 
{
public:
	Base()
	{
		cout << "Base构造函数!" << endl;
	}
	~Base()
	{
		cout << "Base析构函数!" << endl;
	}
};

class Son : public Base
{
public:
	Son()
	{
		cout << "Son构造函数!" << endl;
	}
	~Son()
	{
		cout << "Son析构函数!" << endl;
	}

};


void test01()
{
	//继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反
	Son s;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



> 总结：继承中 先调用父类构造函数，再调用子类构造函数，析构顺序与构造相反











#### 4.6.5 继承同名成员处理方式



问题：当子类与父类出现同名的成员，如何通过子类对象，访问到子类或父类中同名的数据呢？



* 访问子类同名成员   直接访问即可
* 访问父类同名成员   需要加作用域



**示例：**

```C++
class Base {
public:
	Base()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Base - func()调用" << endl;
	}

	void func(int a)
	{
		cout << "Base - func(int a)调用" << endl;
	}

public:
	int m_A;
};


class Son : public Base {
public:
	Son()
	{
		m_A = 200;
	}

	//当子类与父类拥有同名的成员函数，子类会隐藏父类中所有版本的同名成员函数
	//如果想访问父类中被隐藏的同名成员函数，需要加父类的作用域
	void func()
	{
		cout << "Son - func()调用" << endl;
	}
public:
	int m_A;
};

void test01()
{
	Son s;

	cout << "Son下的m_A = " << s.m_A << endl;
	cout << "Base下的m_A = " << s.Base::m_A << endl;

	s.func();
	s.Base::func();
	s.Base::func(10);

}
int main() {

	test01();

	system("pause");
	return EXIT_SUCCESS;
}
```

总结：

1. 子类对象可以直接访问到子类中同名成员
2. 子类对象加作用域可以访问到父类同名成员
3. 当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数













#### 4.6.6 继承同名静态成员处理方式



问题：继承中同名的静态成员在子类对象上如何进行访问？



静态成员和非静态成员出现同名，处理方式一致



- 访问子类同名成员   直接访问即可
- 访问父类同名成员   需要加作用域



**示例：**

```C++
class Base {
public:
	static void func()
	{
		cout << "Base - static void func()" << endl;
	}
	static void func(int a)
	{
		cout << "Base - static void func(int a)" << endl;
	}

	static int m_A;
};

int Base::m_A = 100;

class Son : public Base {
public:
	static void func()
	{
		cout << "Son - static void func()" << endl;
	}
	static int m_A;
};

int Son::m_A = 200;

//同名成员属性
void test01()
{
	//通过对象访问
	cout << "通过对象访问： " << endl;
	Son s;
	cout << "Son  下 m_A = " << s.m_A << endl;
	cout << "Base 下 m_A = " << s.Base::m_A << endl;

	//通过类名访问
	cout << "通过类名访问： " << endl;
	cout << "Son  下 m_A = " << Son::m_A << endl;
	cout << "Base 下 m_A = " << Son::Base::m_A << endl;
}

//同名成员函数
void test02()
{
	//通过对象访问
	cout << "通过对象访问： " << endl;
	Son s;
	s.func();
	s.Base::func();

	cout << "通过类名访问： " << endl;
	Son::func();
	Son::Base::func();
	//出现同名，子类会隐藏掉父类中所有同名成员函数，需要加作作用域访问
	Son::Base::func(100);
}
int main() {

	//test01();
	test02();

	system("pause");

	return 0;
}
```

> 总结：同名静态成员处理方式和非静态处理方式一样，只不过有两种访问的方式（通过对象 和 通过类名）













#### 4.6.7 多继承语法



C++允许**一个类继承多个类**



语法：` class 子类 ：继承方式 父类1 ， 继承方式 父类2...`



多继承可能会引发父类中有同名成员出现，需要加作用域区分



**C++实际开发中不建议用多继承**







**示例：**

```C++
class Base1 {
public:
	Base1()
	{
		m_A = 100;
	}
public:
	int m_A;
};

class Base2 {
public:
	Base2()
	{
		m_A = 200;  //开始是m_B 不会出问题，但是改为mA就会出现不明确
	}
public:
	int m_A;
};

//语法：class 子类：继承方式 父类1 ，继承方式 父类2 
class Son : public Base2, public Base1 
{
public:
	Son()
	{
		m_C = 300;
		m_D = 400;
	}
public:
	int m_C;
	int m_D;
};


//多继承容易产生成员同名的情况
//通过使用类名作用域可以区分调用哪一个基类的成员
void test01()
{
	Son s;
	cout << "sizeof Son = " << sizeof(s) << endl;
	cout << s.Base1::m_A << endl;
	cout << s.Base2::m_A << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



> 总结： 多继承中如果父类中出现了同名情况，子类使用时候要加作用域











#### 4.6.8 菱形继承



**菱形继承概念：**

​	两个派生类继承同一个基类

​	又有某个类同时继承者两个派生类

​	这种继承被称为菱形继承，或者钻石继承



**典型的菱形继承案例：**



![IMG_256](assets/clip_image002.jpg)



**菱形继承问题：**



1.     羊继承了动物的数据，驼同样继承了动物的数据，当草泥马使用数据时，就会产生二义性。

2. 草泥马继承自动物的数据继承了两份，其实我们应该清楚，这份数据我们只需要一份就可以。



**示例：**

```C++
class Animal
{
public:
	int m_Age;
};

//继承前加virtual关键字后，变为虚继承
//此时公共的父类Animal称为虚基类
class Sheep : virtual public Animal {};
class Tuo   : virtual public Animal {};
class SheepTuo : public Sheep, public Tuo {};

void test01()
{
	SheepTuo st;
	st.Sheep::m_Age = 100;
	st.Tuo::m_Age = 200;

	cout << "st.Sheep::m_Age = " << st.Sheep::m_Age << endl;
	cout << "st.Tuo::m_Age = " <<  st.Tuo::m_Age << endl;
	cout << "st.m_Age = " << st.m_Age << endl;
}


int main() {

	test01();

	system("pause");

	return 0;
}
```



总结：

* 菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义
* 利用虚继承可以解决菱形继承问题



















### 4.7  多态

#### 4.7.1 多态的基本概念



**多态是C++面向对象三大特性之一**

多态分为两类

* 静态多态: 函数重载 和 运算符重载属于静态多态，复用函数名
* 动态多态: 派生类和虚函数实现运行时多态



静态多态和动态多态区别：

* 静态多态的函数地址早绑定  -  编译阶段确定函数地址
* 动态多态的函数地址晚绑定  -  运行阶段确定函数地址



下面通过案例进行讲解多态



```C++
class Animal
{
public:
	//Speak函数就是虚函数
	//函数前面加上virtual关键字，变成虚函数，那么编译器在编译的时候就不能确定函数调用了。
	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}
};

class Cat :public Animal
{
public:
	void speak()
	{
		cout << "小猫在说话" << endl;
	}
};

class Dog :public Animal
{
public:

	void speak()
	{
		cout << "小狗在说话" << endl;
	}

};
//我们希望传入什么对象，那么就调用什么对象的函数
//如果函数地址在编译阶段就能确定，那么静态联编
//如果函数地址在运行阶段才能确定，就是动态联编

void DoSpeak(Animal & animal)
{
	animal.speak();
}
//
//多态满足条件： 
//1、有继承关系
//2、子类重写父类中的虚函数
//多态使用：
//父类指针或引用指向子类对象

void test01()
{
	Cat cat;
	DoSpeak(cat);


	Dog dog;
	DoSpeak(dog);
}


int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

多态满足条件

* 有继承关系
* 子类重写父类中的虚函数

多态使用条件

* 父类指针或引用指向子类对象

重写：函数返回值类型  函数名 参数列表 完全一致称为重写









#### 4.7.2 多态案例一-计算器类



案例描述：

分别利用普通写法和多态技术，设计实现两个操作数进行运算的计算器类



多态的优点：

* 代码组织结构清晰
* 可读性强
* 利于前期和后期的扩展以及维护



**示例：**

```C++
//普通实现
class Calculator {
public:
	int getResult(string oper)
	{
		if (oper == "+") {
			return m_Num1 + m_Num2;
		}
		else if (oper == "-") {
			return m_Num1 - m_Num2;
		}
		else if (oper == "*") {
			return m_Num1 * m_Num2;
		}
		//如果要提供新的运算，需要修改源码
	}
public:
	int m_Num1;
	int m_Num2;
};

void test01()
{
	//普通实现测试
	Calculator c;
	c.m_Num1 = 10;
	c.m_Num2 = 10;
	cout << c.m_Num1 << " + " << c.m_Num2 << " = " << c.getResult("+") << endl;

	cout << c.m_Num1 << " - " << c.m_Num2 << " = " << c.getResult("-") << endl;

	cout << c.m_Num1 << " * " << c.m_Num2 << " = " << c.getResult("*") << endl;
}



//多态实现
//抽象计算器类
//多态优点：代码组织结构清晰，可读性强，利于前期和后期的扩展以及维护
class AbstractCalculator
{
public :

	virtual int getResult()
	{
		return 0;
	}

	int m_Num1;
	int m_Num2;
};

//加法计算器
class AddCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 + m_Num2;
	}
};

//减法计算器
class SubCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 - m_Num2;
	}
};

//乘法计算器
class MulCalculator :public AbstractCalculator
{
public:
	int getResult()
	{
		return m_Num1 * m_Num2;
	}
};


void test02()
{
	//创建加法计算器
	AbstractCalculator *abc = new AddCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " + " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;  //用完了记得销毁

	//创建减法计算器
	abc = new SubCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " - " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;  

	//创建乘法计算器
	abc = new MulCalculator;
	abc->m_Num1 = 10;
	abc->m_Num2 = 10;
	cout << abc->m_Num1 << " * " << abc->m_Num2 << " = " << abc->getResult() << endl;
	delete abc;
}

int main() {

	//test01();

	test02();

	system("pause");

	return 0;
}
```

> 总结：C++开发提倡利用多态设计程序架构，因为多态优点很多

















#### 4.7.3 纯虚函数和抽象类



在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容



因此可以将虚函数改为**纯虚函数**



纯虚函数语法：`virtual 返回值类型 函数名 （参数列表）= 0 ;`



当类中有了纯虚函数，这个类也称为==抽象类==



**抽象类特点**：

 * 无法实例化对象
 * 子类必须重写抽象类中的纯虚函数，否则也属于抽象类





**示例：**

```C++
class Base
{
public:
	//纯虚函数
	//类中只要有一个纯虚函数就称为抽象类
	//抽象类无法实例化对象
	//子类必须重写父类中的纯虚函数，否则也属于抽象类
	virtual void func() = 0;
};

class Son :public Base
{
public:
	virtual void func() 
	{
		cout << "func调用" << endl;
	};
};

void test01()
{
	Base * base = NULL;
	//base = new Base; // 错误，抽象类无法实例化对象
	base = new Son;
	base->func();
	delete base;//记得销毁
}

int main() {

	test01();

	system("pause");

	return 0;
}
```















#### 4.7.4 多态案例二-制作饮品

**案例描述：**

制作饮品的大致流程为：煮水 -  冲泡 - 倒入杯中 - 加入辅料



利用多态技术实现本案例，提供抽象制作饮品基类，提供子类制作咖啡和茶叶



![1545985945198](assets/1545985945198.png)



**示例：**

```C++
//抽象制作饮品
class AbstractDrinking {
public:
	//烧水
	virtual void Boil() = 0;
	//冲泡
	virtual void Brew() = 0;
	//倒入杯中
	virtual void PourInCup() = 0;
	//加入辅料
	virtual void PutSomething() = 0;
	//规定流程
	void MakeDrink() {
		Boil();
		Brew();
		PourInCup();
		PutSomething();
	}
};

//制作咖啡
class Coffee : public AbstractDrinking {
public:
	//烧水
	virtual void Boil() {
		cout << "煮农夫山泉!" << endl;
	}
	//冲泡
	virtual void Brew() {
		cout << "冲泡咖啡!" << endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << "将咖啡倒入杯中!" << endl;
	}
	//加入辅料
	virtual void PutSomething() {
		cout << "加入牛奶!" << endl;
	}
};

//制作茶水
class Tea : public AbstractDrinking {
public:
	//烧水
	virtual void Boil() {
		cout << "煮自来水!" << endl;
	}
	//冲泡
	virtual void Brew() {
		cout << "冲泡茶叶!" << endl;
	}
	//倒入杯中
	virtual void PourInCup() {
		cout << "将茶水倒入杯中!" << endl;
	}
	//加入辅料
	virtual void PutSomething() {
		cout << "加入枸杞!" << endl;
	}
};

//业务函数
void DoWork(AbstractDrinking* drink) {
	drink->MakeDrink();
	delete drink;
}

void test01() {
	DoWork(new Coffee);
	cout << "--------------" << endl;
	DoWork(new Tea);
}


int main() {

	test01();

	system("pause");

	return 0;
}
```



















#### 4.7.5 虚析构和纯虚析构



多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码



解决方式：将父类中的析构函数改为**虚析构**或者**纯虚析构**



虚析构和纯虚析构共性：

* 可以解决父类指针释放子类对象
* 都需要有具体的函数实现

虚析构和纯虚析构区别：

* 如果是纯虚析构，该类属于抽象类，无法实例化对象



虚析构语法：

`virtual ~类名(){}`

纯虚析构语法：

` virtual ~类名() = 0;`

`类名::~类名(){}`



**示例：**

```C++
class Animal {
public:

	Animal()
	{
		cout << "Animal 构造函数调用！" << endl;
	}
	virtual void Speak() = 0;

	//析构函数加上virtual关键字，变成虚析构函数
	//virtual ~Animal()
	//{
	//	cout << "Animal虚析构函数调用！" << endl;
	//}


	virtual ~Animal() = 0;
};

Animal::~Animal()
{
	cout << "Animal 纯虚析构函数调用！" << endl;
}

//和包含普通纯虚函数的类一样，包含了纯虚析构函数的类也是一个抽象类。不能够被实例化。

class Cat : public Animal {
public:
	Cat(string name)
	{
		cout << "Cat构造函数调用！" << endl;
		m_Name = new string(name);
	}
	virtual void Speak()
	{
		cout << *m_Name <<  "小猫在说话!" << endl;
	}
	~Cat()
	{
		cout << "Cat析构函数调用!" << endl;
		if (this->m_Name != NULL) {
			delete m_Name;
			m_Name = NULL;
		}
	}

public:
	string *m_Name;
};

void test01()
{
	Animal *animal = new Cat("Tom");
	animal->Speak();

	//通过父类指针去释放，会导致子类对象可能清理不干净，造成内存泄漏
	//怎么解决？给基类增加一个虚析构函数
	//虚析构函数就是用来解决通过父类指针释放子类对象
	delete animal;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



总结：

​	1. 虚析构或纯虚析构就是用来解决通过父类指针释放子类对象

​	2. 如果子类中没有堆区数据，可以不写为虚析构或纯虚析构

​	3. 拥有纯虚析构函数的类也属于抽象类















#### 4.7.6 多态案例三-电脑组装



**案例描述：**



电脑主要组成部件为 CPU（用于计算），显卡（用于显示），内存条（用于存储）

将每个零件封装出抽象基类，并且提供不同的厂商生产不同的零件，例如Intel厂商和Lenovo厂商

创建电脑类提供让电脑工作的函数，并且调用每个零件工作的接口

测试时组装三台不同的电脑进行工作





**示例：**

```C++
#include<iostream>
using namespace std;

//抽象CPU类
class CPU
{
public:
	//抽象的计算函数
	virtual void calculate() = 0;
};

//抽象显卡类
class VideoCard
{
public:
	//抽象的显示函数
	virtual void display() = 0;
};

//抽象内存条类
class Memory
{
public:
	//抽象的存储函数
	virtual void storage() = 0;
};

//电脑类
class Computer
{
public:
	Computer(CPU * cpu, VideoCard * vc, Memory * mem)
	{
		m_cpu = cpu;
		m_vc = vc;
		m_mem = mem;
	}

	//提供工作的函数
	void work()
	{
		//让零件工作起来，调用接口
		m_cpu->calculate();

		m_vc->display();

		m_mem->storage();
	}

	//提供析构函数 释放3个电脑零件
	~Computer()
	{

		//释放CPU零件
		if (m_cpu != NULL)
		{
			delete m_cpu;
			m_cpu = NULL;
		}

		//释放显卡零件
		if (m_vc != NULL)
		{
			delete m_vc;
			m_vc = NULL;
		}

		//释放内存条零件
		if (m_mem != NULL)
		{
			delete m_mem;
			m_mem = NULL;
		}
	}

private:

	CPU * m_cpu; //CPU的零件指针
	VideoCard * m_vc; //显卡零件指针
	Memory * m_mem; //内存条零件指针
};

//具体厂商
//Intel厂商
class IntelCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Intel的CPU开始计算了！" << endl;
	}
};

class IntelVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Intel的显卡开始显示了！" << endl;
	}
};

class IntelMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Intel的内存条开始存储了！" << endl;
	}
};

//Lenovo厂商
class LenovoCPU :public CPU
{
public:
	virtual void calculate()
	{
		cout << "Lenovo的CPU开始计算了！" << endl;
	}
};

class LenovoVideoCard :public VideoCard
{
public:
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了！" << endl;
	}
};

class LenovoMemory :public Memory
{
public:
	virtual void storage()
	{
		cout << "Lenovo的内存条开始存储了！" << endl;
	}
};


void test01()
{
	//第一台电脑零件
	CPU * intelCpu = new IntelCPU;
	VideoCard * intelCard = new IntelVideoCard;
	Memory * intelMem = new IntelMemory;

	cout << "第一台电脑开始工作：" << endl;
	//创建第一台电脑
	Computer * computer1 = new Computer(intelCpu, intelCard, intelMem);
	computer1->work();
	delete computer1;

	cout << "-----------------------" << endl;
	cout << "第二台电脑开始工作：" << endl;
	//第二台电脑组装
	Computer * computer2 = new Computer(new LenovoCPU, new LenovoVideoCard, new LenovoMemory);;
	computer2->work();
	delete computer2;

	cout << "-----------------------" << endl;
	cout << "第三台电脑开始工作：" << endl;
	//第三台电脑组装
	Computer * computer3 = new Computer(new LenovoCPU, new IntelVideoCard, new LenovoMemory);;
	computer3->work();
	delete computer3;

}
```













## 5 文件操作



程序运行时产生的数据都属于临时数据，程序一旦运行结束都会被释放

通过**文件可以将数据持久化**

C++中对文件操作需要包含头文件 ==&lt; fstream &gt;==



文件类型分为两种：

1. **文本文件**     -  文件以文本的**ASCII码**形式存储在计算机中
2. **二进制文件** -  文件以文本的**二进制**形式存储在计算机中，用户一般不能直接读懂它们



操作文件的三大类:

1. ofstream：写操作
2. ifstream： 读操作
3. fstream ： 读写操作



### 5.1文本文件

#### 5.1.1写文件

   写文件步骤如下：

1. 包含头文件   

     \#include <fstream\>

2. 创建流对象  

   ofstream ofs;

3. 打开文件

   ofs.open("文件路径",打开方式);

4. 写数据

   ofs << "写入的数据";

5. 关闭文件

   ofs.close();

   

文件打开方式：

| 打开方式    | 解释                       |
| ----------- | -------------------------- |
| ios::in     | 为读文件而打开文件         |
| ios::out    | 为写文件而打开文件         |
| ios::ate    | 初始位置：文件尾           |
| ios::app    | 追加方式写文件             |
| ios::trunc  | 如果文件存在先删除，再创建 |
| ios::binary | 二进制方式                 |

**注意：** 文件打开方式可以配合使用，利用|操作符

**例如：**用二进制方式写文件 `ios::binary |  ios:: out`





**示例：**

```C++
#include <fstream>

void test01()
{
	ofstream ofs;
	ofs.open("test.txt", ios::out);

	ofs << "姓名：张三" << endl;
	ofs << "性别：男" << endl;
	ofs << "年龄：18" << endl;

	ofs.close();
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

* 文件操作必须包含头文件 fstream
* 读文件可以利用 ofstream  ，或者fstream类
* 打开文件时候需要指定操作文件的路径，以及打开方式
* 利用<<可以向文件中写数据
* 操作完毕，要关闭文件

















#### 5.1.2读文件



读文件与写文件步骤相似，但是读取方式相对于比较多



读文件步骤如下：

1. 包含头文件   

     \#include <fstream\>

2. 创建流对象  

   ifstream ifs;

3. 打开文件并判断文件是否打开成功

   ifs.open("文件路径",打开方式);

4. 读数据

   四种方式读取

5. 关闭文件

   ifs.close();



**示例：**

```C++
#include <fstream>
#include <string>
void test01()
{
	ifstream ifs;
	ifs.open("test.txt", ios::in);

	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		return;
	}

	//第一种方式
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}

	//第二种
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))
	//{
	//	cout << buf << endl;
	//}

	//第三种
	//string buf;
	//while (getline(ifs, buf))
	//{
	//	cout << buf << endl;
	//}

	char c;
	while ((c = ifs.get()) != EOF)
	{
		cout << c;
	}

	ifs.close();


}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

- 读文件可以利用 ifstream  ，或者fstream类
- 利用is_open函数可以判断文件是否打开成功
- close 关闭文件 















### 5.2 二进制文件

以二进制的方式对文件进行读写操作

打开方式要指定为 ==ios::binary==



#### 5.2.1 写文件

二进制方式写文件主要利用流对象调用成员函数write

函数原型 ：`ostream& write(const char * buffer,int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数



**示例：**

```C++
#include <fstream>
#include <string>

class Person
{
public:
	char m_Name[64];
	int m_Age;
};

//二进制文件  写文件
void test01()
{
	//1、包含头文件

	//2、创建输出流对象
	ofstream ofs("person.txt", ios::out | ios::binary);
	
	//3、打开文件
	//ofs.open("person.txt", ios::out | ios::binary);

	Person p = {"张三"  , 18};

	//4、写文件
	ofs.write((const char *)&p, sizeof(p));

	//5、关闭文件
	ofs.close();
}

int main() {

	test01();

	system("pause");

	return 0;
}
```

总结：

* 文件输出流对象 可以通过write函数，以二进制方式写数据











#### 5.2.2 读文件

二进制方式读文件主要利用流对象调用成员函数read

函数原型：`istream& read(char *buffer,int len);`

参数解释：字符指针buffer指向内存中一段存储空间。len是读写的字节数

示例：

```C++
#include <fstream>
#include <string>

class Person
{
public:
	char m_Name[64];
	int m_Age;
};

void test01()
{
	ifstream ifs("person.txt", ios::in | ios::binary);
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
	}

	Person p;
	ifs.read((char *)&p, sizeof(p));

	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

int main() {

	test01();

	system("pause");

	return 0;
}
```



- 文件输入流对象 可以通过read函数，以二进制方式读数据

