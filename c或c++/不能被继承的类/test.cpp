#include<iostream>
using namespace std;

//因为构造函数和析构函数都为私有的，所以他不能被继承
//缺陷：它只能在堆上生成，不能在栈上生成。
class A
{
public:
	static A& GetObject(int a)
	{
		return *new A(a);
	}
private: //把构造函数声明为私有的
	A(int a)
	{
		_a=a;
	}
	~A()
	{
		delete this;
	}
	int _a;
};
//所以用虚继承来实现，可以在堆上创建对象，也可以在栈上创建对象
template <typename T>
class C
{
	friend T;  //友元类型
private:
	C()
	{}
	~C(){}
	int _a;
};
class D:virtual public C<D>    //D是C的友元类型，所以D可以访问C的私有函数，来实现创建对象
{
public:
	D(){}  
	~D(){}
};        //D不能被继承