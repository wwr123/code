/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if(pHead==NULL)
            return pHead;
        RandomListNode* cur=pHead;
        //1.合并
        //插节点
        while(cur)
        {
            RandomListNode* newnode=new RandomListNode(cur->label);
            newnode->next=cur->next;
            cur->next=newnode;
            cur=cur->next->next;
        }
        //连随机指针
        cur=pHead;
        while(cur)
        {
            RandomListNode* pnext=cur->next;
            if(cur->random!=NULL)  //备注：重点
                pnext->random=cur->random->next;
            else
                pnext->random=NULL;
            cur=cur->next->next;
        }
        //2.拆分
        RandomListNode* p1=pHead;
        RandomListNode* p2=pHead->next;
        cur=pHead;
        while(cur)
        {
            RandomListNode* pnext=cur->next;
            cur->next=cur->next->next;
            if(cur->next==NULL)
                pnext->next=NULL;
            else
                pnext->next=pnext->next->next;
            cur=cur->next;
        }
        return p2;
	}
    
};