#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//网易笔试
//字符串拼接最好的有哪几种方式
//最多只允许出现一次，两个不同的字符串相挨
//思路：一串字符串中最多只允许出现2中字符。 O(n)
int test1(string& s)
{
	if(s.size()>50)
		return 0;
	map<char,int> m;
	const char* ptr=s.c_str();
	while(*ptr!='\0')
	{
		m[*ptr]++;
		ptr++;
	}
	if(m.size()>=3)
		return 0;
	else
		return m.size();
}
//每输入一次数字就逆序一次
//比如，输入 1 2 3 4 就要逆序4次   
void test2(int n,vector<int>& v,vector<int>& arr)
{
    int index = 0;
    int count = 0;
    
    while(1){
        arr.push_back(v[index]);
        reverse(arr.begin(), arr.end());
        
        count++;
        if(count == n){
            break;
        }
        
        index++;
 
    }
}

int main()
{
  /*  int n = 0;
    cin>>n;
    vector<int> v; 
	for(int i = 0;i < n;i++)
	{
        int num = 0;
        cin>>num;
        v.push_back(num);
    }
	vector<int> arr;
    test2(n,v,arr); 
    for(int i = 0;i < arr.size();i++){
        cout<<arr[i];
		if(i!=(arr.size()-1))
			cout<<" ";
    }
    cout<<endl;*/
	//cout<<"0 1 3 10"<<endl;
	char arr[]="aaaa";
	cout<<strlen(arr)<<endl;    //4
	cout<<sizeof(arr)<<endl;    //5
    system("pause");
    return 0;
}
