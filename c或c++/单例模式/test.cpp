#include<iostream>
using namespace std;
#include<stdlib.h>
//单例模式--》只能实现一个实例
//多线程下不安全--》new Singleton不是原子操作
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		if(_inst==NULL)
//		{
//			_inst=new Singleton;
//		}
//		return _inst;
//	}
//	void Printf()
//	{
//		cout<<"Singleton: "<<_inst<<endl;
//	}
//private:
//	Singleton()
//	{}
//	~Singleton()
//	{}
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//	static Singleton* _inst;  //静态的成员在类外进行初始化
//};
//Singleton* Singleton::_inst =NULL;


//懒汉模式--》线程安全情况---》加锁
//#include<mutex.h>
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		//当只有一个if时，不管_inst为不为空，都会获取锁，效率低
//		if(_inst==NULL) 
//		{
//			//lock();  pthread_mutex_lock  说明要加锁
//			lock_guard<mutex>lkl(_mux); 
//			//c++11中用于加锁，它与metux配合使用，把锁放到它中，
//			//mutex自动上锁，当它析构时，同时mutex解锁
//			if(_inst==NULL)
//			{
//				_inst=new Singleton;
//				//它分为3步，1.分配空间，2.调用构造函数，3.赋值
//				//编译器会对2 3步进行指令的交换，
//				//那时线程会调用一个未初始化的对象，造成内存泄露
//				//解决方案--》加入内存栏栅
//				//Singleton* tmp=new Singleton;
//				//Memorybarrier();
//				//_inst=tmp;
//				
//			}
//			//unlock();  解锁
//		}
//		return _inst;
//	}
//	void Printf()
//	{
//		cout<<"Singleton: "<<_inst<<endl;
//	}
//private:
//	Singleton()
//	{}
//	~Singleton()
//	{}
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//	static Singleton* _inst;  //静态的成员在类外进行初始化
//	static mutex _mux; // 保证多个线程公用一把互斥锁
//};
//Singleton* Singleton::_inst =NULL;


//RAII--》实现一个自动管理锁的类
//class AutoLock
//{
//public:
//	AutoLock(const mutex& _mtx)
//	{
//		_mtx.lock();
//	}
//	~AutoLock()
//	{
//		_mtx.unlock();
//	}
//};
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//      if(_inst==NULL)
//      {
//			AutoLock(_mtx);
//			if(_inst==NULL)
//			{
//				_inst=new Singleton;
//		    }
//      }
//		return _inst;
//	}
//	void Printf()
//	{
//		cout<<"Singleton: "<<_inst<<endl;
//	}
//private:
//	Singleton()
//	{}
//	~Singleton()
//	{}
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//	static Singleton* _inst;  //静态的成员在类外进行初始化
//  static mutex _mtx;
//};
//Singleton* Singleton::_inst =NULL;

//饿汉模式--》不用加锁
//方式1：在main函数之前就已经创建了对象
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		return _inst;
//	}
//	void Printf()
//	{
//		cout<<"Singleton: "<<_inst<<endl;
//	}
//private:
//	Singleton()
//	{}
//	~Singleton()
//	{}
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//	static Singleton* _inst;  //静态的成员在类外进行初始化
//};
//Singleton* Singleton::_inst =new Singleton;

//饿汉模式--》不用加锁
//方式2：在第一次调用时创建
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		static Singleton _inst;  //创建一个静态的对象
//		return &_inst;
//	}
//	void Printf()
//	{
//		cout<<"Singleton: "<<endl;
//	}
//private:
//	Singleton()
//	{}
//	~Singleton()
//	{}
//	Singleton(const Singleton&);
//	Singleton& operator=(const Singleton&);
//};

//RAII 具有自动回收实例对象的方式
//有一些文件锁，数据库...不会随着程序的关闭而立即释放资源，需要手动释放
class Singleton
{
public:
	static Singleton* GetSingleton()
	{
		return _inst;
	}
	void Printf()
	{
		cout<<"Singleton: "<<_inst<<endl;
	}
	//垃圾回收类
	class GC
	{
	public:
		GC(){}
		~GC()
		{
			if(_inst)
			{
				cout<<"delete _inst"<<endl;
				delete _inst;
			}
		}
	};
private:
	Singleton()
	{}
	~Singleton()
	{}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
	static Singleton* _inst;  //静态的成员在类外进行初始化
};
Singleton* Singleton::_inst =new Singleton;
void fun1()
{
	Singleton::GC gc;
	Singleton* p1=Singleton::GetSingleton();
	Singleton* p2=Singleton::GetSingleton();
	Singleton* p3=Singleton::GetSingleton();
	p1->Printf ();
	p2->Printf ();
	p3->Printf ();
}
int main()
{
	fun1();
	system("pause");
	return 0;
}