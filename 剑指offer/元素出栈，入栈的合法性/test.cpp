class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.size()!=popV.size())
            return false;
        stack<int> s;
        int j=0;
        for(int i=0;i<pushV.size();++i)
        {
            if(pushV[i]!=popV[j])
            {
                s.push(pushV[i]);
            }
            else
            {
                j++;
                while(!s.empty()&&popV[j]==s.top())
                {
                    /*if(popV[j]==s.top())
                    {
                        j++;
                    	s.pop();
                    }
                    else 
                        break;
                        */
                    j++;
                    s.pop();
                }
                
            }
        }
       
        if(s.empty())   
        {
            return true;
        }
        else
            return false;
    }
};