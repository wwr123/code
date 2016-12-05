#pragma once
#include<vector>
template<class T>
class ObjectPool
{
protected:
	struct Node
	{
		void* _memory;// �ڴ��
		Node* _next; //ָ����һ��ڵ��ָ��
		size_t _objectNum;//ͳ���ڴ����ĸ���
		Node(size_t objectNum)
			:_objectNum(objectNum)
			,_next(NULL)
		{
			_memory=malloc(_iteamSize*_objectNum);
		}
	};
	size_t _countIn;//��ǰ�ڵ����õĸ���
	Node* _frist;
	Node* _last;
	size_t _maxNum; //�ڵ������ڴ������С
    static size_t _iteamSize;//��������Ĵ�С
	T* _lastDelete;
public:
	static size_t initIteam()
	{
		if(sizeof(T)>=sizeof(void*))
			return sizeof(T);
		else
			return sizeof(void*);
	}
	ObjectPool(size_t initNum=32,size_t maxNum=10000)
		:_countIn(0)
		,_maxNum(maxNum)
		,_lastDelete(NULL)
	{
		if(initNum>maxNum)
			initNum=maxNum;
		_frist=new Node(initNum);
		_last=_frist;
	}
	T* New()
	{
		if(_lastDelete)
		{
			T* obj=_lastDelete;  
			_lastDelete=*((T**)_lastDelete);
			return new (obj)T();//new�Ķ�λ���ʽ
		}
		else  //û���ͷŵ��ڴ����
		{
			if(_countIn>=_last->_objectNum)
				AllocateNewNode();
			T* obj=(T*)((char*)_last->_memory+_countIn*_iteamSize);
		    _countIn++;
			return new (obj)T();  //obj�ǵ�ַ��T������
		}
	}
	void AllocateNewNode()
	{
		size_t objectNum=_last->_objectNum*2;
		if(objectNum>_maxNum)
			objectNum=_maxNum;
		_last->_next=new Node(objectNum);
		_last=_last->_next;
		_countIn=0;
	}
	void Delete(T* ptr)
	{
		if(ptr)
		{
			*((T**)ptr)=_lastDelete;
			_lastDelete=ptr;
		}
	}
	void Destory()
	{
		Node* cur=_frist;
		while(cur)
		{
			Node* del=cur;
			cur=cur->_next;
			delete del;
		}
		_countIn=0;
		_frist=_last=NULL;
	}
	~ObjectPool()
	{
		Destory();
	}
};
template<class T>   //��̬�ĳ�Ա����������������г�ʼ��
size_t  ObjectPool<T>::_iteamSize =ObjectPool<T>::initIteam ();


// �����ڴ����صĳ���ʹ�ú��ڴ������ظ�ʹ��
void TestObjectPool()
{
	vector<string*> v;

	ObjectPool<string> pool;
	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	v.push_back(pool.New());
	printf("Pool New : %p\n", v.back());
}

#include <Windows.h>

// ��Ե�ǰ���ڴ����ؽ��м򵥵����ܲ���
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 10000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// ���������ͷ�5��
	begin = GetTickCount();
	ObjectPool<string> pool;
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}


	end = GetTickCount();
	cout<<"Pool:"<<end - begin<<endl;

	cout<<"new/delete==============================="<<endl;
	begin = GetTickCount();

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	end = GetTickCount();
	cout<<"new/delete:"<<end - begin<<endl;
}