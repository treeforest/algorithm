#pragma once

#include "../AdjacencyList/AdjacencyList.hpp"

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
 * 遍历元素的函数指针
 *
 * 参数
 *  index ：结点的索引
 *  v ：节点值
 */
typedef void(*VisitProc)(int i, VexType vex);
void DefaultVisitProc(int i, VexType vex) {
	cout << "顶点索引：" << i << "\t顶点：" << vex << endl;
}

/*
 * 继承于邻接矩阵的图类
 */
class CGraph : public ALGraph < VexType, VexInfo, EdgeInfo, FuncType >
{
public:
	CGraph() :ALGraph(f, DN) {}
	~CGraph() {}

	bool TopologicalSort(VisitProc visit);
};

/*
 * 拓扑排序
 *
 * 参数
 *  visit ：拓扑排序中访问结点的函数指针
 *
 * 返回值
 *  bool ：如果该图能进行，返回 true；否则返回 false
 */
bool CGraph::TopologicalSort(VisitProc visit)
{
	int vexnum = GetVexNum();
	if (vexnum <= 0) {
		return false;
	}

	int* indegree = new int[vexnum]();
	int* stack = new int[vexnum]();
	int top = -1;
	int count = 0;
	int i = 0, j = 0;	
	const VNode<VexType, VexInfo, EdgeInfo>* szVex = GetAdjList();
	EdgeNode<EdgeInfo>* p = NULL;

	// 初始化每个顶点的入度
	for (i = 0; i < vexnum; ++i) {
		indegree[i] = 0;
	}
	for (i = 0; i < vexnum; i++) {
		p = szVex[i].firstarc;
		while (p != NULL) {
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}

	// 初始化栈，将入度为 0 的顶点入栈
	for (i = 0; i < vexnum; ++i) {
		if (indegree[i] == 0) {
			stack[++top] = i;
		}
	}
	
	while (top != -1) {
		i = stack[top--];
		visit(i, szVex[i].val);
		count++;

		for (p = szVex[i].firstarc; p != NULL; p = p->nextarc) {
			i = p->adjvex;
			if (!(--indegree[i])) {
				stack[++top] = i;
			}
		}
	}

	delete[] indegree;
	delete[] stack;

	if (count < vexnum) {
		return false;
	}

	return true;
}