#include<iostream>
using namespace std;
#include<cstdlib>
#include<list>
#define M 3 //��Դ��
#define N 5 //������

struct DijkstraNode
{
	int num;//������
	int max[M];//���̶�ĳ����Դ���������
	int allocation[M];//�ѷ����
	int need[M];//�������
	bool finish;//״̬
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
	int MaxNum[M]; //������Դ������
	int Available[M];//�����õ���Դ
	int Safeylist[N]; //���氲ȫ����
	int Work[M];
	
	void Init()
	{
		cout<<"������Դ������(M=3)"<<endl;
		for(size_t i=0;i<M;++i)
		{
			cin>>MaxNum[i];
		}
		cout<<"��������N=5��"<<" "<<"����Դ�������"<<" "<<"�ѷ����"<<endl;
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
		//��need
		list<Node>::iterator it=l.begin ();
		while(it!=l.end())
		{
			for(size_t i=0;i<M;++i)
			{
				it->need [i]=it->max [i]-it->allocation [i];
			}
			++it;
		}
		//��Available
		cout<<"�����õ���ԴΪ��";
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
			cout<<"�Ƿ����������Դ��1.�� 0.��"<<endl;
			int state=0;
			cin>>state;
			if(state==1)
			{
				int  n;
				int request[M]={0};
				cout<<"����Ҫ������Դ�Ľ��̣�"<<endl;
				cin>>n;
				cout<<"����Ҫ�������Դ��"<<endl;
				for(size_t i=0;i<M;++i)
				{
					cin>>request[i];
				}
				//�ҽ��̵�λ��
				list<Node>::iterator it=l.begin ();
				while(it!=l.end())
				{
					if(it->num ==n)
						break;
					++it;
				}
				if(it==l.end())
				{
					cout<<"���ǵ�ǰ�Ľ���"<<endl;
					continue;
				}
				//�ж�Request��need,Available
				int falg=0;
				for(size_t i=0;i<M;++i)
				{
					if(request[i]>it->need [i])
					{
						falg=1;
						cout<<"����>���󣬲��ܷ���"<<endl;
						break;
					}
					if(request[i]>Available[i])
					{
						falg=1;
						cout<<"����>�����ã����ܷ���"<<endl;
						break;
					}
				} 
				if(falg==1)
					continue;
				//����
				int PrevAvailable[M];
				int PrevItAllocation[M];
				int PrevItNeed[M];
				memcpy(PrevAvailable,Available,M*sizeof(Available[0]));
				memcpy(PrevItAllocation,it->allocation,M*sizeof(PrevItAllocation[0]));
				memcpy(PrevItNeed,it->need,M*sizeof(PrevItNeed[0]));

				//����ɷ��䣬�޸�ֵ
				for(size_t i=0;i<M;++i)
				{
					Available[i] -= request[i];
					it->need [i] = it->need[i] - request[i];
					it->allocation [i] = it->allocation[i] + request[i];
				}

				//��finish��ʼ��Ϊfalse
				list<Node>::iterator it1 = l.begin ();
				while(it1!=l.end())
				{
					it1->finish =false;
					++it1;
				}

				//�Ѱ�ȫ�������
				for(size_t i=0;i<N;++i)
				{
					Safeylist[N]=0;
				}

				SafeyList();

				//����Ƿ���ڰ�ȫ����
				list<Node>::iterator it2=l.begin ();
				while(it2!=l.end())
				{
					if(it2->finish ==false)
					{
						memcpy(Available,PrevAvailable,M*sizeof(Available[0]));
						memcpy(it->allocation,PrevItAllocation,M*sizeof(PrevItAllocation[0]));
						memcpy(it->need,PrevItNeed,M*sizeof(PrevItNeed[0]));
						cout<<"��λ:"<<endl;
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
		cout<<"��ȫ����Ϊ��"<<endl;
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
				cout<<"�Ҳ������������Ľ���,�����в���ȫ"<<endl;
				return false;
			}
			it->finish =true;
			Safeylist[i]=it->num ;

			//��ӡ��
			cout<<"���̺�"<<" "<<"work"<<"    "<<"need"<<"    "<<"allo"<<"    "
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

			//����work
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
				if(j==M)   //��>=
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
