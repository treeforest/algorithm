#include "Floyd.h"

CGraph g_Graph;

void InitGraph();
void Test_Floyd();
void Test_FloydPath(VexType v1, VexType v2);

int main() {
	InitGraph();

	Test_Floyd();

	Test_FloydPath('a', 'c');
	Test_FloydPath('a', 'b');
	Test_FloydPath('b', 'c');
	Test_FloydPath('b', 'a');
	Test_FloydPath('c', 'a');
	Test_FloydPath('c', 'b');
}

void Test_FloydPath(VexType v1, VexType v2) {
	

	Path p = g_Graph.FloydPath(v1, v2);

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

void Test_Floyd() {
	int vexnum = g_Graph.GetVexNum();
	Dist** szDist = g_Graph.Floyd();

	cout << "Floyd 各顶点之间最短路径矩阵：" << endl;
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			cout << szDist[i][j].dist << " ";
		}
		cout << endl;
	}
	cout << "Floyd 各顶点之间最短路径前驱节点的矩阵：" << endl;
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			cout << szDist[i][j].i << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

void InitGraph() {
	struct Edge {
		VexType v1, v2;
		EdgeInfo weight;
	};

	VexType szVex[3] = { 'a', 'b', 'c' };
	Edge szEdge[5] = {
		{'a', 'b', 6}, {'a', 'c', 13},
		{'b', 'a', 10}, {'b', 'c', 4},
		{'c', 'a', 5},
	};

	for (int i = 0; i < 3; ++i) {
		g_Graph.InsertVex(szVex[i]);
	}

	for (int i = 0; i < 5; ++i) {
		g_Graph.InsertEdge(szEdge[i].v1, szEdge[i].v2, &(szEdge[i].weight));
	}

	g_Graph.PrintInfo();
	cout << endl << endl;
}
