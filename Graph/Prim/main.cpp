#include "MSTPrim.h"
#include <iostream>
using namespace std;

VexType g_szVex[6] = { "V1", "V2", "V3", "V4", "V5", "V6" };
CGraph g_Graph;

void InitGraph();
void Test(VexType v1, VexType v2);

int main() {
	InitGraph();

	Test(g_szVex[0], g_szVex[5]);
	Test(g_szVex[5], g_szVex[1]);
	Test(g_szVex[3], g_szVex[4]);

	return 0;
}

void Test(VexType v1, VexType v2) {
	Path* path = g_Graph.MSTPrim(v1, v2);
	if (path == NULL) {
		cout << "没有找到对应的路径" << endl;
		return;
	}

	cout << "顶点 " << v1 << "->" << v2 << " 的依次经历的顶点为：" << endl;
	int cnt = 0;
	while (path != NULL) {
		cout << "顶点序号：" << path->i << "\t顶点：" << path->v << "\t权值：" << path->weight << endl;
		cnt = cnt + path->weight;
		path = path->next;
	}
	cout << "路径总开销为： " << cnt << endl << endl;
}

void InitGraph() {
	VexType str;
	EdgeInfo info;

	// 初始化顶点
	for (int i = 0; i < 6; i++) {
		g_Graph.InsertVex(g_szVex[i]);
	}

	// 初始化边
	info = 6;
	g_Graph.InsertEdge("V1", "V2", &info);
	info = 1;
	g_Graph.InsertEdge("V1", "V3", &info);
	info = 5;
	g_Graph.InsertEdge("V1", "V4", &info);
	info = 5;
	g_Graph.InsertEdge("V2", "V3", &info);
	info = 3;
	g_Graph.InsertEdge("V2", "V5", &info);
	info = 5;
	g_Graph.InsertEdge("V3", "V4", &info);
	info = 4;
	g_Graph.InsertEdge("V3", "V6", &info);
	info = 6;
	g_Graph.InsertEdge("V3", "V5", &info);
	info = 2;
	g_Graph.InsertEdge("V4", "V6", &info);
	info = 6;
	g_Graph.InsertEdge("V5", "V6", &info);

	g_Graph.PrintInfo();
	cout << endl << endl;
}