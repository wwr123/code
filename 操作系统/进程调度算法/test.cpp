#include<iostream>
using namespace std;
#include<vector>
#include<cstdlib>
#include<algorithm>
enum State
{
	EXIST,
	EMPTY,
};
struct Pro
{
	int name;      //作业名
	int ArriveTime;//到达时间
	int Runtime;   //运行时间
	int BeginTime; //开始时间
	int FinishTime;//完成时间
	int ZTime;     //周转时间
	double WTime;  //带权周转时间
    double Pow;    //优先权
    State _sta;    
	Pro()
		:name(0)
		,ArriveTime(0)
		,Runtime(0)
		,BeginTime(0)
		,FinishTime(0)
		,ZTime(0)
		,WTime(0)
		,Pow(0.0)
		,_sta(EMPTY)
	{}
};

class FJF
{
public:
	
	void Insert(int n)
	{
		cout<<"输入作业名，到达时间，运行时间"<<endl;
		_v.resize(n);
		for(int i=0;i<n;++i)
		{
			cin>>_v[i].name >>_v[i].ArriveTime >>_v[i].Runtime ;
			_v[i]._sta =EXIST;
		}
	}
	//先来先服务
	void FCFS()
	{

		//按到达时间排序
		vector<Pro>::iterator it1=_v.begin ();
		vector<Pro>::iterator it2=_v.end ();
		struct Compare
		{
				bool operator()(Pro& l,Pro& r)
				{
					return l.ArriveTime  < r.ArriveTime  ;
				}
		};
		sort(it1,it2,Compare()); 
		
		for(size_t i=0;i<_v.size();++i)
		{
			if(i==0)
			{
				_v[i].BeginTime =_v[i].ArriveTime ;	
			}
			else
			{
				_v[i].BeginTime =_v[i-1].FinishTime ;
			}
			    _v[i].FinishTime =_v[i].BeginTime +_v[i].Runtime ;
				_v[i].ZTime =_v[i].FinishTime-_v[i].ArriveTime;
				_v[i].WTime =(double)_v[i].ZTime/_v[i].Runtime;
		}
	}

	//短作业
	void SJF()
	{
		//按到达时间排序
		vector<Pro>::iterator it1=_v.begin ();
		vector<Pro>::iterator it2=_v.end ();
		struct Compare
		{
				bool operator()(Pro& l,Pro& r)
				{
					return l.ArriveTime  < r.ArriveTime  ;
				}
		};
		sort(it1,it2,Compare()); 
		//第一个最先到达的第一个先运行
		vector<Pro>::iterator it=_v.begin ();
		vector<Pro>::iterator prev=_v.begin ();
		_v[0].BeginTime =_v[0].ArriveTime ;	
		_v[0].FinishTime =_v[0].BeginTime +_v[0].Runtime ;
		_v[0].ZTime =_v[0].FinishTime-_v[0].ArriveTime;
		_v[0].WTime =(double)_v[0].ZTime/_v[0].Runtime;
	  
		for(size_t i=1;i<_v.size();++i)
		{
			vector<Pro>::iterator cur=it+1;
		 
			while(cur!=_v.end())
			{
					if(cur->ArriveTime >it->FinishTime )
						break;
					cur++;
			
			}
		
			struct Compare
			{
				bool operator()(Pro& l,Pro& r)
				{
					return l.Runtime  < r.Runtime ;
				}
			};
			
			sort(it+1,cur,Compare()); 

			it++;
			
		    _v[i].BeginTime =_v[i-1].FinishTime ;
			_v[i].FinishTime =_v[i].BeginTime +_v[i].Runtime ;
			_v[i].ZTime =_v[i].FinishTime-_v[i].ArriveTime;
			_v[i].WTime =(double)_v[i].ZTime/_v[i].Runtime;
		     
		}

		
	}
	
	//高响应比
	void HRRN()
	{
		//按到达时间排序
		vector<Pro>::iterator it1=_v.begin ();
		vector<Pro>::iterator it2=_v.end ();
		struct Compare
		{
				bool operator()(Pro& l,Pro& r)
				{
					return l.ArriveTime  < r.ArriveTime  ;
				}
		};
		sort(it1,it2,Compare()); 

		vector<Pro>::iterator prev=_v.begin ();
		vector<Pro>::iterator cur=_v.begin();
		for(size_t i=0;i<_v.size();++i)
		{
			if(i==0)
			{
				_v[i].BeginTime =_v[i].ArriveTime ;	
				_v[i].FinishTime =_v[i].BeginTime +_v[i].Runtime ;
				_v[i].ZTime =_v[i].FinishTime-_v[i].ArriveTime;
				_v[i].WTime =(double)_v[i].ZTime/_v[i].Runtime;
				_v[i]._sta =EMPTY;
			}
			else
			{

				for(size_t j=1;j<_v.size();++j)
				{
					if(prev->FinishTime >=_v[j].ArriveTime&&_v[j]._sta ==EXIST)
					{
						double Rp=(double)(prev->FinishTime -_v[j].ArriveTime+_v[j].Runtime  )/
						(prev->FinishTime -_v[j].ArriveTime);
					  
						_v[j].Pow =Rp;
					}
				}

                double tmp=0.0;
				for(size_t k=1;k<_v.size();++k)
				{
					if((_v[k].Pow >tmp)&&(_v[k]._sta !=EMPTY)&&(prev->FinishTime>=_v[k].ArriveTime ))
					{
						tmp=_v[k].Pow;
						cur=_v.begin ();
						cur+=k;
					}
				}
				cur->BeginTime =prev->FinishTime ;
				cur->FinishTime=cur->BeginTime +cur->Runtime ;
				cur->ZTime =cur->FinishTime-cur->ArriveTime;
				cur->WTime =(double)cur->ZTime/cur->Runtime;
				cur->_sta =EMPTY;
				prev=cur;
			}
		}
	}
	void Print()
	{
		cout<<"作业"<<" "<<"到达"<<" "<<"运行"<<" "<<" "
			<<"开始"<<" "<<"完成"<<" "<<"周转"<<" "<<"带权周转"<<endl;
		for(size_t i=0;i<_v.size();++i)
		{
			cout<<_v[i].name <<"    "<<_v[i].ArriveTime <<"    "<<_v[i].Runtime 
				<<"    "<<_v[i].BeginTime <<"    "
				<<_v[i].FinishTime <<"    "<<_v[i].ZTime <<"    "<<_v[i].WTime<<endl;
		
		}
		cout<<endl;
	}
private:
	vector<Pro> _v;
};

int main()
{
	 FJF f;
	 f.Insert (3);
	//f.FCFS ();
	//f.SJF ();
	 f.HRRN ();
	 f.Print ();
	 system("pause");
	 return 0;
}