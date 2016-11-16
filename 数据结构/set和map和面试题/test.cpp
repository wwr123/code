#include<iostream>
using namespace std;
#include<cstdlib>
#include<set>
#include<map>
#include<vector>
#include<string>
#include<algorithm>

//统计水果出现次数最多的前三个
void CountTopK(vector<string>& v)
{
	map<string,int> countMap;
	for(size_t i=0;i<v.size();++i)
	{
		//	第一种方法
	//	find()遍历了一遍，insert()又重复遍历了一遍
	//	map<string,int>::iterator ret=countMap.find(v[i]);
	//	if(ret!=countMap.end())   //找到
	//	{
	//		ret->second ++;
	//	}
	//	else  //没找到
	//		countMap.insert(pair<string,int>(v[i],1));


	//	第二种方法
		//pair<map<string,int>::iterator ,bool> ret=countMap.insert(pair<string,int>(v[i],1));
		//if(ret.second ==false) //没插入成功，说明已有
		//	ret.first ->second ++;



	//	第三种方法
	    countMap[v[i]]++;
	}
	

	//只能统计出数量最多的一个
	/*map<string,int>::iterator countit=countMap.begin ();
	map<string,int>::iterator max=countMap.begin ();
	while(countit!=countMap.end())
	{
		if(countit->second >max->second )
			max=countit;
		++countit;
	}*/

    //为了统计出排在前三位置的水果

	//第一种解法：把map的迭代器push到vector中，然后调用算法中的sort方法
	//vector<map<string,int>::iterator > vinfos;   //因为迭代器为4个字节，减少了内存
	//map<string,int>::iterator countit=countMap.begin ();
	//while(countit!=countMap.end())
	//{
	//    vinfos.push_back (countit);
	//	countit++;
	//}
	//仿函数
	//struct Compare
	//{
	//	bool operator()(map<string,int>::iterator& l,map<string,int>::iterator& r)
	//	{
	//		return l->second > r->second;
	//	}
	//};
	//sort(vinfos.begin(),vinfos.end(),Compare()); //从大到小排列


	//第二种解法：把pair结构插入到vector中
	 vector<pair<string,int>> vinfos(countMap.begin (),countMap.end());
	              //countMap.begin ()的类型为迭代器，解引用后的类型是pair结构
	//仿函数
	struct Compare
	{
		bool operator()(pair<string,int>& l,pair<string,int>& r)
		{
			return l.second > r.second;
		}
	};
	
	sort(vinfos.begin(),vinfos.end(),Compare()); //从大到小排列

}
int main()
{
	vector<string> v;
	
	v.push_back ("苹果");
	v.push_back ("苹果"); 
	v.push_back ("香蕉"); 
	v.push_back ("苹果"); 
	v.push_back ("苹果"); 
	v.push_back ("梨"); 
	v.push_back ("梨"); 
	v.push_back ("苹果"); 
	v.push_back ("苹果"); 
	v.push_back ("苹果"); 
	v.push_back ("苹果"); 
	v.push_back ("梨"); 

	//给it指向的位置插入“西瓜”，其他的依次向后拷贝，size+1
	/*vector<string>::iterator  it=v.begin();
	it++;
	v.insert(it,"西瓜");*/

	CountTopK(v);
	system("pause");
	return 0;
}


//void TestSet()
//{
//	set<int> s;
//	int arr[]={1,2,3,4,5};
//	set<int> s1(arr,arr+3);  //构造函数的范围 [,) 
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
//	//s.insert (it,14);//it代表从哪开始插入，它指向的位置不变
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