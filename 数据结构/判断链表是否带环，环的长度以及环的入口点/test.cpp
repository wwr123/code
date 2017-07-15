//判断链表是否带环  O(n)
 //（快指针走3步时，特例：1->2->3->4->5->4慢指针每次都赶超快指针一步）
 int IsLoop(Node* head)
 {
	 if(head==NULL)
		 return -1;
	 Node* solw=head;
	 Node* fast=head;
	 while(fast&&fast->next) //奇数个fast->next,偶数个fast
	 {
		 solw=solw->next;
		 fast=fast->next->next;
		 if(solw==fast)
			 return 1; //带环
	 }
	 return 0; //没带环
 }
 void fun3()
 {
	 Node* node1=new Node(2);
	 Node* node2=new Node(8);
	 Node* node3=new Node(6);
	 Node* node4=new Node(9);
	 Node* node5=new Node(5);
	 node1->next=node2;
	 node2->next=node3;
	 node3->next=node4;
	 node4->next=node5;
	 node5->next=node4;
	// node5->next=NULL;
	 cout<<IsLoop(node1)<<endl;   //1  带环
	 Node node6;  //在栈上创建了一个对象
	 cout<<IsLoop(&node6)<<endl;   //0
	 Node* node7=NULL;  //空链表
	 cout<<IsLoop(node7)<<endl;  //-1 
 }
 //求环的长度
 int LoopLen(Node* head)
 {
	 if(head==NULL)
		 return 0;
	 Node* solw=head;
	 Node* fast=head;
	 while(fast&&fast->next) //奇数个fast->next,偶数个fast
	 {
		 solw=solw->next;
		 fast=fast->next->next;
		 if(solw==fast)
		 {
			 solw=solw->next;
			 int len=1;
			 while(solw!=fast)
			 {
				 solw=solw->next;
				 len++;
			 }
			 return len;
		 }
	 }
	 return 0; //没带环
 }
 void fun4()
 {
	 Node* node1=new Node(2);
	 Node* node2=new Node(8);
	 Node* node3=new Node(6);
	 Node* node4=new Node(9);
	 Node* node5=new Node(5);
	 node1->next=node2;
	 node2->next=node3;
	 node3->next=node4;
	 node4->next=node5;
	 node5->next=node5;
	 cout<<LoopLen(node1)<<endl;
 }
 
 //求环的入口点
 //2(L+x)=L+x+Nc  -->L=Nc-x (n>=1)
 Node* LoopStart(Node* head)
 {
	 if(head==NULL)
		 return NULL;
	 Node* solw=head;
	 Node* fast=head;
	 while(fast&&fast->next) //奇数个fast->next,偶数个fast
	 {
		 solw=solw->next;
		 fast=fast->next->next;
		 if(solw==fast)
		 {
			 solw=head;
			 while(solw!=fast)
			 {
				 solw=solw->next;
				 fast=fast->next;
			 }
			 return solw;
		 }
	 }
	 return NULL;
 }
 void fun5()
 {
	 Node* node1=new Node(2);
	 Node* node2=new Node(8);
	 Node* node3=new Node(6);
	 Node* node4=new Node(9);
	 Node* node5=new Node(5);
	 node1->next=node2;
	 node2->next=node3;
	 node3->next=node4;
	 node4->next=node5;
	 node5->next=node5;
	 Node* node=LoopStart(node1);
	 cout<<node->data<<endl;
 }