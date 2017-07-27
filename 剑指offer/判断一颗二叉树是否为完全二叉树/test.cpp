//判断一颗二叉树是否为完全二叉树
int TreeIsCompleteTree(Node* root)
{
	if(root==NULL)
		return 0;
	queue<Node*> q;
	Node* cur=root;
	while(cur)
	{
		q.push(cur->left);
		q.push(cur->right);
	  	cur=q.front();
		q.pop();
	}
	//cur==NULL
    while(!q.empty())
	{
		cur=q.front();
		q.pop();
		if(cur!=NULL)
			return 0;
	}
	return 1;
}
void fun6()
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
	node3->right=node6;
	node2->right=node7;
	Node* node8=NULL;
	cout<<TreeIsCompleteTree(node1)<<endl;
}