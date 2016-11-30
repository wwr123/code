#pragma once
template<class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex,size_t size,bool isHaveDirecte=false)
		:_vertex(new V[size])
		,_size(size)
		,_isHaveDirecte(isHaveDirecte)
	{
		_matrix=new W*[_size];
		for(size_t i=0;i<_size;++i)
		{
			_vertex[i]=vertex[i];
			_matrix[i]=new W[_size];
		}
		 for(size_t i=0;i<_size;++i)
		 {
			 for(size_t j=0;j<_size;++j)
			 {
				_matrix[i][j]=0;
			 }
		 }
	}
	int GetIndex(const V& v)
	{
		for(size_t i=0;i<_size;++i)
		{
			if(_vertex[i]==v)
				return i;
		}
		throw std::invalid_argument("��������");
	}
	void AddEdge(const V& v1,const V& v2,const W& w)
	{
		int index1=GetIndex(v1);
		int index2=GetIndex(v2);
		_matrix[index1][index2]=w;
		if(_isHaveDirecte==false)
			_matrix[index2][index1]=w;
	}
	void Print()
	{
	     for(size_t i=0;i<_size;++i)
		 {
			 for(size_t j=0;j<_size;++j)
			 {
				 cout<<_matrix[i][j]<<"    ";
			 }
			 cout<<endl;
		 }
	}
	~GraphMatrix()
	{
		delete[] _vertex;
		for(size_t i=0;i<_size;++i)
		{
			W* del=_matrix[i];
			delete[] del;
		}
	}
protected:
	V* _vertex;  //����ļ���
	W** _matrix;  //��Ȩֵ�ľ���
	size_t _size;
	bool _isHaveDirecte;
};
void TestGraphMatrix()
{
	string v[5]={"����","���","�Ϻ�","����","�㶫"};
	GraphMatrix<string,int> g(v,5);
	g.AddEdge ("����","���",200);
	g.AddEdge ("����","�Ϻ�",500);
	g.AddEdge ("����","���",300);
	g.AddEdge ("�㶫","����",100);
	g.Print ();
	
}