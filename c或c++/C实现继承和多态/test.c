#include<stdio.h>
#include<stdlib.h>
//ʵ�ּ̳�
//������Ե��ø���ĳ�Ա�����ͳ�Ա����
//��Ϊ�ṹ�����޺��������ú���ָ����ʵ��
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
	_b._a .s();   //����fun����
}
//ʵ�ֶ�̬
//��̬--������Ը�����麯��������д��������������������ֵ����ͬ��Э����⣩��
//�����ָ��/���õ�����д���麯��ʱ����ָ����Ķ�����Ǹ�����麯����
//��ָ��������õģ�����������麯��

typedef void (*Fun)();  //������һ��Fun���͵ĺ���ָ��
	//��ΪC�Ľṹ���в��ܰ������������ú���ָ����ʵ��
struct C
{
	Fun fun; //ΪFun���Ͷ���һ������
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
	c1->fun();   //���ø����麯��
	c1=(struct C*)&dd;
	c1->fun();   //����������麯��
}
int main()
{
	fun1();
	fun2();
	system("pause");
	return 0;
}