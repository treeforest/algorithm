#ifndef __BFS_H__
#define __BFS_H__

#include "../AdjacencyMatrix/AdjacencyMatrix.hpp"
#include <queue>
#include <iostream>
using namespace std;

#define INFINITY_DISTANCE -1

typedef char VexType;
typedef int VexInfo;
typedef int EdgeType;
typedef BOOL(*FuncType)(VexType v1, VexType v2);

BOOL f(VexType v1, VexType v2) {
	if (v1 == v2) return TRUE;
	return FALSE;
}

/*
 * 遍历元素的函数指针
 *
 * 参数
 *  index ：结点的索引
 *  v ：节点值
 */
typedef void(*VisitProc)(int index, VexType v);
void DefaultVisitProc(int index, VexType v) {
	cout << index << " " << v << endl;
}

class CGraph:public MGraph<VexType, VexInfo, EdgeType, FuncType>
{
public:
	CGraph(GraphKind kind = UDG);
	~CGraph();

	void BFSTraverse(VisitProc visit = DefaultVisitProc);
	void BFSMinDistance(VexType vex);

private:
	void BFS(int v, VisitProc visit);
	void Clear();

private:
	bool m_visited[MAX_VERTEX_NUM];// 访问标记数组
	queue<int> m_queue;// 辅助队列
};

inline CGraph::CGraph(GraphKind kind /*= UDG*/) : MGraph(f, kind)
{
	memset(m_visited, 0, sizeof(bool) * MAX_VERTEX_NUM);
}

CGraph::~CGraph() 
{

}

/*
 * 广度优先遍历
 */
void CGraph::BFSTraverse(VisitProc visit /*= DefaultVisitProc*/)
{
	Clear();
	int i = 0;

	for (i = 0; i < GetVexNum(); ++i) {
		m_visited[i] = false;
	}

	for (i = 0; i < GetVexNum(); ++i) {
		if (!(m_visited[i])) {
			BFS(i, visit);
		}
	}
}

/*
 * 使用 BFS 求解单源最短路径(适用非带权图)
 *
 * 参数
 *  vex ：路径的开始顶点
 *
 * 其他
 *  对求解的最短路径直接会在函数内进行打印输出
 */
void CGraph::BFSMinDistance(VexType vex)
{
	int vexnum = GetVexNum();
	int u = this->LocateVex(vex);

	if (u < 0 || u >= vexnum) {
		return;
	}

	Clear();

	int* szDistance = new int[vexnum]();

	for (int i = 0; i < vexnum; ++i) {
		szDistance[i] = INFINITY_DISTANCE;
	}

	m_visited[u] = true;
	szDistance[u] = 0;
	m_queue.push(u);
	int v;

	while (!m_queue.empty()) {

		v = m_queue.front();
		m_queue.pop();
		for (int w = FirstAdjVexByIndex(v); w >= 0; w = NextAdjVexByIndex(v, w)) {

			if (!m_visited[w]) {
				m_visited[w] = true;
				szDistance[w] = szDistance[v] + 1;
				m_queue.push(w);
			}
		}
	}

	// 输出打印
	cout << "序号 index = " << u << " 的顶点 " << this->GetVexVal(u) << " 到达其他顶点的距离为：" << endl;
	for (int i = 0; i < vexnum; ++i) {
		cout << "到达索引为 " << i << " 的顶点 " << this->GetVexVal(i) << " 的距离为：" << szDistance[i] << endl;
	}
}

void CGraph::BFS(int v, VisitProc visit)
{
	visit(v, this->GetVexVal(v));
	m_visited[v] = true;
	m_queue.push(v);

	while (!m_queue.empty()) {

		v = m_queue.front();
		m_queue.pop();

		for (int w = FirstAdjVexByIndex(v); w >= 0; w = NextAdjVexByIndex(v, w)) {

			if (!m_visited[w]) {
				visit(w, this->GetVexVal(w));
				m_visited[w] = true;
				m_queue.push(w);
			}
		}
	}
}

inline void CGraph::Clear()
{
	int n = m_queue.size();
	while (n > 0) {
		m_queue.pop();
		--n;
	}

	memset(m_visited, 0, sizeof(bool) * MAX_VERTEX_NUM);
}

#endif