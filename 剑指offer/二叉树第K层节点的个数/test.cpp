//二叉树第k层节点的个数
void KNodeNumR(Node* node,int& num,int level,int k)
{
	if(level==k)
	{
		num++;
		return;
	}
	if(node->left)
		 KNodeNumR(node->left,num,level+1,k);  
	//为什么使用level+1,对下个递归函数进行了改变，但没有对本函数中的level进行改变
	if(node->right)
		 KNodeNumR(node->right,num,level+1,k);

}
int KNodeNum(Node* node,int k)
{
	if(node==NULL)
		return 0;
	int level=1;
	int num=0;
	KNodeNumR(node,num,level,k);
	return num;
}
void fun2()
{
	Node* node1=new Node(1);
	Node* node2=new Node(2);
	Node* node3=new Node(3);
	Node* node4=new Node(4);
	Node* node5=new Node(5);
	Node* node6=new Node(6);
	Node* node7=new Node(7);
	node1->left=node2;
	node1->right=node3;
	node2->left=node4;
	node3->left=node5;
	node5->left=node6;
	node3->right=node7;
	Node* node8=new Node(8);
	cout<<KNodeNum(node1,3)<<endl;
}