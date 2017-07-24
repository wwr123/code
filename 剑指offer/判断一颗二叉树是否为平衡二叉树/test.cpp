//判断一个二叉树是否是平衡二叉树
static int ret=0;

int TreeIsAVLR(Node* node)
{
	if(node==NULL)
		return 0;	
	int left=TreeIsAVLR(node->left);
    int right=TreeIsAVLR(node->right);
	if(left>right)
	{
		if((left-right)>1)
			ret=1;
	}
	if(right>left)
	{
		if((right-left)>1)
			ret=1;
	}
	return (left+1)>(right+1)?(left+1):(right+1);
			
}
int TreeIsAVL(Node* root)
{
	if(root==NULL)
		return 1;
	int rt= TreeIsAVLR(root);
	return rt;
}
void fun3()
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
	node2->right=node7;
	Node* node8=new Node(8);
	cout<<TreeIsAVL(node1)<<endl;
	cout<<ret<<endl;
}