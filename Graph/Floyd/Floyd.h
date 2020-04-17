#pragma once

#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"

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
 * 保存路径信息的结构体
 *
 * 成员变量
 *  i ：当前节点的前驱节点
 *  dist ：最短路径长度
 */
struct Dist {
	int i;
	int dist;
};

/*
 * 最短路径结点
 *
 * 成员变量
 *  i ：当前节点
 *  dist ：最短路径
 *  next ：下一条边
 */
struct PathNode {
	int i;
	int dist;
	struct PathNode* next;
};
typedef PathNode* Path;

/*
 * 继承于邻接矩阵的图类
 */
class CGraph : public MGraph < VexType, VexInfo, EdgeInfo, FuncType >
{
public:
	CGraph() :MGraph(f, DG) {}
	~CGraph() {}

	Dist** Floyd();
	Path FloydPath(VexType V1, VexType V2);
};

/*
 * 通过 Floyd 算法求解两个顶点之间的最短路径
 *
 * 参数
 *  V1 ：源顶点
 *  V2 ：目的顶点
 *
 * 返回值
 *  Path ：如果存在 V1 到 V2 的路径，则返回对应的路径信息；如果不存在对应路径，则返回 NULL 
 */
Path CGraph::FloydPath(VexType V1, VexType V2)
{
	int vexnum = GetVexNum();
	int nBeginVexIndex = LocateVex(V1);
	int nEndVexIndex = LocateVex(V2);

	if (nBeginVexIndex < 0 || nBeginVexIndex >= vexnum || nEndVexIndex < 0 || nEndVexIndex >= vexnum) {
		return NULL;
	}

	Dist** szDist = Floyd();
	if (szDist == NULL) {
		return NULL;
	}

	if (szDist[nBeginVexIndex][nEndVexIndex].dist == INFINITY_DISTANCE) {
		return NULL;
	}

	int i = nEndVexIndex;
	Path path = NULL;
	PathNode* p = NULL;
	do 
	{
		p = new PathNode;
		p->i = i;
		p->dist = szDist[nBeginVexIndex][i].dist;
		p->next = path;
		path = p;

		i = szDist[nBeginVexIndex][i].i;
		if (i == -1) {
			break;
		}

	} while (1);

	return path;
}

/*
 * Floyd 求解各顶点之间的最短路径问题
 *
 * 返回值
 *  Dist** ：返回保存各顶点之间的最短路径的二维数组的指针
 */
Dist** CGraph::Floyd()
{
	EdgeInfo weight;
	int vexnum = GetVexNum();

	if (vexnum <= 0) {
		return NULL;
	}

	Dist** szDist = new Dist * [vexnum]();
	for (int i = 0; i < vexnum; ++i) {
		szDist[i] = new Dist[vexnum]();
	}

	for (int i = 0; i < vexnum; ++i) {
		for (int j = 0; j < vexnum; ++j) {

			if (i == j) {
				szDist[i][j].dist = 0;
				szDist[i][j].i = -1;
				continue;
			}

			memset(&weight, 0, sizeof(EdgeInfo));
			if (TRUE == GetEdgeByIndex(i, j, weight)) {
				szDist[i][j].dist = weight;
				szDist[i][j].i = i;
			}
			else {
				szDist[i][j].dist = INFINITY_DISTANCE;
				szDist[i][j].i = -1;
			}
		}
	}

	for (int k = 0; k < vexnum; ++k) {
		for (int i = 0; i < vexnum; ++i) {
			for (int j = 0; j < vexnum; ++j) {
				if (szDist[i][k].dist + szDist[k][j].dist < szDist[i][j].dist) {
					szDist[i][j].dist = szDist[i][k].dist + szDist[k][j].dist;
					szDist[i][j].i = k;
				}
			}
		}
	}

	return szDist;
}