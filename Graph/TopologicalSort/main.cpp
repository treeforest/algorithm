#include "TopologicalSort.h"

CGraph g_Graph;

void InitGraph();
void Test();

int main() {
	InitGraph();
	Test();

	return 0;
}

void Test() {
	g_Graph.TopologicalSort(DefaultVisitProc);
}

void InitGraph() {
	struct Edge {
		VexType v1, v2;
	};

	VexType szVex[5] = { '1', '2', '3', '4', '5'};
	Edge szEdge[7] = { {'1', '2'}, {'1', '4'}, {'2', '3'}, {'2', '4'}, {'3', '5'}, {'4', '3'}, {'4', '5'} };

	for (int i = 0; i < 5; ++i) {
		g_Graph.InsertVex(szVex[i]);
	}

	for (int i = 0; i < 7; ++i) {
		g_Graph.InsertEdge(szEdge[i].v1, szEdge[i].v2);
	}

	g_Graph.PrintInfo();
	cout << endl << endl;
}
