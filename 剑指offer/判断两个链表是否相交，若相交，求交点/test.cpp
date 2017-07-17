 //判断链表是否带环
 Node* ListIsLoop(Node* head)
 {
	 Node* solw=head;
	 Node* fast=head;
	 while(fast&&fast->next) //奇数个fast->next,偶数个fast
	 {
		 solw=solw->next;
		 fast=fast->next->next;
		 if(solw==fast)
			 return solw; //带环
	 }
	 return NULL; //没带环
 }
 //判断两个链表是否相交，若相交，求交点
 Node* ListIsIntersect(Node* head1,Node* head2)
 {
	 if(head1==NULL||head2==NULL) //有一个链表为空
		 return NULL;
	 Node* p1=ListIsLoop(head1);  //判断链表1是否带环
	 Node* p2=ListIsLoop(head2);  //判断链表2是否带环
	 if(p1!=NULL&&p2!=NULL)  //两个链表都带环
	 {
		 Node* cur=p2;
		 while(cur!=p1)
		 {
			 cur=cur->next;
			 if(cur==p2) //cur走了一圈了，还没有与p1相遇，说明他们不相交
			 {
				 return NULL;
			 }
		 }
		 //说明两个链表相交
		 //带环相交有两种情况，交点在环上，交点没在环上
		 Node* start1=LoopStart(head1);
		 Node* start2=LoopStart(head2); //求环的入口点
		 if(start1==start2)  //两个链表的入口点一样，说明交点在链表上，没在环上
		 {
			 //求交点可以等价于求两个无环链表的交点
			 Node* cur1=head1;
			 Node* cur2=head2;
			 while(cur1!=cur2)
			 {
				 if(cur1==start1)
					 cur1=head2;
				 else
				 {
					 cur1=cur1->next;
				 }
				 if(cur2==start2)
					cur2=head1;
				 else
				 {
					cur2=cur2->next;
				 }
			 }
			 return cur1;

		 }
		 else  //交点在环上，两个入口点都可能是交点，随便返回一个
		 {
			 return start2;
		 }

	 }
	 else if(p1==NULL&&p2==NULL)  //两个链表都没带环
	 {
		 Node* cur1=head1;
		 Node* cur2=head2;
		 while(cur1!=cur2)
		 {
			 if(cur1==NULL)
				 cur1=head2;
			 else
			 {
				 cur1=cur1->next;
			 }
			 if(cur2==NULL)
				cur2=head1;
			 else
			 {
				cur2=cur2->next;
			 }
		 }
		 return cur1;
	 }
	 else  //一个链表带环，一个没有带环，他们肯定没有交点
	 {
		 return NULL;
	 }
 }
 void fun6()
 {
	 Node* node1=new Node(2);
	 Node* node2=new Node(8);
	 Node* node3=new Node(6);
	 Node* node4=new Node(9);
	 Node* node5=new Node(5);
	 node1->next=node2;
	 node2->next=node3;
	 node3->next=node3;

	 node4->next=node5;
	 node5->next=node3;
	 Node* node=ListIsIntersect(node1,node4);  
	 if(node!=NULL)
		cout<<node->data<<endl;
	 else
		 cout<<"0"<<endl;
 }