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

/*
 * 顶点之间最小代价结构体
 *
 * 成员变量
 *  i, j ：i 为上一个顶点的索引，j 为当前顶点的索引
 *  weight ：i 到 j 对应边的权值
 */
struct LowCost {
	int i, j;
	int weight; 
};

/*
 * 继承与邻接矩阵的图类
 */
class CGraph :public MGraph<VexType, VexInfo, EdgeInfo, FuncType>
{
public:
	CGraph():MGraph(f, UDG) {}
	~CGraph() {}

	LowCost* MSTPrim(VexType v, int& sum);
};

/*
 * Prim 求最小生成树算法（适用于带权无向图 UDG）
 *
 * 参数
 *  v ：作为最小生成树的根节点的顶点
 *  sum ：最小生成树中所有权值的和
 *
 * 返回值
 *  LowCost ：最小生成树
 */
LowCost* CGraph::MSTPrim(VexType v, int& sum)
{
	int i = 0, j = 0;
	int vexnum = GetVexNum();
	int nVexIndex = LocateVex(v);
	int nMinArcWeight = 0;
	int nMinVexIndex = 0;
	BOOL* szVexSet = NULL;// 顶点是否被访问。true：已经被访问；false：未被访问
	LowCost* szLowcost = NULL;
	LowCost lc;
	EdgeInfo weight;// 边信息
	BOOL bRet = FALSE;
	sum = 0;
	
	if (nVexIndex < 0 || nVexIndex >= vexnum) {
		return NULL;
	}

	szLowcost = new LowCost[vexnum]();
	szVexSet = new BOOL[vexnum]();

	// 初始化顶点 v 到其他顶点 i 的路径开销
	for (i = 0; i < vexnum; ++i) {
		memset(&lc, 0, sizeof(LowCost));

		lc.i = nVexIndex;
		lc.j = i;
		if (i == nVexIndex) {
			lc.weight = 0;
		}
		else {
			bRet = GetEdgeByIndex(nVexIndex, i, weight);
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

	szVexSet[nVexIndex] = TRUE;

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
		sum = sum + nMinArcWeight;

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

	delete[] szVexSet;

	return szLowcost;
}

#endif // !__PRIM_H__
