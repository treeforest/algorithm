#include "MSTPrim.h"
#include <iostream>
using namespace std;

VexType g_szVex[6] = { "V1", "V2", "V3", "V4", "V5", "V6" };
CGraph g_Graph;

void InitGraph();
void Test(VexType v);

int main() {
	InitGraph();

	Test(g_szVex[0]);
	Test(g_szVex[5]);
	Test(g_szVex[3]);

	return 0;
}

void Test(VexType v) {
	int sum = 0;

	LowCost* lc = g_Graph.MSTPrim(v, sum);
	if (lc == NULL) {
		cout << "没有找到对应的最小生成树" << endl;
		return;
	}

	cout << "以顶点 " << v << " 为根结点的最小生成树：\ni : 前驱结点序号\nj : 当前结点序号\nweight ：i 到 j 的权值\n";
	int n = g_Graph.GetVexNum();
	for (int i = 0; i < n; i++) {
		cout << "i = " << lc[i].i << ", j = " << lc[i].j << ", weight = " << lc[i].weight << endl;
	}

	cout << "权值总和为： " << sum << endl << endl;
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