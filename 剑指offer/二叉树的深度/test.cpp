class Solution {
public:
    int TreeDepthR(TreeNode* node)
    {
        if(node==NULL)
            return 0;
        int left=TreeDepthR(node->left);
        int right=TreeDepthR(node->right);
        return (left+1)>(right+1)?(left+1):(right+1);
    }
    int TreeDepth(TreeNode* pRoot)
    {
        if(pRoot==NULL)
            return 0;
    	int depth=TreeDepthR(pRoot);
        return depth;
    }
};