class Solution {
public:
    vector<int> v;
    void Print(int startrow,int row,int startcol,int col,vector<vector<int>> matrix)
	{
        //从左到右
    	for(int i=startcol;i<col;i++)
        {
            v.push_back(matrix[startrow][i]);
        }
        //从上到下
        for(int i=startrow+1;i<row;i++)
        {
            v.push_back(matrix[i][col-1]);
        }
        //从右到左
        for(int i=col-2;i>=startcol;i--)
        {
            if(i>=startcol&&row-1!=startcol)   //要考虑只有一行情况
               v.push_back(matrix[row-1][i]);
        }
         //从下到上
        for(int i=row-2;i>=startrow;i--)
        {
            if(i>startrow&&startcol!=col-1)   //要考虑只有一列情况
               v.push_back(matrix[i][startcol]);
        }
	}
    vector<int> printMatrix(vector<vector<int> > matrix) {
    	
        int row=matrix.size();  //行数
    	if(row==0)
            return v;
    	int col=(matrix[0]).size();  //列数
    	if(col==0)
            return v;
    	int startrow=0;
    	int startcol=0;
    	while(row>startrow&&col>startcol)
        {
            Print(startrow++,row--,startcol++,col--,matrix);
            
        }
		return v;
    }
};