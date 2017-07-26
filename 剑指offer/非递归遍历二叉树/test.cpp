//前序遍历二叉树 根 左 右
void PrevOrder(Node* root)
{
	if(root==NULL)
		return;
	stack<Node*> s;
	s.push(root);
	while(!s.empty())
	{
		Node* node=s.top();
		s.pop();
		cout<<node->data<<" ";
		if(node->right)
			s.push(node->right);
		if(node->left)
			s.push(node->left);
	}
	cout<<endl;
}
//中序遍历二叉树   左 根 右
void InOrder(Node* root)
{
	if(root==NULL)
		return;
	stack<Node*> s;
	while(root||!s.empty()) //划分为子问题
	
	{
		while(root)
		{
			s.push(root);
			root=root->left;
		}
		//root->left==NULL
		Node* node=s.top();
		s.pop();
		cout<<node->data<<" ";
		root=node->right;
	}
	cout<<endl;
}
void PostOrder(Node* root)
{
	if(root==NULL)
		return;
	stack<Node*> s;
	Node* prev=NULL;
	while(root||!s.empty())
	{
		while(root)
		{
			s.push(root);
			root=root->left;
		}
		Node* top=s.top();
		if(top->right==NULL||top->right==prev)
		{
			s.pop();
			cout<<top->data<<" ";
			prev=top;
		}
		else
		{
			root=top->right;
		}
	}
	cout<<endl;
}
void fun4()
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
	InOrder(node1);
}