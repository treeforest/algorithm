#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include "../public/define.h"
#include <iostream>
using namespace std;

/**************************
 *     邻接表存储结构
 *************************/

/*
 * 边表节点
 */
template<typename EdgeType>
struct EdgeNode
{
    // 该边所指向的顶点的位置
    int adjvex;

    // 该边相关的信息
    EdgeType info;

    // 该边信息 info 是否有记录
    unsigned int valid : 1;
    
    // 指向下一条边的指针
    struct EdgeNode<EdgeType>* nextarc;
};

/*
 * 顶点节点
 */
template<typename VexType, typename EdgeType>
struct VNode 
{
    // 顶点信息
    VexType data;

    // 指向第一条依附该顶点的弧的指针
	EdgeNode<EdgeType>* firstarc;
};

/*
 * 默认的CompareFunc类型以及默认的顶点比较函数
 */
typedef BOOL(*CompareFuncType)(char* v1, char* v2);
BOOL DefaultCompare(char* v1, char* v2) {
	if (0 == strcmp(v1, v2)) {
		return TRUE;
	}
	return FALSE;
}

/*
 * 邻接表存储结构
 * CompareFunc: 比较顶点值的函数指针，函数格式： BOOL FunctionName(VertexType v, VertexType w);要求：相同返回TRUE，否则返回FALSE
 */
template<typename VexType, typename EdgeType, typename CompareFunc>
class ALGraph 
{
public:
    ALGraph(CompareFunc func, GraphKind kind = DG);
    virtual ~ALGraph();

	// 在图G中插入顶点, 返回当前顶点的索引号
	virtual int InsertVex(const VexType v);

	// 在图G中删除顶点
	virtual BOOL DeleteVex(const VexType v);
	virtual BOOL DeleteVexByIndex(const int i);

    // 若无向边(x, y)或有向边<x, y>不存在，则向图G中添加该边。
    // 如果 modify == true，则在存在 Edge 的情况下进行修改该边的弧信息；如果 modify 为 false，在边已经存在的请款下会返回 FALSE
	virtual BOOL InsertEdge(VexType v, VexType w, EdgeType* pInfo = NULL, BOOL modify = TRUE);
	virtual BOOL InsertEdgeByIndex(int i, int j, EdgeType* pInfo = NULL, BOOL modify = TRUE);

	// 若无向边(x, y)或有向边<x, y>存在，则从图G中删除该边。若边不存在则返回 FALSE，设置成功返回 TRUE。
	virtual BOOL DeleteEdge(VexType v, VexType w);
	virtual BOOL DeleteEdgeByIndex(int i, int j);

    // 是否存在边（v, w）或 <v, w>
    virtual BOOL ExistEdge(VexType v, VexType w);
    virtual BOOL ExistEdgeByIndex(int i, int j);

	// 若图中存在顶点 value,则返回该顶点在图中位置；否则返回-1
	virtual int LocateVex(const VexType v);

	// 若图中存在顶点 value，则返回 TRUE，否则返回 FALSE
	virtual BOOL ExistVex(const VexType v);
	virtual BOOL ExistVexByIndex(const int i);

	// 求图G中顶点 x 的第一个邻接点。若有，则返回顶点号；若 x 没有邻接点或不存在 x，则返回-1。
	virtual int FirstAdjVex(const VexType v);
	virtual int FirstAdjVexByIndex(int i);

	// 假设图G中顶点 y 是顶点 x 的一个邻接点，返回除 y 之外顶点 x 的下一个邻接点的顶点号；若 y 是 x 的最后一个邻接点，则返回 -1。
	virtual int NextAdjVex(const VexType v, const VexType w);
	virtual int NextAdjVexByIndex(int i, int j);

	// 获取索引为 i 的顶点信息
	virtual VexType GetVexByIndex(int i) const { return m_szVex[i].data; }

	// 获取当前图的类型
	virtual GraphKind GetGraphKind() const { return m_graphKind; }

	// 获取当前顶点数量
	virtual int GetVexNum() const { return m_vexnum; }

	// 测试输出
	void PrintInfo();

private:
	// 屏蔽默认构造函数
	ALGraph() {}

	BOOL deleteEdge(int i, int j);

private:
    // 邻接表
    VNode<VexType, EdgeType> m_szVex[MAX_VERTEX_NUM];

    // 图当前的顶点数
    int m_vexnum;

    // 图当前的弧数
    int m_arcnum;

    // 图的种类标志
    GraphKind m_graphKind;

	// 顶点的比较函数
	CompareFunc compare;
};

template<typename VexType, typename EdgeType, typename CompareFunc>
ALGraph<VexType, EdgeType, CompareFunc>::ALGraph(CompareFunc func, GraphKind kind /*= DG*/)
{
    memset(m_szVex, 0, sizeof(VNode<VexType, EdgeType>) * MAX_VERTEX_NUM);
    m_arcnum = 0;
    m_vexnum = 0;
    m_graphKind = kind;
	compare = func;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
ALGraph<VexType, EdgeType, CompareFunc>::~ALGraph()
{

}


template<typename VexType, typename EdgeType, typename CompareFunc>
int ALGraph<VexType, EdgeType, CompareFunc>::InsertVex(const VexType v)
{
    int loc = -1;

    if (!ExistVex(v)) {
		VNode<VexType, EdgeType> vex;
		vex.data = v;
		vex.firstarc = NULL;

		loc = m_vexnum++;
		m_szVex[loc] = vex;
    }

    return loc;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::DeleteVex(const VexType v)
{
	return DeleteVexByIndex(LocateVex(v));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::DeleteVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}

	// 删除边
	int j = 0;
	EdgeNode<EdgeType>* p = NULL;
	EdgeNode<EdgeType>* q = NULL;

	for (j = 0; j < m_vexnum; ++j) {

		p = m_szVex[j].firstarc;

		if (j == i) {
			while (p) {
				q = p->nextarc;
				delete p;
				p = q;
				--m_arcnum;
			}
			m_szVex[j].firstarc = NULL;
		}
		else {
			if (p != NULL && p->adjvex == i) {
				m_szVex[j].firstarc = p->nextarc;
				delete p;
				--m_arcnum;
			}
			else
			{
				while (p) {
					if (p->adjvex == i) {
						q->nextarc = p->nextarc;
						delete p;
						--m_arcnum;
						break;
					}
					q = p;
					p = p->nextarc;
				}
			}
		}
	}

	// 删除顶点
	for (j = 0; j < m_vexnum; ++j) {

		if (j == i) {
			continue;
		}

		p = m_szVex[j].firstarc;
		while (p) {
			// 删除索引为 i 的顶点后，> i 的顶点往前移，索引减少1
			if (p->adjvex > i) {
				(p->adjvex)--;
			}
			p = p->nextarc;
		}

		// 移动元素
		if (j > i) {
			m_szVex[j - 1] = m_szVex[j];
		}
	}

	memset(&m_szVex[m_vexnum - 1], 0, sizeof(VNode<VexType, EdgeType>));
	--m_vexnum;

	return TRUE;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::InsertEdge(VexType v, VexType w, EdgeType* pInfo /*=NULL*/, BOOL modify)
{
    return InsertEdgeByIndex(LocateVex(v), LocateVex(w), pInfo, modify);
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::InsertEdgeByIndex(int i, int j, EdgeType* pInfo /*=NULL*/, BOOL modify)
{
	if (i < 0 || i > m_vexnum || j < 0 || j > m_vexnum) {
		return FALSE;
	}

	if (ExistEdgeByIndex(i, j) && modify == FALSE) {
		return FALSE;
	}

	VNode<VexType, EdgeType>* p = NULL;

	p = &m_szVex[i];
	EdgeNode<EdgeType>* arc = new EdgeNode<EdgeType>();
	arc->adjvex = j;
	if (pInfo == NULL) {
		arc->valid = INVALID;
	}
	else {
		arc->info = *pInfo;
		arc->valid = VALID;
	}
	arc->nextarc = p->firstarc;
	p->firstarc = arc;

	if (m_graphKind == UDG || m_graphKind == UDN) {
		// 无向图
		p = &m_szVex[j];

		EdgeNode<EdgeType>* arc2 = new EdgeNode<EdgeType>();
		arc2->adjvex = i;
		if (pInfo == NULL) {
			arc2->valid = INVALID;
		}
		else {
			arc2->info = *pInfo;
			arc2->valid = VALID;
		}
		arc2->nextarc = p->firstarc;
		p->firstarc = arc2;

		++m_arcnum;
	}

	++m_arcnum;

	return TRUE;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::DeleteEdge(VexType v, VexType w)
{
	return DeleteEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::DeleteEdgeByIndex(int i, int j)
{
	if (deleteEdge(i, j) == FALSE) {
		return FALSE;
	}

	if (m_graphKind == UDG || m_graphKind == UDN) {
		deleteEdge(j, i);
	}

	return TRUE;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::ExistEdge(VexType v, VexType w)
{
	return ExistEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::ExistEdgeByIndex(int i, int j)
{
    if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		EdgeNode<EdgeType>* p = m_szVex[i].firstarc;
		while (p)
		{
			if (p->adjvex == j) {
				return TRUE;
			}

			p = p->nextarc;
		}
    }

    return FALSE;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline int ALGraph<VexType, EdgeType, CompareFunc>::LocateVex(const VexType v)
{
    int i = 0;
	for (i; i < m_vexnum; ++i) {
		if (compare(m_szVex[i].data, v) == TRUE) {
			break;
		}
	}

    if (i == m_vexnum) {
        return -1;
    }

    return i;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::ExistVex(const VexType v)
{
    return ExistVexByIndex(LocateVex(v));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::ExistVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}
	return TRUE;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline int ALGraph<VexType, EdgeType, CompareFunc>::FirstAdjVex(const VexType v)
{
	return FirstAdjVexByIndex(LocateVex(v));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline int ALGraph<VexType, EdgeType, CompareFunc>::FirstAdjVexByIndex(int i)
{
	if (i >= 0 && i < m_vexnum) {
		EdgeNode<EdgeType>* p = m_szVex[i].firstarc;
		if (p != NULL) {
			return p->adjvex;
		}
	}

	return -1;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline int ALGraph<VexType, EdgeType, CompareFunc>::NextAdjVex(const VexType v, const VexType w)
{
	return NextAdjVexByIndex(LocateVex(v), LocateVex(w));
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline int ALGraph<VexType, EdgeType, CompareFunc>::NextAdjVexByIndex(int i, int j)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		EdgeNode<EdgeType>* p = NULL;
		p = m_szVex[i].firstarc;
		while (p)
		{
			if (p->adjvex == j) {
				p = p->nextarc;
				break;
			}

			p = p->nextarc;
		}

		if (p != NULL) {
			return p->adjvex;
		}
	}

	return -1;
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline void ALGraph<VexType, EdgeType, CompareFunc>::PrintInfo()
{
	cout << "当前顶点已使用空间：" << m_vexnum << endl;
	cout << "当前边所使用的空间：" << m_arcnum << endl;

	// 打印顶点信息
	cout << "当前顶点信息如下：(共有 " << m_vexnum << " 个顶点)" << endl;
	for (int i = 0; i < m_vexnum; i++) {
		cout << "第 " << i + 1 << " 个顶点的信息为：" << m_szVex[i].data << endl;
	}
	
	// 打印边信息
	if (m_graphKind == DG || m_graphKind == DN) {
		cout << "当前有向边共有：" << m_arcnum << "条" << endl;
	}
	else {
		cout << "当前无向边共有：" << m_arcnum << "条" << endl;
	}
	
	int num = 0;
	for (int i = 0; i < m_vexnum; i++) {
		EdgeNode<EdgeType>* p = m_szVex[i].firstarc;
		while (p) {
			if (m_graphKind == DG || m_graphKind == DN) {
				cout << "第 " << ++num << " 条边 <" << m_szVex[i].data << "," << m_szVex[p->adjvex].data << "> 的信息为: " << p->info << endl;
			}
			else {
				cout << "第 " << ++num << " 条边 (" << m_szVex[i].data << "," << m_szVex[p->adjvex].data << ") 的信息为: " << p->info << endl;
			}
			p = p->nextarc;
		}
	}
	
}

template<typename VexType, typename EdgeType, typename CompareFunc>
inline BOOL ALGraph<VexType, EdgeType, CompareFunc>::deleteEdge(int i, int j)
{
	if (i < 0 || i > m_vexnum || j < 0 || j > m_vexnum) {
		return FALSE;
	}

	if (!ExistEdgeByIndex(i, j)) {
		return FALSE;
	}

	EdgeNode<EdgeType>* p = NULL;
	EdgeNode<EdgeType>* q = NULL;

	p = m_szVex[i].firstarc;
	if (p == NULL) {
		return FALSE;
	}

	if (p->adjvex == j) {
		m_szVex[i].firstarc = p->nextarc;
		delete p;
	}
	else {
		while (p) {
			if (p->adjvex == j) {
				q->nextarc = p->nextarc;
				delete p;
				break;
			}
			q = p;
			p = p->nextarc;
		}
	}

	--m_arcnum;
	
	return TRUE;
}


#endif // !__ADJACENCYLIST_H__