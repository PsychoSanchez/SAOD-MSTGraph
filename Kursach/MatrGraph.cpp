#include "stdafx.h"
#include "MatrGraph.h"
#include <iostream>
#include <algorithm>
#include <iterator>


MatrGraph::MatrGraph()
{
}


MatrGraph::~MatrGraph()
{
}
//Functions for abstract Graph
void MatrGraph::SetSize(int size_)
{
	size = size_;
	Resize();
}

void MatrGraph::Output()
{
	for (int i = 0; i<size; ++i)
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
	}
}

void MatrGraph::Resize()
{
	VecGraph.resize(size);
	for (int i = 0; i<size; ++i)
		VecGraph[i].resize(size);
}

//Functions for UnOrMatrGraph
void UnOrGraph::Input()
{
	for (int i = 0; i<size; ++i)
	{
		for (int j = 0; j<size; ++j)
		{
			if (i>j)
				continue;
			std::cout << "Enter 1 for connect " << i + 1 << " node with " << j + 1 << " node: ";
			std::cin >> VecGraph[i][j];
			while (VecGraph[i][j] < 0 || VecGraph[i][j]>1)
			{
				std::cout << "Попробуйте снова. Enter 1 for connect " << i + 1 << " node with " << j + 1 << " node: ";
				std::cin >> VecGraph[i][j];
			}
			if (i != j)
				VecGraph[j][i] = VecGraph[i][j];
		}
	}
}

//Functions for OrMatrGraph
void OrGraph::Input()
{
	for (int i = 0; i<size; ++i)
	{
		for (int j = 0; j<size; ++j)
		{
			std::cout << "Enter 1 for connect " << i + 1 << " node with " << j + 1 << " node: ";
			std::cin >> VecGraph[i][j];
			while (VecGraph[i][j] < 0 || VecGraph[i][j]>1)
			{
				std::cout << "Попробуйте снова. Enter 1 for connect " << i + 1 << " node with " << j + 1 << " node: ";
				std::cin >> VecGraph[i][j];
			}
		}
	}
}