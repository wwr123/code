#include<iostream>
using namespace std;
#include<cstdlib>
#include<list>
#define M 3 //资源数
#define N 5 //进程数

struct DijkstraNode
{
	int num;//进程名
	int max[M];//进程对某类资源的最大需求
	int allocation[M];//已分配的
	int need[M];//尚需求的
	bool finish;//状态
	DijkstraNode()
	{
		num=0;
		finish=false;
		for(size_t i=0;i<M;++i)
		{
			max[i]=0;
			allocation[i]=0;
			need[i]=0;
		}
	}
};
class Dijkstra
{
	typedef DijkstraNode Node;
public:
	int MaxNum[M]; //各类资源的总数
	int Available[M];//可利用的资源
	int Safeylist[N]; //保存安全序列
	int Work[M];
	
	void Init()
	{
		cout<<"各类资源的总数(M=3)"<<endl;
		for(size_t i=0;i<M;++i)
		{
			cin>>MaxNum[i];
		}
		cout<<"进程名（N=5）"<<" "<<"对资源最大需求"<<" "<<"已分配的"<<endl;
		for(size_t i=0;i<N;++i)
		{
			Node n;
			cin>>n.num;
			for(size_t i=0;i<M;++i)
			{
				cin>>n.max [i];
			}
			for(size_t i=0;i<M;++i)
			{
				cin>>n.allocation [i];
			}
			l.push_back (n);
		}
		//求need
		list<Node>::iterator it=l.begin ();
		while(it!=l.end())
		{
			for(size_t i=0;i<M;++i)
			{
				it->need [i]=it->max [i]-it->allocation [i];
			}
			++it;
		}
		//求Available
		cout<<"可利用的资源为：";
		for(size_t i=0;i<M;++i)
		{
			list<Node>::iterator it=l.begin ();
			int num=0;
			while(it!=l.end())
			{
				num+=it->allocation [i];
				++it;
			}
			Available[i]=MaxNum[i]-num;
			cout<<Available[i]<<" ";
		}
		cout<<endl;
	}

  
	void SafeyList()
	{
		memcpy(Work,Available,M*sizeof(Available[0]));
		bool state=_saftlist();
		if(state)
		   _Display();
	}
  
	void Request()
	{
		while(1)
		{
			cout<<"是否请求分配资源：1.是 0.否："<<endl;
			int state=0;
			cin>>state;
			if(state==1)
			{
				int  n;
				int request[M]={0};
				cout<<"输入要请求资源的进程："<<endl;
				cin>>n;
				cout<<"输入要请求的资源："<<endl;
				for(size_t i=0;i<M;++i)
				{
					cin>>request[i];
				}
				//找进程的位置
				list<Node>::iterator it=l.begin ();
				while(it!=l.end())
				{
					if(it->num ==n)
						break;
					++it;
				}
				if(it==l.end())
				{
					cout<<"不是当前的进程"<<endl;
					continue;
				}
				//判断Request，need,Available
				int falg=0;
				for(size_t i=0;i<M;++i)
				{
					if(request[i]>it->need [i])
					{
						falg=1;
						cout<<"请求>需求，不能分配"<<endl;
						break;
					}
					if(request[i]>Available[i])
					{
						falg=1;
						cout<<"请求>可利用，不能分配"<<endl;
						break;
					}
				} 
				if(falg==1)
					continue;
				//备份
				int PrevAvailable[M];
				int PrevItAllocation[M];
				int PrevItNeed[M];
				memcpy(PrevAvailable,Available,M*sizeof(Available[0]));
				memcpy(PrevItAllocation,it->allocation,M*sizeof(PrevItAllocation[0]));
				memcpy(PrevItNeed,it->need,M*sizeof(PrevItNeed[0]));

				//假设可分配，修改值
				for(size_t i=0;i<M;++i)
				{
					Available[i] -= request[i];
					it->need [i] = it->need[i] - request[i];
					it->allocation [i] = it->allocation[i] + request[i];
				}

				//把finish初始化为false
				list<Node>::iterator it1 = l.begin ();
				while(it1!=l.end())
				{
					it1->finish =false;
					++it1;
				}

				//把安全序列清空
				for(size_t i=0;i<N;++i)
				{
					Safeylist[N]=0;
				}

				SafeyList();

				//检测是否存在安全序列
				list<Node>::iterator it2=l.begin ();
				while(it2!=l.end())
				{
					if(it2->finish ==false)
					{
						memcpy(Available,PrevAvailable,M*sizeof(Available[0]));
						memcpy(it->allocation,PrevItAllocation,M*sizeof(PrevItAllocation[0]));
						memcpy(it->need,PrevItNeed,M*sizeof(PrevItNeed[0]));
						cout<<"归位:"<<endl;
						cout<<"Avi"<<" "<<"All"<<" "<<"Need"<<endl;
						for(size_t i=0;i<M;++i)
						{
							cout<<Available[i]<<"   "<<it->allocation[i]<<"   "<<it->need[i]<<endl;
						}
						break;
					}
					++it2;
				}	
			}
			else 
				return;
		}

    }
protected:
	void _Display()
	{
		cout<<"安全序列为："<<endl;
		for(size_t i=0;i<N;++i)
		{
			cout<<Safeylist[i]<<" ";
		}
		cout<<endl;
	}
	bool _saftlist()
	{
		for(size_t i=0;i<N;++i)
		{
			list<Node>::iterator it=_Find(); 
			if(it==l.end())
			{
				cout<<"找不到满足条件的进程,该序列不安全"<<endl;
				return false;
			}
			it->finish =true;
			Safeylist[i]=it->num ;

			//打印表
			cout<<"进程号"<<" "<<"work"<<"    "<<"need"<<"    "<<"allo"<<"    "
			<<"work+allo"<<"    "<<"finish"<<endl;
			cout<<it->num <<"     ";
			for(size_t j=0;j<M;++j)
			{
				cout<<Work[j]<<" ";
			}
			cout<<"   ";
			for(size_t j=0;j<M;++j)
			{
				cout<<it->need [j]<<" ";
			}
			cout<<"  ";
			for(size_t j=0;j<M;++j)
			{
				cout<<it->allocation [j]<<" ";
			}
			cout<<"  ";
			for(size_t j=0;j<M;++j)
			{
				cout<<Work[j]+it->allocation [j]<<" ";
			}
			cout<<"      ";
			cout<<it->finish <<endl;

			//更新work
			for(size_t j=0;j<M;++j)
			{
				Work[j] = Work[j]+ it->allocation [j];
			}
		
		}
		return true;
	}
	list<Node>::iterator _Find()
	{
		list<Node>::iterator it = l.begin ();
		while(it != l.end())
		{
			if(it->finish ==false)
			{
				size_t j=0;
				for(j=0;j<M;++j)
				{
					if(Work[j]<it->need [j])
						break;
				}
				if(j==M)   //都>=
					return it;
			}
			++it;
		}
		return it;
	}
private:
	list<Node> l;
};
void TestDijkstra()
{
	Dijkstra d;
	d.Init ();
    d.SafeyList ();
	d.Request ();
	
}
int main()
{
	TestDijkstra();
	system("pause");
	return 0;
}
