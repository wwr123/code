#include<iostream>
using namespace std;
#include<cstdlib>
#include<vector>
#include<cassert>
//压缩矩阵
template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a,size_t n)    //i>=j
		:_n(n)
		
	{
		_a=new T[n*(n+1)/2];
		size_t k=0;
		for(size_t i=0;i<n;i++)
		{
			for(size_t j=0;j<n;j++)
			{
				if(i>=j)
				{
					  _a[k++]=a[i*_n+j];
				}
			}
		}
	}
	~SymmetricMatrix()
	{
		if(_a!=NULL)
		{
			delete[] _a;
			_n=0;
		}
	}
	T& Access(size_t i,size_t j)
	{
		if(i<j)
		{
			swap(i,j);
		}
		return _a[i*(i+1)/2+j];
	}
	void Display()
	{
		for(size_t i=0;i<_n;i++)
		{
			for(size_t j=0;j<_n;j++)
			{
				cout<<Access(i,j)<<" ";
			}
			cout<<endl;
		}
	}

private:
	T* _a;   //数组
	size_t _n;   //行和列数
};
void TestSymmetricMatrix()
{
	int a[5][5]=
	{
		{0,1,2,3,4},
		{1,0,1,2,3},
		{2,1,0,1,2},
		{3,2,1,0,1},
		{4,3,2,1,0},
	};
	SymmetricMatrix<int> sm((int*)a,5);
    //cout<<sm.Access (4,0)<<endl;
	sm.Display();
}

//稀疏矩阵
template<class T>
struct Triple     //三元组
{
	Triple(size_t row,size_t col,const T& data)
		:_row(row)
		,_col(col)
		,_data(data)
	{}
	Triple(){}
	size_t _row;
	size_t _col;
	T _data;
};
template<class T>
class SparseMatrix
{
public:
	SparseMatrix(){}
	SparseMatrix(T* a,size_t m,size_t n,const T& invalid)   //数组 行 列 非法值
		:_m(m)
		,_n(n)
		,_invalid(invalid)
	{
		for(size_t i=0;i<_m;i++)
		{
			for(size_t j=0;j<_n;j++)
			{
				if(a[i*_n+j]!=_invalid)
				{
					v.push_back (Triple<T>(i,j,a[i*_n+j]));
				}
			}
		}
	}
	//普通转置
	SparseMatrix<T> TransposedMatrix()
	{
		SparseMatrix<T> sm;
		sm._m =_n;//_m=5行
		sm._n =_m;//_n=6列
		sm._invalid =_invalid;
		sm.v.reserve (v.size());

		for(size_t i=0;i<_n;++i)
		{
			size_t index=0;
			while(index<v.size())
			{
				if(v[index]._col==i)
				{
					Triple<T> t(v[index]._col,v[index]._row,v[index]._data);
					sm.v .push_back (t);
				}
				++index;
			}

		}
		return sm;
	}
	//快速转置
	SparseMatrix<T> FastTransposedMatrix()
	{
		SparseMatrix<T> sm;
		sm._m =_n;//_m=5行
		sm._n =_m;//_n=6列
		sm._invalid =_invalid;
		sm.v.resize (v.size());

		int* count=new int[_n]; //统计转置后每一行数据的个数
		memset(count,0,_n*sizeof(int));
		int* start=new int[_n];  //统计转置后每一行在压缩矩阵存储的开始位置

		//统计个数转置后的
		size_t index=0;
		while(index<v.size ())
		{
			int row=v[index]._col;
			count[row]++;
			++index;
		}
		//开始位置
		start[0]=0;
		for(size_t i=1;i<_n;++i)
		{
			start[i]=start[i-1]+count[i-1];
		}
		index=0;
		while(index<v.size())
		{
			Triple<T> t(v[index]._col,v[index]._row,v[index]._data);//三元组
			int row=v[index]._col;   //得到行
			int begin=start[row];   //得到这一行转置后在v的初始位置
			sm.v[begin]=t;          //在把这个数的信息插入进去
			start[row]++;
			++index;
		}
		delete[] count;
		delete[] start;
		return sm;
	}
	~SparseMatrix()
	{}
	void Display()
	{
		size_t k=0;
		for(size_t i=0;i<_m;i++)
		{
			for(size_t j=0;j<_n;j++)
			{
				if((i==v[k]._row)&&(j==v[k] ._col))
				{
					cout<<v[k] ._data<<" ";
					if(k<v.size ()-1)
						k++;
				}
				else
					cout<<_invalid<<" ";
			}
			cout<<endl;
		}
	}
protected:
	vector<Triple<T>> v;
	size_t _m;
	size_t _n;
	T _invalid;
};
void TestSparseMatrix()
{
	int a[6][5]=
	{
		{1,0,3,0,5},
		{0,0,0,0,0},
		{0,0,0,0,0},
		{2,0,4,0,6},
		{0,0,0,0,0},	
		{0,0,0,0,0},		
	};
	SparseMatrix<int> sm((int*)a,6,5,0);
	sm.Display ();
	/*SparseMatrix<int> tsm=sm.TransposedMatrix();
	tsm.Display ();*/
	SparseMatrix<int> ftsm=sm.FastTransposedMatrix ();
	ftsm.Display ();
}



template<class T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	Vector()
		:_finish(0)
		,_start(0)
		,_endofStorage(0)
	{}
	Iterator& Begin()
	{
		return _start;
	}
	Iterator& End()
	{
		return _finish;
	}
	
	void Insert(Iterator& pos,const T& x)
	{
		CheckStorage();
		if(pos==_finish)
		{
			*pos=x;
			++_finish;
		}
		else
		{
			size_t size=Size();
			Iterator cur=_finish-1;
		    ++_finish;
		    while(pos<=cur)
			{
				_start[size]=_start[size-1];
				--size;
				--cur;
			}
			*pos=x;
		}

	}
	void Erase(Iterator& pos)
	{
	    if(pos!=_finish)
		{
			size_t size=pos-_start;
		    Iterator cur=pos+1;
		    while(_finish!=cur)
		    {
				_start[size]=_start[size+1];
		        ++size;
		        ++cur;
		   }
		   --_finish;
		}
	}
	size_t Size()
	{
		return _finish-_start;
	}
	void CheckStorage()
	{
		if(_finish==_endofStorage)
		{
			size_t size=Size();
			Iterator tmp=new T[size*2+3];
			for(size_t i=0;i<size;i++)
			{
				tmp[i]=_start[i];
			}
			delete[] _start;
			_start=tmp;
			_finish=_start+size;
			_endofStorage=_start+size*2+3;
		}
	}
	void PushBack(const T& x)
	{
		Insert(End(),x);
	}
	void PopBack()
	{
		Erase(--End());
	}
	~Vector()
	{
		if(_start!=_finish)
		{
			delete[] _start;
			_start=NULL;
			_finish=NULL;
			_endofStorage=NULL;
		}
	}
protected:
	Iterator _start;    //[
	Iterator _finish;   //)
	Iterator _endofStorage;
};
void TestVector()
{
	Vector<int> v;


	v.PushBack (1);
	v.PushBack (2);
	//v.PopBack ();
	//Vector<int>::Iterator it1=v.Begin ();
	//v.Insert (it1,5);
	Vector<int>::Iterator it1=v.Begin ();
	v.Erase (it1);
	v.PushBack (3);
	v.PushBack (4);
	//v.PopBack ();
	Vector<int>::Iterator it=v.Begin ();
	while(it!=v.End ())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
	
	
}
int main()
{
	//TestSymmetricMatrix();
	//TestSparseMatrix();
	//vector<int> v;
    //TestVector();
	TestSparseMatrix();
	system("pause");
	return 0;
}