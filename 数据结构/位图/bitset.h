#pragma once
#include<vector>
class BitSet
{
public:
	BitSet(const size_t& range)
	{
		_bitset.resize(range>>5+1);   //>>5相当于除以32
		//(range>>3+1)  range为char
	}
	//0变为1
	void Set(const size_t& x)
	{
		size_t index=x>>5;   //得到x在第几个size_t
		size_t num=x%32;     //在得到x在第几位
		_bitset[index]|=(1<<num);  //0或1为1
	}
	//1变为0
	void ReSet(const size_t& x)
	{
		size_t index=x>>5;   //得到x在第几个size_t
		size_t num=x%32;     //在得到x在第几位
		_bitset[index]&=(~(1<<num));  //0与1为0  
	}
	//判断是0，返回false,1返回true
	bool Test(const size_t& x)
	{
		size_t index=x>>5;   //得到x在第几个size_t
		size_t num=x%32;     //在得到x在第几位
		return _bitset[index]&(1<<num);//不为0，则返回true 
	}
private:
	vector<size_t> _bitset;
};
void TestBitSet()
{
	BitSet b(64);
	for(size_t i=0;i<64;i++)
	{
		b.Set (i);
	}
}