class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> v;
        if(root==NULL)
            return v;
    	queue<TreeNode*> q;
    	q.push(root);
        while(!q.empty())
        {
            TreeNode* front=q.front();
            q.pop();
            v.push_back(front->val);
            if(front->left)
                q.push(front->left);
            if(front->right)
                q.push(front->right);
        }
        return v;

    }
};