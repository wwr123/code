#include<iostream>
using namespace std;
#include<cstdlib>
#include<cassert>
#include<cstdio>
#include<stack>
//#include<queue>
//实现一个栈，Push,Pop,Min O(1)

//思路：用已有的栈来完成时间复杂度为O（1）的栈

//template<class T>
//class Stack
//{
//public:
//	Stack()                  //datastack  push 2 3  1 4 pop  2 3  pop 2 
//	{}                       //minstack        2 2  1 1      2 3      2
//	~Stack()
//	{}
//	void Push(const T& x)       
//	{                           
//		datastack.push (x);
//		if(minstack.size() ==0||x<minstack.top ())    //把当前最小值push到辅助栈中
//		{
//			minstack.push (x);
//		}
//		else
//			minstack.push (minstack.top ());
//	}
//	void Pop()
//	{
//		datastack.pop ();
//		minstack.pop ();
//	}
//	T& Min()
//	{
//		return minstack.top ();
//	}
//private:
//	stack<T> datastack;  //数据栈
//	stack<T> minstack;   //辅助栈
//};
//void test1()
//{
//	Stack<int> s;
//	s.Push (7);
//	s.Push (3);
//	s.Push (2);
//	s.Push (4);
//	s.Push (6);
//	cout<<s.Min ()<<endl;
//}

//使用两个栈实现一个队列

//思路：用两个栈相互倒来实现队列

//template<class T>
//class Queue
//{
//public:
//	Queue() {}
//	~Queue() {}
//	void Push(const T& x)
//	{
//		s1.push (x);
//	}
//	void Pop()
//	{
//		while(!s1.empty ())   //s1 1 2 3        s2 3 2 
//		{
//			if(s1.size ()==1)
//			{
//				s1.pop ();
//		    }
//		    else
//		    {
//				s2.push (s1.top ());
//				s1.pop ();
//		    }
//		}
//		while(!s2.empty ())  //s2 3 2       s1 2 3
//		{
//			s1.push (s2.top ());
//			s2.pop ();
//		}
//	}
//	T& Front()
//	{
//		T tmp;
//		while(!s1.empty ())  //s1   1 2 3
//		{
//			if(s1.size ()==1)
//			{
//			   tmp=s1.top ();   
//			}
//			s2.push (s1.top ());
//			s1.pop ();
//		}
//		while(!s2.empty ())
//		{
//			s1.push (s2.top ());
//			s2.pop ();
//		}
//		return tmp;
//	}
//	T& Back()
//	{
//		return s1.top ();
//	}
//	bool Empty()
//	{
//		return s1.empty();
//	}
//	size_t Size()
//	{
//		return s1.size ();
//	}
//private:
//	stack<T> s1;
//	stack<T> s2;
//};
//void test2()
//{
//	Queue<int> q;   //先进先出
//	q.Push (1);
//	q.Push (2);
//	q.Push (3);
//	q.Push (4);
//	q.Pop ();
//	cout<<q.Front ()<<endl;   //2
//	cout<<q.Back ()<<endl;    //4
//	cout<<q.Empty ()<<endl;   //0
//	cout<<q.Size() <<endl;    //3
//}

//使用两个队列实现一个栈

//template<typename T>
//class Stack
//{
//public:
//	Stack(){}
//	~Stack(){}
//	void Push(T x)
//	{
//		s1.push ( x);
//	}
//    void Pop()
//	{
//	    while(!s1.empty ())        //s1   1 2 3
//	    {
//		   if(s1.front ()!=s1.back ())  
//		   {
//			   s2.push (s1.front ());        //s2   1 2 
//		   }
//		   s1.pop ();
//	   }
//	   while(!s2.empty ())        //s1    1 2
//	   {
//		s1.push (s2.front ());
//        s2.pop ();
//	   }
//    }
//	T& Top()
//	{
//		T tmp;
//	    while(!s1.empty ())    //s1   1 2 3 
//	    {
//		    if(s1.front ()==s1.back ()) //tmp=3
//		    {
//			   tmp=s1.front();   
//		    }
//		    s2.push (s1.front ());  //s2   1 2 3
//		    s1.pop ();
//		}
//		while(!s2.empty ())
//	   {
//		   s1.push (s2.front ());
//           s2.pop ();
//	   }
//	//top()
//	//tmp=s1.back ();
//	   return tmp;
//    }
//	size_t Size()
//	{
//		return s1.size ();
//	}
//	bool Empty()
//	{
//		return s1.empty ();
//	}
//private:
//	queue<T> s1;
//	queue<T> s2;
//};
//
//void test()
//{
//	Stack<int> s;
//	s.Push (1);
//	s.Push (2);
//	s.Push (3);
//	s.Pop ();
//	while(!s.Empty ())
//	{
//		cout<<s.Top ()<<" ";   //2 1
//		s.Pop ();
//	}
//	cout<<endl;
//
//}
//

//判断元素出栈，入栈的合法性
bool IsLegal(int PushStack[],int PopStack[],int len1,int len2)
{
	int j=0;
	stack<int> s;
	for(int i=0;i<len1;i++)
	{
		if((PushStack[i]==PopStack[j]))
		{
			j++;
		}
		else if((PopStack[j]==PushStack[i-2]))
		{
			j++;
			i--;
		}
		else
		{
			s.push (PushStack[i]);
		}
	}
	while(j<len2)
	{
		if(s.top ()==PopStack[j])
		{
			s.pop ();
			j++;
		}
		else
			break;
	}
	if(j==len2)
	{
		return true;
	}
	else 
		return false;
}
 
void test()
{
	int PushStack[]={1,2,3,4,5};
	int PopStack[]={2,1,4,3,5};
	bool ret=IsLegal(PushStack,PopStack,5,5);
	cout<<ret<<endl;
}



//一个数组实现两个栈

//template<class T>
//class Twostack      //从两边向中间
//{
//public:
//	Twostack()
//		:_top1(0)
//		,_top2(0)
//		,_capacity(0)
//		,_a(0)
//	{}
//	~Twostack() 
//	{
//		if(_a)
//		{
//			delete[] _a;
//		}
//	}
//	void Push1(const T& x)
//	{
//		CheckCapacity();
//		_a[_top1++]=x;
//	}
//	void Pop1()
//	{
//		--_top1;
//	}
//	T& Top1()
//	{
//		return _a[_top1-1];
//	}
//	T& Top2()
//	{
//		return _a[_top2+1];
//	}
//	bool Empty1()
//	{
//		return _top1==0;
//	}
//	bool Empty2()
//	{
//		return _top2==0;
//	}
//	size_t Size1()
//	{
//		return _top1;
//	}
//	size_t Size2()
//	{
//		return _capacity-1-_top2;
//	}
//	void Pop2()
//	{
//		++_top2;
//	}
//	void Push2(const T& x)
//	{
//		CheckCapacity();
//		_a[_top2--]=x;
//	}
//	void CheckCapacity()
//	{
//		T* tmp;
//		if(_a==NULL)
//		{
//			_capacity+=10;
//			_a=new T[_capacity];
//			_top2=_capacity-1;
//		}
//		if(_top1==_top2)
//		{
//			int Newcapacity=2*_capacity;
//			tmp=new T[Newcapacity];
//			for(int i=0;i<_top1;i++)
//			{
//				tmp[i]=_a[i];
//			}
//			for(int j=_capacity-1,i=Newcapacity-1;j>_top2;j--,i--)
//			{
//				tmp[i]=_a[j];
//			}
//			_capacity=Newcapacity;
//			delete[] _a;
//		    _a=tmp;
//		    _top2+=_capacity/2;      //
//		}
//		
//	}
//	void Display()
//	{
//		for(int i=_top1-1;i>=0;i--)
//		{
//			cout<<_a[i]<<" ";
//		}
//		cout<<endl;
//		for(int j=_top2+1;j<=_capacity-1;j++)
//		{
//			cout<<_a[j]<<" ";
//		}
//		cout<<endl;
//	}
//private:
//	int _capacity;
//	T* _a;          //指向数组的指针
//	int _top1;     
//	int _top2;
//};
//void test()
//{
//	Twostack<int> s;
//	s.Push1 (1);
//	s.Push1 (2);
//	s.Pop1 ();
//	s.Push1 (3);
//	s.Push2 (4);
//	s.Push2 (5);
//	s.Pop2 ();
//	s.Push2 (6);
//	cout<<s.Size1 ()<<endl;
//	cout<<s.Size2 ()<<endl;
//
//	/*cout<<s.Empty1 ()<<endl;
//	cout<<s.Empty2 ()<<endl;*/
//
//	/*cout<<s.Top1()<<endl;
//	cout<<s.Top2 ()<<endl;
//	s.Display ();*/
//}
int main()
{
	test();
	system("pause");
	return 0;
}