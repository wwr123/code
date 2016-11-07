#pragma once
#include<vector>
//enum State
//{
//	EXIST,
//	EMPTY,
//	DELETE,
//};
////�º���==>��������
//struct __StringHashFunc
//{
//	static size_t BKDRHash(const char*str)
//	{
//		unsigned int seed= 131;// 31 131 1313 13131 131313 
//		unsigned int hash= 0;
//		while(*str)
//		{
//		hash=hash*seed+ (*str++);
//		}
//		return(hash& 0x7FFFFFFF);
//	}
//	size_t operator()(const string& s)
//	{
//		return BKDRHash(s.c_str());
//	}
//};
//template<class K>
//struct __HashFunc
//{
//	size_t operator()(const K& key)
//	{
//		return key;
//	}
//};
//
////�ػ�
////template<class K>
////struct __HashFunc
////{
////	size_t operator()(K& key)
////	{
////		return key;
////	}
////};
////template<>
////struct __HashFunc<string>
////{
////	static size_t BKDRHash(const char*str)
////	{
////		unsigned int seed= 131;// 31 131 1313 13131 131313 
////		unsigned int hash= 0;
////		while(*str)
////		{
////		hash=hash*seed+ (*str++);
////		}
////		return(hash& 0x7FFFFFFF);
////	}
////	size_t operator()(const string& s)
////	{
////		return BKDRHash(s.c_str());
////	}
////};
//
//template<class K,class V>
//struct HsahTableNode
//{
//	K _key;
//	V _value;
//	State _state;
//	HsahTableNode(const K& key,const V& value)
//		:_key(key)
//		,_value(value)
//		,_state(EMPTY)
//	{}
//	HsahTableNode()
//		:_state(EMPTY)
//	{}
//};
//
//template<class K,class V,class HashFunc=__HashFunc<K>>
//class HashTable
//{
//public:
//	typedef HsahTableNode<K,V> Node;
//	HashTable()
//		:_size(0)
//	{
//		_tables.resize (_GetNextPrime(0));  
//	}
//
//	bool Insert(const K& key,const V& value)
//	{
//		_Chicksize();
//		size_t index=_HashFunc(key); //�ҵ�key���±�
//
//		while(_tables[index]._state==EXIST)
//		{
//			if(_tables[index]._key==key)
//				return false;
//			++index;                 //����̽��--���ٹ�ϣ��ͻ
//			if(index==_tables.size())
//				index=0;
//		}
//
//		_tables[index]._key=key;
//		_tables[index]._value=value;
//		_tables[index]._state=EXIST;
//		return true;
//	}
//	bool Remove(const K& key)
//	{
//		//��һ�ַ���
//		/*size_t index=_HashFunc(key);
//
//		while(_tables[index]._state!=EMPTY)
//		{
//			if(_tables[index]._key==key)
//			{
//				_tables[index]._state=DELETE;
//				return true;
//			}
//			else
//				++index;
//		}
//		return false;*/
//
//		//�ڶ��ַ���
//		Node* ret=Find(key);
//		if(ret)
//		{
//			ret->_state =DELETE;
//			return true;
//		}
//		return false;
//	}
//	Node* Find(const K& key)
//	{
//		size_t index=_HashFunc(key);
//		while(_tables[index]._state!=EMPTY)
//		{
//			if(_tables[index]._key==key)
//			{
//				return &_tables[index];
//			}
//			else
//				++index;
//		}
//		return NULL;
//	}
//protected:
//	size_t _HashFunc(const K& key)
//	{
//		HashFunc hf;
//		return hf(key)%_tables.size ();           //����������
//	}
//	void _Chicksize()
//	{
//		if(_tables.size ()==0||_size*10/_tables.size()>=8)    //Ϊ�ջ���ڸ�������
//		{
//			size_t NewSize=_GetNextPrime(_tables.size ()); 
//			HashTable<K,V> Newhashtable;
//			Newhashtable._tables .resize (NewSize);
//
//			for(size_t i=0;i<_tables.size ();++i)      //���ƽڵ�
//			{
//				if(_tables[i]._state==EXIST)
//		        {
//					Newhashtable.Insert (_tables[i]._key,_tables[i]._value);
//				}
//			}
//
//			Swap(Newhashtable);
//		}
//	}
//	void Swap(HashTable<K,V>& Newhashtable)
//	{
//		_tables.swap (Newhashtable._tables);   //����vector��ָ��
//		swap(_size,Newhashtable._size );   //����ָ���_size
//	}
//	int _GetNextPrime(size_t size)
//	{
//		const int _PrimeSize= 28;			
//		static const unsigned long _PrimeList[_PrimeSize]=	
//		{
//			53ul, 97ul,	193ul, 389ul, 769ul,
//		    1543ul,	3079ul,	6151ul,	12289ul, 24593ul,
//			49157ul, 98317ul, 196613ul,	393241ul,	
//			786433ul, 1572869ul, 3145739ul,	6291469ul,	12582917ul,	
//			25165843ul,	50331653ul,	100663319ul, 201326611ul, 402653189ul,	
//			805306457ul, 1610612741ul, 3221225473ul, 4294967291ul		
//	    };				
//		for(size_t i=0;i<_PrimeSize;++i)
//		{
//			if(size<_PrimeList[i])
//			{
//				return _PrimeList[i];
//			}
//		}
//	}
//private:
//	vector<Node> _tables;
//	size_t _size;
//};
//void TestHsahTableNode()
//{
//	//HashTable<int,int> ht;
//	//int arr[]={89,18,49,58,9,111};
//	//for(size_t i=0;i<6;++i)
//	//{
//	//	ht.Insert (arr[i],i);
//	//}
//	//cout<<ht.Remove (111)<<endl;  //1
//	//cout<<ht.Remove (55)<<endl;   //0
//
//
//	//ͳ���ַ����ֵĴ���
//	HashTable<string,int,__StringHashFunc> ht1;
//	char* str[]={"aaa","aaaa","aaa","ddd"};
//	for(size_t i=0;i<sizeof(str)/sizeof(str[0]);++i)
//	{
//		HsahTableNode<string,int>* ret=ht1.Find (str[i]);
//		if(ret)   //����
//		{
//		    //ret->_value ++;
//			(*ret)._value ++;
//		}
//		ht1.Insert (str[i],0);
//	}
//
//}






//������
template<class K,class V>
struct KVNode
{
	K _key;
	V _value;
	KVNode<K,V>* _next;
	KVNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template<class K,class V>
class HashTable
{
	typedef KVNode<K,V> Node;
public:
	HashTable()
		:_size(0)
	{
		_tables.resize (_GetNextPrime(0));
	}
	Node* Find(const K& key)
	{
		if(_size==0)  //Ϊ��
		{
			return NULL;
		}
		size_t index=_HashFunc(key);
		Node* cur=_tables[index];  
		while(cur)    
		{
			if(cur->_key ==key)
			    return cur;  //����
			cur=cur->_next ;
		}
		return NULL;
	}
	bool Insert(const K& key,const V& value)
	{
		ChickCapacity();
		size_t index=_HashFunc(key);
		if(Find(key))
		{
			return false; //���ڣ�ֱ�ӷ���
		}
		//ͷ��
		Node* tmp=new Node(key,value);
		tmp->_next =_tables[index];
		_tables[index]=tmp;
		++_size;
		return true;
	}
	bool Remove(const K& key)
	{
		if(_size==0)
			return false;
		size_t index=_HashFunc(key);
		Node* cur=_tables[index];  
		Node* prev=NULL;
		while(cur)
		{
			if(cur->_key ==key)  //�ҵ�Ҫɾ���Ľڵ�
			{
				if(prev==NULL)   //��һ���ڵ�
				{
					_tables[index]=cur->_next ;
				}
				else    //���ǵ�һ���ڵ�����
					prev->_next =cur->_next ;
				delete cur;
				--_size;
				return true;
			}
			prev=cur;
			cur=cur->_next ;
		}
		return false;
	}
	void Print()
	{
		for(size_t i=0;i<_tables.size();++i)
		{
			printf("_tables[%d]->",i);
			Node* cur=_tables[i];
			while(cur)
			{
				cout<<cur->_key <<"->";
				cur=cur->_next ;
			}
			cout<<"NULL"<<endl;
		}
	}
	~HashTable()
	{
		for(size_t i=0;i<_tables.size();++i)
		{
			Node* cur=_tables[i];
			while(cur)
			{
				Node* next=cur->_next ;
				delete cur;
				cur=next;
			}
		}
		_size=0;
		_tables.clear();  //sizeֻ�ܼ���0�������ͷſռ䡣
		                  //��Ҫ�ͷſռ䣬��Ҫ����һ���µĿն���
		                  //Ȼ�󽻻����������������ͻ��Զ���������
	}
protected:
	HashTable(const HashTables& ht); //������

	;
	size_t _HashFunc(const K& key)
	{
		return key%_tables.size ();           //����������
	}
	void ChickCapacity()
	{
		if(_tables.size()==0||_size==_tables.size())
		{
			//����
			vector<Node*> tmptables;
			tmptables.resize (_tables.size());
			for(size_t i=0;i<_tables.size();++i)
			{
				Node* cur=_tables[i];
				while(cur)
				{
					Node* next=cur->_next ;
					size_t index=_HashFunc(cur->_key );   //�ҵ��±���Ҫ��λ��
					//ͷ��
					cur->_next =_tables[index];
					_tables[index]=cur;

					cur=next;
				}
			}
		}

	}
	int _GetNextPrime(size_t size)
	{
		const int _PrimeSize= 28;			
		static const unsigned long _PrimeList[_PrimeSize]=	
		{
			53ul, 97ul,	193ul, 389ul, 769ul,
		    1543ul,	3079ul,	6151ul,	12289ul, 24593ul,
			49157ul, 98317ul, 196613ul,	393241ul,	
			786433ul, 1572869ul, 3145739ul,	6291469ul,	12582917ul,	
			25165843ul,	50331653ul,	100663319ul, 201326611ul, 402653189ul,	
			805306457ul, 1610612741ul, 3221225473ul, 4294967291ul		
	    };				
		for(size_t i=0;i<_PrimeSize;++i)
		{
			if(size<_PrimeList[i])
			{
				return _PrimeList[i];
			}
		}
	}
private:
	vector<Node*> _tables;
	size_t _size;
};
void TestHsahTable()
{
	HashTable<int,int> ht1;
	int arr[]={89,18,49,58,9,111};
	for(size_t i=0;i<6;++i)
	{
		ht1.Insert (arr[i],i);
	}
	ht1.Print ();
	HashTable<int,int> ht2;
	//ht2(ht1);   //��������

	//cout<<ht1.Remove (111)<<endl;  //1
	//cout<<ht1.Remove (55)<<endl;   //0


	

}
