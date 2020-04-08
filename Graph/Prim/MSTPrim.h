#ifndef __PRIM_H__
#define __PRIM_H__

#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"
#include <string>

/***************** 最小生成树算法：Prim *****************/

#define INFINITY_DISTANCE (~(1 << (sizeof(int) * 8 - 1)))

typedef string VexType;
typedef int VexInfo;
typedef int EdgeInfo;
typedef BOOL(*FuncType)(VexType v1, VexType v2);
BOOL f(VexType v1, VexType v2) {
	if (0 == v1.compare(v2)) {
		return TRUE;
	}
	return FALSE;
}

// 到达顶点v的最小代价
struct LowCost {
	// 最小权值的边(from, to). 
	// j 为上一个顶点的索引，j 为当前顶点的索引
	int i, j;

	// i 到 j 对应边的权值
	int weight; 
};

// 保存路径的结构体
struct Path {
	int i;
	VexType v;
	int weight;
	struct Path* next;
};


// 图类
class CGraph :public MGraph<VexType, VexInfo, EdgeInfo, FuncType>
{
public:
	CGraph():MGraph(f, UDG) {}
	~CGraph() {}

	// 适用于带权无向图 UDG
	Path* MSTPrim(VexType vex, VexType vexEnd);
};


Path* CGraph::MSTPrim(VexType vexBegin, VexType vexEnd)
{
	int i = 0, j = 0;
	int vexnum = GetVexNum();
	int nBeginVexIndex = LocateVex(vexBegin);
	int nEndVexIndex = LocateVex(vexEnd);
	int nMinArcWeight = 0;
	int nMinVexIndex = 0;
	BOOL* szVexSet = NULL;// 顶点是否被访问。true：已经被访问；false：未被访问
	LowCost* szLowcost = NULL;
	LowCost lc;
	EdgeInfo weight;// 边信息
	BOOL bRet = FALSE;
	
	if (nBeginVexIndex < 0 || nBeginVexIndex >= vexnum || nEndVexIndex < 0 ||nEndVexIndex >= vexnum) {
		return NULL;
	}

	szLowcost = new LowCost[vexnum]();
	szVexSet = new BOOL[vexnum]();

	// 初始化顶点 v 到其他顶点 i 的路径开销
	for (i = 0; i < vexnum; ++i) {
		memset(&lc, 0, sizeof(LowCost));

		lc.i = nBeginVexIndex;
		lc.j = i;
		if (i == nBeginVexIndex) {
			lc.weight = 0;
		}
		else {
			bRet = GetEdgeByIndex(nBeginVexIndex, i, weight);
			if (bRet == FALSE) {
				lc.weight = INFINITY_DISTANCE;
			}
			else {
				lc.weight = weight;
			}
		}

		szVexSet[i] = FALSE;
		szLowcost[i] = lc;
	}

	szVexSet[nBeginVexIndex] = TRUE;

	// 找出最小边
	for (i = 0; i < vexnum - 1; ++i) {
		nMinArcWeight = INFINITY_DISTANCE;
		
		// 找出最小边的开销 min_arc，并用 k 记录最小开销所对应的顶点索引 j
		for (j = 0; j < vexnum; ++j) {
			if (szVexSet[j] == FALSE && szLowcost[j].weight < nMinArcWeight) {
				nMinArcWeight = szLowcost[j].weight;
				nMinVexIndex = j;
			}
		}

		// 记录 min_vex 为已访问状态
		szVexSet[nMinVexIndex] = TRUE;

		// 已找到目标顶点
		if (nMinVexIndex == nEndVexIndex) {
			break;
		}
		
		// 更新 min_vex 到其他未访问顶点的最小路径开销
		for (j = 0; j < vexnum; ++j) {

			if (szVexSet[j] == TRUE) {
				continue;
			}

			bRet = GetEdgeByIndex(nMinVexIndex, j, weight);

			if (bRet == FALSE) {
				continue;
			}
			else {
				if (weight < szLowcost[j].weight) { 
					memset(&lc, 0, sizeof(LowCost));
					lc.i = nMinVexIndex;
					lc.j = j;
					lc.weight = weight;
					szLowcost[j] = lc;
				}
			}
		}
	}

	// 记录最短距离路径
	Path* p = NULL;
	Path* path = NULL;
	i = nEndVexIndex;
	j = 0;

	path = new Path;
	path->i = i;
	path->v = GetVexVal(i);
	path->weight = szLowcost[i].weight;
	path->next = p;
	p = path;

	while (i != nBeginVexIndex && j < vexnum) {
		i = szLowcost[i].i;
		j++;

		path = new Path;
		path->i = i;
		path->v = GetVexVal(i);
		if (i == nBeginVexIndex) {
			path->weight = 0;
		}
		else {
			path->weight = szLowcost[i].weight;
		}
		path->next = p;
		p = path;
	}

	delete[] szLowcost;
	delete[] szVexSet;

	// 两个顶点之间没有路径
	if (i != nBeginVexIndex) {
		while (p != NULL) {
			path = p;
			p->next;
			delete path;
		}

		return NULL;
	}

	return p;
}

#endif // !__PRIM_H__
