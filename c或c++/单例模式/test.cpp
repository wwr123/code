#include<iostream>
using namespace std;
#include<stdlib.h>
//����ģʽ--��ֻ��ʵ��һ��ʵ��
//���߳��²���ȫ--��new Singleton����ԭ�Ӳ���
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
//	static Singleton* _inst;  //��̬�ĳ�Ա��������г�ʼ��
//};
//Singleton* Singleton::_inst =NULL;


//����ģʽ--���̰߳�ȫ���---������
//#include<mutex.h>
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		//��ֻ��һ��ifʱ������_instΪ��Ϊ�գ������ȡ����Ч�ʵ�
//		if(_inst==NULL) 
//		{
//			//lock();  pthread_mutex_lock  ˵��Ҫ����
//			lock_guard<mutex>lkl(_mux); 
//			//c++11�����ڼ���������metux���ʹ�ã������ŵ����У�
//			//mutex�Զ���������������ʱ��ͬʱmutex����
//			if(_inst==NULL)
//			{
//				_inst=new Singleton;
//				//����Ϊ3����1.����ռ䣬2.���ù��캯����3.��ֵ
//				//���������2 3������ָ��Ľ�����
//				//��ʱ�̻߳����һ��δ��ʼ���Ķ�������ڴ�й¶
//				//�������--�������ڴ���դ
//				//Singleton* tmp=new Singleton;
//				//Memorybarrier();
//				//_inst=tmp;
//				
//			}
//			//unlock();  ����
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
//	static Singleton* _inst;  //��̬�ĳ�Ա��������г�ʼ��
//	static mutex _mux; // ��֤����̹߳���һ�ѻ�����
//};
//Singleton* Singleton::_inst =NULL;


//RAII--��ʵ��һ���Զ�����������
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
//	static Singleton* _inst;  //��̬�ĳ�Ա��������г�ʼ��
//  static mutex _mtx;
//};
//Singleton* Singleton::_inst =NULL;

//����ģʽ--�����ü���
//��ʽ1����main����֮ǰ���Ѿ������˶���
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
//	static Singleton* _inst;  //��̬�ĳ�Ա��������г�ʼ��
//};
//Singleton* Singleton::_inst =new Singleton;

//����ģʽ--�����ü���
//��ʽ2���ڵ�һ�ε���ʱ����
//class Singleton
//{
//public:
//	static Singleton* GetSingleton()
//	{
//		static Singleton _inst;  //����һ����̬�Ķ���
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

//RAII �����Զ�����ʵ������ķ�ʽ
//��һЩ�ļ��������ݿ�...�������ų���Ĺرն������ͷ���Դ����Ҫ�ֶ��ͷ�
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
	//����������
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
	static Singleton* _inst;  //��̬�ĳ�Ա��������г�ʼ��
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