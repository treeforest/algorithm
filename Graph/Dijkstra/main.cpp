#include "Dijkstra.h"

// 记录有向边<v1, v2>以及对应的权值weight
struct Edge{
	VexType v1, v2;
	EdgeInfo weight;
};

VexType szVex[5] = { 'a', 'b', 'c', 'd', 'e' };
Edge szEdge[10] = {
	{'a', 'b', 10}, {'a', 'e', 5},
	{'b', 'c', 1}, {'b', 'e', 2},
	{'c', 'd', 4},
	{'d', 'a', 7},{'d', 'c', 6},
	{'e', 'b', 3}, {'e', 'c', 9}, {'e', 'd', 2}
};

CGraph g_Graph;
void InitGraph();
void Test(VexType v1, VexType v2);

int main() {

	InitGraph();

	Test('a', 'c');
	Test('a', 'd');
	Test('b', 'd');
	Test('b', 'a');

	return 0;
}

void Test(VexType v1, VexType v2) {
	Path* p = g_Graph.Dijkstra(v1, v2);

	cout << "顶点 " << v1 << "->" << v2 << " 的依次经历的顶点为：" << endl;

	if (p == NULL) {
		cout << "没有找到对应的路径...";
		return;
	}
	else {
		while (p != NULL) {
			cout << "顶点序号：" << p->i << "\t顶点：" << g_Graph.GetVexVal(p->i) << "\t最短路径长度：" << p->dist << endl;
			p = p->next;
		}
	}

	cout << endl << endl;
}

void InitGraph(){
	// 初始化顶点
	for (int i = 0; i < 5; ++i) {
		g_Graph.InsertVex(szVex[i]);
	}

	// 初始化边
	EdgeInfo weight;
	for (int i = 0; i < 10; ++i) {
		weight = szEdge[i].weight;
		g_Graph.InsertEdge(szEdge[i].v1, szEdge[i].v2, &weight);
	}

	g_Graph.PrintInfo();
	cout << endl << endl;
}
