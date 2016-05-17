#pragma once
#include <iostream>
#include <vector>
using namespace std;
class MatrList
{
public:
	MatrList();
	~MatrList();
	void SetSize(int size_);
	const int GetSize() const { return size; }
	virtual void Input() = 0;
	void Output();
	void Resize();
protected:
	int size;
	vector < pair < int, pair<int, int> > > g; // вес - вершина 1 - вершина 2
	vector < pair<int, int> > res;
	vector<int> tree_id;
};

