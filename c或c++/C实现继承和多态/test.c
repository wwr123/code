#include<stdio.h>
#include<stdlib.h>
//实现继承
//子类可以调用父类的成员函数和成员变量
//因为结构体中无函数，故用函数指针来实现
typedef void (*ss)();
struct A
{
	ss s;
	int a;
};
struct B
{
	struct A _a;
	int b;
};
void f1()
{
	printf("father de f1()...\n");
}
void fun1()
{
	struct A _a;
	struct B _b;
	_b._a.a =1;
	_b._a.s =f1; 
	_b.b=2;
	printf("child--->father:%d\n",_b._a.a);
	_b._a .s();   //调用fun函数
}
//实现多态
//多态--》子类对父类的虚函数进行重写（函数名，参数，返回值都相同，协变除外），
//父类的指针/引用调用重写的虚函数时，当指向父类的对象就是父类的虚函数，
//当指向子类调用的，就是子类的虚函数

typedef void (*Fun)();  //定义了一个Fun类型的函数指针
	//因为C的结构体中不能包含函数，故用函数指针来实现
struct C
{
	Fun fun; //为Fun类型定义一个变量
	int a;
	int b;
};
struct D
{
	struct C c;
};
void PrintfC()
{
	printf("C is father....\n");
}
void PrintfD()
{
	printf("D is child......\n");
}
void fun2()
{
	struct C cc;
	struct D dd;
	struct C* c1;
	cc.fun =PrintfC;  
	dd.c .fun=PrintfD;
	c1=&cc;
	c1->fun();   //调用父类虚函数
	c1=(struct C*)&dd;
	c1->fun();   //调用子类的虚函数
}
int main()
{
	fun1();
	fun2();
	system("pause");
	return 0;
}