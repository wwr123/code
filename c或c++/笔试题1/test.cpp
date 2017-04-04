#include<iostream>
using namespace std;
#include<cstdlib>
#include<vector>
#include<queue>

//������̨������
//size_t Jump(size_t n)
//{
//	if(n==1)
//		return 1;
//	int num1=1;
//	int num2=1;
//	int num3=1;
//	for(size_t i=1;i<n;++i)
//	{
//		num3=num1+num2;
//		num1=num2;
//		num2=num3;
//	}
//	return num3;
//}
//������ǰ��ż���ں�
//void reOrderArray()
//{
//	int a[]={3,5,4,2,7,8,1,6};
//	int n=sizeof(a)/sizeof(a[0]);
	//���������˼�� O(n^2)
	//for(size_t index=1;index<n;++index)
	//{
	//	if(a[index]%2==1)  //����
	//	{
	//		int pos=index;
	//		while(pos>=0&&a[pos-1]%2==0)
	//		{
	//			int tmp=a[pos];
	//			a[pos]=a[pos-1];
	//			a[pos-1]=tmp;
	//			--pos;
	//		}
	//	}
	//}

	//vector
//	vector<int> v1;  //�������
//	vector<int> v2;  //���ż��
//	for(size_t i=0;i<n;++i)
//	{
//		if(a[i]%2==1)
//			v1.push_back (a[i]);
//		else
//			v2.push_back (a[i]);
//	}
//	for(size_t i=0;i<v1.size();++i)
//	{
//		a[i]=v1[i];
//	}
//	for(size_t j=0;j<v2.size();++j)
//	{
//		a[v1.size()+j]=v2[j];
//	}
//	for(size_t i=0;i<n;++i)
//	{
//		cout<<a[i]<<" ";    //3 5 7 1 4 2 8 6
//	}
//	cout<<endl;
//}
//struct BinaryTreeNode
//{
//	int value;
//	BinaryTreeNode* left;
//	BinaryTreeNode* right;
//};
////�ؽ�������
//BinaryTreeNode* Construct(int* preorder,int* preorderend,int* inorder,int* inorderend)
//{
//	if(preorder==NULL||preorderend==NULL||inorder==NULL||inorderend==NULL)
//		return NULL;
//	int rootval=preorder[0];  //���ڵ��ֵ
//	BinaryTreeNode* root=new BinaryTreeNode();
//	root->value =rootval;
//	if(preorder==preorderend)  //ֻ��һ���ڵ�
//	{
//		if(inorder==inorderend)
//			return root;
//		else  //���������в�ֻ��һ���ڵ㣬�쳣
//			return NULL;
//	}
//	//�����������У���root�ڵ�
//	int* rootinorder=inorder;
//	while(rootinorder!=inorderend&&rootval!=(*rootinorder))  
//		++rootinorder;
//	if(rootinorder==inorderend&&rootval!=(*rootinorder)) //û���ҵ�
//		return  NULL;
//	int len=rootinorder-inorder;  //�������ĳ���
//	if(len>0)
//	{
//		//����������
//		root->left =Construct(preorder+1,preorder+len,inorder,rootinorder-1);
//	}
//	if(len<preorderend-preorder)  //����������<�ܳ���
//	{
//		//����������
//		root->right =Construct(preorder+len+1,preorderend,rootinorder+1,inorderend);
//	}
//	return root;
//}
////��α���
//void Levelorder(BinaryTreeNode* root)
//{
//	if(root==NULL)
//		return;
//	queue<BinaryTreeNode*> q;
//	q.push(root);
//	while(!q.empty())
//	{
//		BinaryTreeNode* cur=q.front ();
//		cout<<cur->value <<" ";
//		q.pop();
//		if(cur->left !=NULL)
//		{
//			q.push (cur->left );
//		}
//		if(cur->right !=NULL)
//		{
//			q.push (cur->right );
//		}
//	}
//
//
//}
//
//void test()
//{
//	int n=0;
//	cin>>n; //���Ľڵ����
//	int* preorder=new int[n];
//	int* inorder=new int[n];
//	for(int i=0;i<n;++i)
//	{
//		cin>>preorder[i];
//	}
//	for(int j=0;j<n;j++)
//	{
//		cin>>inorder[j];
//	}
//	BinaryTreeNode* root=Construct(preorder,preorder+n-1,inorder,inorder+n-1);
//	Levelorder(root);
//}
//������8   ���ֲ��ң��ҵ���С���� O(logn)
void test1()
{
	int numbers[]={1,0,1,1,1};
	int length=sizeof(numbers)/sizeof(numbers[0]);
	int index1=0;
	int index2=length-1;
	int indexmin=index1;  //Ϊ�˷�ֹ������鱾���������õ�����
	while(numbers[index1]>=numbers[index2])
	{
		if((index2-index1)==1) //index1ָ�����ģ�index2ָ����С��
		{
			indexmin=index2;
			break;
		}
		int indexmin=((index2-index1)>>1)+index1;   //����м��±�
		//1 0 1 1 1
		if(numbers[index1]==numbers[index2]&&numbers[index1]==numbers[indexmin])
		{
			//��ͷ��β����һ���ҵ���С��
			indexmin=index1;
			for(int i=0;i<length;++i)
			{
				if(numbers[indexmin]>numbers[i])
					indexmin=i;
			}
		}

		if(numbers[indexmin]>=numbers[index2])
		{
			index1=indexmin;
		}
		if(numbers[indexmin]<=numbers[index2])
		{
			index2=indexmin;
		}
	}
	cout<<numbers[indexmin]<<endl;;
}
//���ڶ�������
#include<algorithm>
#include<cmath>
int FindMin(int* arr,int left,int right)
{
	int mid=((right-left)>>1)+left;
	if(arr[0]<=mid&&arr[2]>=mid)
		return mid;
	else if(arr[0]>mid)
		return FindMin(arr,mid+1,right);
	else if(arr[2]<mid)
		return FindMin(arr,left,mid-1);
}
void test2()
{
	int k=0;
	cin>>k;
	int arr[3];
	for(int i=0;i<3;++i)
	{
		cin>>arr[i];	
	}
	sort(arr,arr+3);
	int right=(1<<k)-1; //��1����kλ��===��2^k
	int min=FindMin(arr,1,right);
	cout<<min<<endl;
}
#include<string>
void print(string s,int k)
{
	printf("%08x",k*16); //
	printf(" ");
	for(int i=0;i<8;++i)
	{
		printf("%02x ",s[k*16+i]);
	}
	printf(" ");
	for(int i=8;i<16;++i)
	{
		printf("%02x ",s[k*16+i]);
	}
	printf(" ");
	for(int i=0;i<16;++i)
	{
		printf("%c",s[k*16+i]);
	}
	printf("\n");
}
void test3()
{
	string s;
	cin>>s;
	int k=s.size()/16;
	for(int i=0;i<k;++i)
	{
		print(s,i);
	}
}

int main()
{
	//reOrderArray();
	//cout<<Jump(6);
	//TestBinaryTree();
	//test();
	//test2();
	//char c='a';
	//printf("%x",c); //61 ,a��16����Ϊ61
	test3();
	system("pause");
	return 0;
}