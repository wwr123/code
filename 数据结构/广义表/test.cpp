#include"generalizedlist.h"
#include<cstdlib>
struct A
{
		int a;     //4
		//int* b;    //4
		union
		{
			int c;
			int* d;
		};    //4
};
int main()
{
	
	//A a;    
	//cout<<sizeof(a)<<endl;   //12
	TestGeneralizedList();
	system("pause");
	return 0;
}