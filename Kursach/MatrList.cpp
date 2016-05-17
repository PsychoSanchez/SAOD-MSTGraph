#include "stdafx.h"
#include "MatrList.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

MatrList::MatrList()
{
}


MatrList::~MatrList()
{
}

void MatrList::SetSize(int size_)
{
	size = size_;
	Resize();
}

void MatrList::Output()
{
	/*for (int i = 0; i<size; ++i)
	{
		std::copy(VecGraph[i].begin(), VecGraph[i].end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
	for (int i = 0; i<size; ++i)
	{
		for (int j = 0; j<size; ++j)
		{
			if (VecGraph[i][j] == 1)
				std::cout << i + 1 << " node is connected with " << j + 1 << " node.\n";
		}
	}*/
}

void MatrList::Resize()
{
	g.resize(size);
	sort(g.begin(), g.end());
	for (int i = 0; i<size; ++i)
		tree_id[i] = i;
}