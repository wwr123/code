#include<iostream>
using namespace std;
#include<cstdlib>
#include<set>
#include<map>
#include<vector>
#include<string>
#include<algorithm>

//ͳ��ˮ�����ִ�������ǰ����
void CountTopK(vector<string>& v)
{
	map<string,int> countMap;
	for(size_t i=0;i<v.size();++i)
	{
		//	��һ�ַ���
	//	find()������һ�飬insert()���ظ�������һ��
	//	map<string,int>::iterator ret=countMap.find(v[i]);
	//	if(ret!=countMap.end())   //�ҵ�
	//	{
	//		ret->second ++;
	//	}
	//	else  //û�ҵ�
	//		countMap.insert(pair<string,int>(v[i],1));


	//	�ڶ��ַ���
		//pair<map<string,int>::iterator ,bool> ret=countMap.insert(pair<string,int>(v[i],1));
		//if(ret.second ==false) //û����ɹ���˵������
		//	ret.first ->second ++;



	//	�����ַ���
	    countMap[v[i]]++;
	}
	

	//ֻ��ͳ�Ƴ���������һ��
	/*map<string,int>::iterator countit=countMap.begin ();
	map<string,int>::iterator max=countMap.begin ();
	while(countit!=countMap.end())
	{
		if(countit->second >max->second )
			max=countit;
		++countit;
	}*/

    //Ϊ��ͳ�Ƴ�����ǰ��λ�õ�ˮ��

	//��һ�ֽⷨ����map�ĵ�����push��vector�У�Ȼ������㷨�е�sort����
	//vector<map<string,int>::iterator > vinfos;   //��Ϊ������Ϊ4���ֽڣ��������ڴ�
	//map<string,int>::iterator countit=countMap.begin ();
	//while(countit!=countMap.end())
	//{
	//    vinfos.push_back (countit);
	//	countit++;
	//}
	//�º���
	//struct Compare
	//{
	//	bool operator()(map<string,int>::iterator& l,map<string,int>::iterator& r)
	//	{
	//		return l->second > r->second;
	//	}
	//};
	//sort(vinfos.begin(),vinfos.end(),Compare()); //�Ӵ�С����


	//�ڶ��ֽⷨ����pair�ṹ���뵽vector��
	 vector<pair<string,int>> vinfos(countMap.begin (),countMap.end());
	              //countMap.begin ()������Ϊ�������������ú��������pair�ṹ
	//�º���
	struct Compare
	{
		bool operator()(pair<string,int>& l,pair<string,int>& r)
		{
			return l.second > r.second;
		}
	};
	
	sort(vinfos.begin(),vinfos.end(),Compare()); //�Ӵ�С����

}
int main()
{
	vector<string> v;
	
	v.push_back ("ƻ��");
	v.push_back ("ƻ��"); 
	v.push_back ("�㽶"); 
	v.push_back ("ƻ��"); 
	v.push_back ("ƻ��"); 
	v.push_back ("��"); 
	v.push_back ("��"); 
	v.push_back ("ƻ��"); 
	v.push_back ("ƻ��"); 
	v.push_back ("ƻ��"); 
	v.push_back ("ƻ��"); 
	v.push_back ("��"); 

	//��itָ���λ�ò��롰���ϡ���������������󿽱���size+1
	/*vector<string>::iterator  it=v.begin();
	it++;
	v.insert(it,"����");*/

	CountTopK(v);
	system("pause");
	return 0;
}


//void TestSet()
//{
//	set<int> s;
//	int arr[]={1,2,3,4,5};
//	set<int> s1(arr,arr+3);  //���캯���ķ�Χ [,) 
//	set<int>::iterator it=s1.begin ();
//	while(it!=s1.end())
//	{
//		cout<<*it<<" ";
//		++it;
//	}               //1 2 3
//
//	s.insert(23);
//	s.insert(24);
//	s.insert(25);
//	s.insert(26);
//	//pair<set<int>::iterator,bool> ret=s.insert(24);
//	////cout<<*(ret.first)<<endl;   //24
//	//set<int>::iterator it=ret.first ;
// //   s.insert (it,27);
//	//it=s.begin ();
//	//while(it!=s.end())
//	//{
//	//	cout<<*it<<" ";
//	//	++it;
//	//}
//	//cout<<endl;   //23 24 25 26 27
//
//	//pair<set<int>::iterator,bool> ret=s.insert(28);
//	//set<int>::iterator it=ret.first ;
//	//cout<<*it<<endl; //28
// //   //s.insert (it,27);
//	////it=s.begin ();
//
//	//s.insert (it,14);//it������Ŀ�ʼ���룬��ָ���λ�ò���
//
//	//while(it!=s.end())
//	//{
//	//	cout<<*it<<" ";
//	//	++it;
//	//}
//	//cout<<endl;   //23 24 25 26 27 28
//}
//void TestMap()
//{
//	map<char,int> m;
//	m.insert(pair<char,int>('a',2));
//
//	cout<<m['a']<<endl;  //2
//}
//