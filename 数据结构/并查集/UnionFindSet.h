#pragma once
class UnionFindSet
{
public:
	UnionFindSet(int n)
		:_n(n)
	{
		_a=new int[n+1];
		for(size_t i=0;i<=n;++i)
		{
			_a[i]=-1;
		}
	}
	int FindRoot(int x)
	{
		while(_a[x]>=0)  //²»ÊÇ¸ù
		{
			x=_a[x];
		}
		return x;
	}
	void Union(int x1,int x2)
	{
		int root1=FindRoot(x1);
		int root2=FindRoot(x2);
	    if(root1!=root2)
		{
			_a[root1]+=_a[root2];
		    _a[root2]=root1;
		}
	}
	int Count()
	{
		int count=0;
		for(size_t i=0;i<=_n;++i)
		{
			if(_a[i]<=-1)
				count++;
		}
		return count-1;
	}
protected:
	int* _a;
	int _n;
};
int friends(int n,int m,int a[][2])
{
	UnionFindSet u(5);
	for(size_t i=0;i<m;++i)
	{
		u.Union (a[i][0],a[i][1]);
	}
	return u.Count ();
}
void TestUnionFindSet()
{
	int r[][2]={{1,2},{2,3},{4,5}};
	cout<<friends(5,3,r)<<endl;
}
