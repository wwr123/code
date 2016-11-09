#pragma once
#include<vector>
class BitSet
{
public:
	BitSet(const size_t& range)
	{
		_bitset.resize(range>>5+1);   //>>5�൱�ڳ���32
		//(range>>3+1)  rangeΪchar
	}
	//0��Ϊ1
	void Set(const size_t& x)
	{
		size_t index=x>>5;   //�õ�x�ڵڼ���size_t
		size_t num=x%32;     //�ڵõ�x�ڵڼ�λ
		_bitset[index]|=(1<<num);  //0��1Ϊ1
	}
	//1��Ϊ0
	void ReSet(const size_t& x)
	{
		size_t index=x>>5;   //�õ�x�ڵڼ���size_t
		size_t num=x%32;     //�ڵõ�x�ڵڼ�λ
		_bitset[index]&=(~(1<<num));  //0��1Ϊ0  
	}
	//�ж���0������false,1����true
	bool Test(const size_t& x)
	{
		size_t index=x>>5;   //�õ�x�ڵڼ���size_t
		size_t num=x%32;     //�ڵõ�x�ڵڼ�λ
		return _bitset[index]&(1<<num);//��Ϊ0���򷵻�true 
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