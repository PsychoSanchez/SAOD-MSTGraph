#pragma once
#include "vector"
class MatrGraph
{
public:
	void SetSize(int size_);
	const int GetSize() const { return size; }
	virtual void Input() = 0;
	void Output();
	void Resize();
	MatrGraph();
	~MatrGraph();
protected:
	std::vector<std::vector<int> > VecGraph;
	int size;
};

class OrGraph :public MatrGraph
{
public:
	OrGraph(){}
	~OrGraph(){}
	void Input();
};

class UnOrGraph :public MatrGraph
{
public:
	UnOrGraph(){}
	~UnOrGraph(){}
	void Input();
};