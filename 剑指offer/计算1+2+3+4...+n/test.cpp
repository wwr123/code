class tmp
{
    public:
	tmp() 
    {
        ++n;
        sum+=n;    
    }
    static void reset()
    {
        n=0;
        sum=0;
    }
    static int GetSum()
    {
        return sum;
    }
    static int n;
    static int sum;
};
int tmp::n=0;
int tmp::sum=0;

class Solution {
public:
    int Sum_Solution(int n) {
        tmp::reset();
        tmp* a=new tmp[n];
        delete []a;
        a=NULL;
        return tmp::GetSum();
    }
};