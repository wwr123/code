#include<iostream>
using namespace std;

//��Ϊ���캯��������������Ϊ˽�еģ����������ܱ��̳�
//ȱ�ݣ���ֻ���ڶ������ɣ�������ջ�����ɡ�
class A
{
public:
	static A& GetObject(int a)
	{
		return *new A(a);
	}
private: //�ѹ��캯������Ϊ˽�е�
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
//��������̳���ʵ�֣������ڶ��ϴ�������Ҳ������ջ�ϴ�������
template <typename T>
class C
{
	friend T;  //��Ԫ����
private:
	C()
	{}
	~C(){}
	int _a;
};
class D:virtual public C<D>    //D��C����Ԫ���ͣ�����D���Է���C��˽�к�������ʵ�ִ�������
{
public:
	D(){}  
	~D(){}
};        //D���ܱ��̳�