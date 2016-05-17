// Kursach.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MatrGraph.h"
#include "iostream"
#include "windows.h"
#include <vector>
#include <algorithm> 
#include <utility>


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	

	//int cost = 0;
	//vector < pair<int, int> > res;

	/*sort(g.begin(), g.end());
	vector<int> tree_id(n);
	for (int i = 0; i<n; ++i)
		tree_id[i] = i;
	for (int i = 0; i<m; ++i)
	{
		int a = g[i].second.first, b = g[i].second.second, l = g[i].first;
		if (tree_id[a] != tree_id[b])
		{
			cost += l;
			res.push_back(make_pair(a, b));
			int old_id = tree_id[a], new_id = tree_id[b];
			for (int j = 0; j<n; ++j)
				if (tree_id[j] == old_id)
					tree_id[j] = new_id;
		}
	}*/
	setlocale(LC_ALL,"rus");
	std::cout << "Введите тип представления графа в памяти ЭВМ"<<std::endl;
	int switch_on;
	std::cin >> switch_on;
	switch (switch_on)
	{
	case 1:
	{
		std::cout << "Матрица смежности\n";
		int size = -1;
		int state = 0;

		MatrGraph* pOb;

		std::cout << "Введите количество нодов (Учтите не меньше нуля): ";
		while (size <= 0)
		{
			std::cin >> size;
			if (size == 0)
			{
				std::cout << "Это пустой граф. Попробуйте другой граф.\n";
			}
		}
		

		std::cout << "Выберите тип графа: Введите 1 для неориентированного графа и 2 для ориентированного: ";
		std::cin >> state;
		if ((state <1 || state > 2))
		{
			bool trigger = false;
			while (!trigger)
			{
				std::cout << "\n1(Неориентированный) или 2(Ориентированный)?";
				std::cin >> state;
				if (state == 1 || state == 2)
					trigger = true;
			}
		}
		if (state == 2) pOb = new OrGraph;
		else pOb = new UnOrGraph;
		pOb->SetSize(size);
		pOb->Input();
		pOb->Output();
		break;
	}
	case 2:
		std::cout << "Массив дуг";
		break;
	case 3:
		std::cout << "Списки смежности";
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}

