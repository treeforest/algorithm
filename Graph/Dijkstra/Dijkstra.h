#pragma once

#include "../AdjacencyList/AdjacencyList.hpp"

#define INFINITY_DISTANCE (~(1 << (sizeof(int) * 8 - 1)))

typedef char VexType;
typedef int VexInfo;
typedef int EdgeInfo;
typedef BOOL(*FuncType)(VexType V1, VexType V2);
BOOL f(VexType V1, VexType V2) {
	if (V1 == V2) {
		return TRUE;
	}
	return FALSE;
}

/*
 * 保存最短路径信息的结构体
 *
 * 成员变量
 *  i ：当前节点索引值
 *  dist ：目标顶点到 j 的最短距离（权值和）
 *  next ：指向路径的下一个结点的指针
 */
struct Path {
	int i;
	int dist;
	struct Path* next;
};

/*
 * 继承与邻接表的图类
 */
class CGraph : public ALGraph<VexType, VexInfo, EdgeInfo, FuncType>
{
public:
	CGraph() :ALGraph(f, DG) {}
	~CGraph() {}

	Path* Dijkstra(VexType V1, VexType V2);
};

/*
 * Dijkstra 最短路径算法
 *
 * 参数
 *  V1 ：源顶点
 *  V2 ：目的顶点
 *
 * 返回值
 *  Path* ：若存在 V1 到 V2 的路径，则返回对应的路径指针；否则，返回 NULL
 */
Path* CGraph::Dijkstra(VexType V1, VexType V2) {
	bool* szState = NULL; // 标记顶点是否被访问
	int* szPre = NULL; // 保存最短路径中，当前顶点的前驱节点信息
	int* szDist = NULL; // 保存从顶点 V1 到当前顶点的最短距离（权值和）
	EdgeInfo weight = 0;
	BOOL bRet = FALSE;
	bool bFound = false;
	int i = 0, j = 0;
	int min = 0;
	int minIndex = 0;
	int vexnum = GetVexNum();
	int nBeginVexIndex = LocateVex(V1);
	int nEndVexIndex = LocateVex(V2);
	Path* p = NULL;
	Path* tmp = NULL;

	if (nBeginVexIndex < 0 || nBeginVexIndex >= vexnum || nEndVexIndex < 0 || nEndVexIndex >= vexnum) {
		return NULL;
	}

	szState = new bool[vexnum]();
	szPre = new int[vexnum]();
	szDist = new int[vexnum]();

	// Init path[] s[] dist[]
	for (int i = 0; i < vexnum; ++i) {

		memset(&weight, 0, sizeof(EdgeInfo));
		bRet = GetEdgeByIndex(nBeginVexIndex, i, weight);

		if (bRet == FALSE) {
			szDist[i] = INFINITY_DISTANCE; // not exist edge of <begin, i>
			szPre[i] = -1;
		}
		else {
			szDist[i] = weight;
			szPre[i] = nBeginVexIndex;
		}

		szState[i] = false;
	}

	szState[nBeginVexIndex] = true;
	szPre[nBeginVexIndex] = -1;
	szDist[nBeginVexIndex] = 0;

	for (i = 0; i < vexnum; ++i) {

		min = INFINITY_DISTANCE;
		for (j = 0; j < vexnum; ++j) {
			if (szState[j] == false && szDist[j] < min) {
				min = szDist[j];
				minIndex = j;
			}
		}

		// Find target vertex
		if (minIndex == nEndVexIndex) {
			bFound = true;
			break;
		}

		szState[minIndex] = true;
		for (j = 0; j < vexnum; ++j) {

			// If the vertex is not visited
			if (szState[j] == false) {

				memset(&weight, 0, sizeof(EdgeInfo));
				bRet = GetEdgeByIndex(minIndex, j, weight);
				if (bRet == FALSE) {
					continue;
				}

				// update less weight
				if (szDist[minIndex] + weight < szDist[j]) {
					szDist[j] = szDist[minIndex] + weight;
					szPre[j] = minIndex;
				}
			}
		}
	}

	// Test print
// 	for (int i = 0; i < vexnum; i++) {
// 		cout << "[" << i << "] pre = " << szPre[i] << " dist = " << szDist[i] << endl;
// 	}	
	
	p = NULL;
	if (bFound == TRUE) {

		i = nEndVexIndex;
		while (i != -1) {
			tmp = new Path;
			tmp->i = i;
			tmp->dist = szDist[i];
			tmp->next = p;
			p = tmp;
			
			i = szPre[i];
		}
	}
	
	delete[] szState;
	delete[] szPre;
	delete[] szDist;

	return p;
}
