#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include <iostream>
using namespace std;

/**************************
 *     邻接表存储结构
 *************************/

#define MAX_VERTEX_NUM 64

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define EXIST 0x1
#define NOTEXIST 0x0

#define VALID 0x1
#define INVALID 0x0

enum GraphKind {
	// 有向图（带权值）
	DG,

	// 有向网
	DN,

	// 无向图（带权值）
	UDG,

	// 无向网
	UDN,
};


/*
 * 边表节点
 */
template<typename EdgeInfo>
struct EdgeNode
{
    // 该边所指向的顶点的位置
    int adjvex;

    // 该边相关的信息
    EdgeInfo info;

    // 该边是否存在 info 记录
    unsigned int valid : 1;
    
    // 指向下一条边的指针
    struct EdgeNode<EdgeInfo>* nextarc;
};

/*
 * 顶点节点
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo>
struct VNode 
{
    // 顶点
    VertexType val;

	// 顶点信息
	VertexInfo info;

	// 该边是否存在 info 记录
	unsigned int valid : 1;

    // 指向第一条依附该顶点的弧的指针
	EdgeNode<EdgeInfo>* firstarc;
};

//
// CompareFunc 书写格式
//
// typedef char VexType;
// typedef BOOL(*CompareFuncType)(VexType v1, VexType v2);
// BOOL DefaultCompare(VexType v1, VexType v2) {
// 	if (v1 == v2) {
// 		return TRUE;
// 	}
// 	return FALSE;
// }

/*
 * 邻接表存储结构
 * CompareFunc: 比较顶点值的函数指针，函数格式： BOOL FunctionName(VertexType v, VertexType w);要求：相同返回TRUE，否则返回FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
class ALGraph 
{
public:
    ALGraph(CompareFunc func, GraphKind kind = DG);
    virtual ~ALGraph();

	// 在图G中插入顶点, 返回当前顶点的索引号
	virtual int InsertVex(const VertexType v);

	// 设置顶点信息. 如果顶点不存在，则返回FALSE；否则记录顶点信息
	// modify 字段: = TRUE,则当顶点信息存在时，就修改顶点信息；否则在顶点信息存在的情况下，直接返回 FALSE
	virtual BOOL SetVex(const VertexType v, const VertexInfo info, BOOL modify = TRUE);
	virtual BOOL SetVexByIndex(int i, const VertexInfo info, BOOL modify = TRUE);

	// 获取顶点信息
	virtual BOOL GetVex(const VertexType v, VertexInfo& info);
	virtual BOOL GetVexByIndex(int i, VertexInfo& info);

	// 在图G中删除顶点
	virtual BOOL DeleteVex(const VertexType v);
	virtual BOOL DeleteVexByIndex(const int i);

    // 若无向边(x, y)或有向边<x, y>不存在，则向图G中添加该边。
    // 如果 modify == true，则在存在 Edge 的情况下进行修改该边的弧信息；如果 modify 为 false，在边已经存在的请款下会返回 FALSE
	virtual BOOL InsertEdge(VertexType v, VertexType w, EdgeInfo* pInfo = NULL, BOOL modify = TRUE);
	virtual BOOL InsertEdgeByIndex(int i, int j, EdgeInfo* pInfo = NULL, BOOL modify = TRUE);

	// 若无向边(x, y)或有向边<x, y>存在，则从图G中删除该边。若边不存在则返回 FALSE，设置成功返回 TRUE。
	virtual BOOL DeleteEdge(VertexType v, VertexType w);
	virtual BOOL DeleteEdgeByIndex(int i, int j);

	// 设置图G中边(x, y)或<x, y>对应的权值 value。若边不存在则返回 FALSE，设置成功返回 TRUE。
	virtual BOOL SetEdge(VertexType v, VertexType w, EdgeInfo* pInfo);
	virtual BOOL SetEdgeByIndex(int i, int j, EdgeInfo* pInfo);

	// 获取图G中边(x, y)或<x, y>对应的权值。
	virtual BOOL GetEdge(VertexType v, VertexType w, EdgeInfo& info);
	virtual BOOL GetEdgeByIndex(int i, int j, EdgeInfo& info);

    // 是否存在边（v, w）或 <v, w>
    virtual BOOL ExistEdge(VertexType v, VertexType w);
    virtual BOOL ExistEdgeByIndex(int i, int j);

	// 若图中存在顶点 value,则返回该顶点在图中位置；否则返回-1
	virtual int LocateVex(const VertexType v);

	// 若图中存在顶点 value，则返回 TRUE，否则返回 FALSE
	virtual BOOL ExistVex(const VertexType v);
	virtual BOOL ExistVexByIndex(const int i);

	// 求图G中顶点 x 的第一个邻接点。若有，则返回顶点号；若 x 没有邻接点或不存在 x，则返回-1。
	virtual int FirstAdjVex(const VertexType v);
	virtual int FirstAdjVexByIndex(int i);

	// 假设图G中顶点 y 是顶点 x 的一个邻接点，返回除 y 之外顶点 x 的下一个邻接点的顶点号；若 y 是 x 的最后一个邻接点，则返回 -1。
	virtual int NextAdjVex(const VertexType v, const VertexType w);
	virtual int NextAdjVexByIndex(int i, int j);

	// 获取索引为 i 的顶点信息
	virtual VertexType GetVexVal(int i) const { return m_szVex[i].val; }

	// 获取当前图的类型
	virtual GraphKind GetGraphKind() const { return m_graphKind; }

	// 获取当前顶点数量
	virtual int GetVexNum() const { return m_vexnum; }

	// 获取邻接表。
	virtual const VNode<VertexType, VertexInfo, EdgeInfo>* GetAdjList() const { return m_szVex; }

	// 测试输出
	void PrintInfo();

private:
	// 屏蔽默认构造函数
	ALGraph() {}

	BOOL deleteEdge(int i, int j);

private:
    // 邻接表
    VNode<VertexType, VertexInfo, EdgeInfo> m_szVex[MAX_VERTEX_NUM];

    // 图当前的顶点数
    int m_vexnum;

    // 图当前的弧数
    int m_arcnum;

    // 图的种类标志
    GraphKind m_graphKind;

	// 顶点的比较函数
	CompareFunc compare;
};


template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ALGraph(CompareFunc func, GraphKind kind /*= DG*/)
{
    //memset(m_szVex, 0, sizeof(VNode<VexType, EdgeType>) * MAX_VERTEX_NUM);
    m_arcnum = 0;
    m_vexnum = 0;
    m_graphKind = kind;
	compare = func;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::~ALGraph()
{

}


template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertVex(const VertexType v)
{
    int loc = -1;

    if (!ExistVex(v)) {
		VNode<VertexType, VertexInfo, EdgeInfo> vex;
		vex.val = v;
		vex.firstarc = NULL;
		vex.valid = INVALID;

		loc = m_vexnum++;
		m_szVex[loc] = vex;
    }

    return loc;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVex(const VertexType v, const VertexInfo info, BOOL modify)
{
	return SetVexByIndex(LocateVex(v), info, modify);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVexByIndex(int i, const VertexInfo info, BOOL modify)
{
	if (i < 0 || i >= m_vexnum) {
		return FALSE;
	}

	if (m_szVex[i].valid == VALID && modify == FALSE) {
		return FALSE;
	}

	m_szVex[i].info = info;
	m_szVex[i].valid = VALID;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVex(const VertexType v, VertexInfo& info)
{
	return GetVexByIndex(LocateVex(v), info);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexByIndex(int i, VertexInfo& info)
{
	if (i < 0 || i >= m_vexnum) {
		return FALSE;
	}

	if (m_szVex[i].valid == INVALID) {
		return FALSE;
	}

	info = m_szVex[i].info;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVex(const VertexType v)
{
	return DeleteVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}

	// 删除边
	int j = 0;
	EdgeNode<EdgeInfo>* p = NULL;
	EdgeNode<EdgeInfo>* q = NULL;

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

	memset(&m_szVex[m_vexnum - 1], 0, sizeof(VNode<VertexType, VertexInfo, EdgeInfo>));
	--m_vexnum;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdge(VertexType v, VertexType w, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
{
    return InsertEdgeByIndex(LocateVex(v), LocateVex(w), pInfo, modify);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdgeByIndex(int i, int j, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
{
	if (i < 0 || i > m_vexnum || j < 0 || j > m_vexnum) {
		return FALSE;
	}

	BOOL exist = ExistEdgeByIndex(i, j);
	EdgeNode<EdgeInfo>* node = NULL;
	VNode<VertexType, VertexInfo, EdgeInfo>* p = NULL;

	// 有向网 或 无向网
	if (m_graphKind == DN || m_graphKind == UDN) {

		if (exist == TRUE) {
			return TRUE;
		}
		node = new EdgeNode<EdgeInfo>();
		node->valid = VALID;
	}
	// 有向图 或 无向图
	else {

		if ((exist == TRUE && modify == FALSE) || pInfo == NULL) {
			return FALSE;
		}
		node = new EdgeNode<EdgeInfo>();
		node->valid = VALID;
		node->info = *pInfo;
	}

	p = &m_szVex[i];
	node->adjvex = j;
	node->nextarc = p->firstarc;
	p->firstarc = node; // Insert head
	++m_arcnum;

	if (m_graphKind == UDG || m_graphKind == UDN) {
		// 无向图
		p = &m_szVex[j];
		EdgeNode<EdgeInfo>* node2 = new EdgeNode<EdgeInfo>();
		node2->adjvex = i;
		node2->info = node->info;
		node2->valid = node->valid;
		node2->nextarc = p->firstarc;
		p->firstarc = node2;

		++m_arcnum;
	}

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdge(VertexType v, VertexType w)
{
	return DeleteEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdgeByIndex(int i, int j)
{
	if (deleteEdge(i, j) == FALSE) {
		return FALSE;
	}

	if (m_graphKind == UDG || m_graphKind == UDN) {
		deleteEdge(j, i);
	}

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdge(VertexType v, VertexType w, EdgeInfo* pInfo)
{
	return SetEdgeByIndex(LocateVex(v), LocateVex(w), pInfo);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdgeByIndex(int i, int j, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(i, j, pInfo, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdge(VertexType v, VertexType w, EdgeInfo& info)
{
	return GetEdgeByIndex(LocateVex(v), LocateVex(w), info);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdgeByIndex(int i, int j, EdgeInfo& info)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {

		EdgeNode<EdgeInfo>* p = m_szVex[i].firstarc;

		while (p)
		{
			if (p->adjvex == j) {
				info = p->info;
				return TRUE;
			}

			p = p->nextarc;
		}
	}

	return FALSE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdge(VertexType v, VertexType w)
{
	return ExistEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdgeByIndex(int i, int j)
{
    if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		EdgeNode<EdgeInfo>* p = m_szVex[i].firstarc;
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

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::LocateVex(const VertexType v)
{
    int i = 0;
	for (i; i < m_vexnum; ++i) {
		if (compare(m_szVex[i].val, v) == TRUE) {
			break;
		}
	}

    if (i == m_vexnum) {
        return -1;
    }

    return i;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVex(const VertexType v)
{
    return ExistVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}
	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVex(const VertexType v)
{
	return FirstAdjVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVexByIndex(int i)
{
	if (i >= 0 && i < m_vexnum) {
		EdgeNode<EdgeInfo>* p = m_szVex[i].firstarc;
		if (p != NULL) {
			return p->adjvex;
		}
	}

	return -1;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVex(const VertexType v, const VertexType w)
{
	return NextAdjVexByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVexByIndex(int i, int j)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		EdgeNode<EdgeInfo>* p = NULL;
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

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline void ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::PrintInfo()
{
	cout << "当前顶点已使用空间：" << m_vexnum << endl;
	cout << "当前边所使用的空间：" << m_arcnum << endl;

	// 打印顶点信息
	cout << "当前顶点信息如下：(共有 " << m_vexnum << " 个顶点)" << endl;
	for (int i = 0; i < m_vexnum; i++) {
		cout << "第 " << i + 1 << " 个顶点为：" << m_szVex[i].val << "\t顶点信息为：";
		if (m_szVex[i].valid == INVALID) {
			cout << "<--没有记录顶点信息-->";
		}
		else {
			cout << m_szVex[i].info;
		}
		cout << endl;
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
		EdgeNode<EdgeInfo>* p = m_szVex[i].firstarc;
		while (p) {
			if (m_graphKind == DG || m_graphKind == DN) {
				cout << "第 " << ++num << " 条边 <" << m_szVex[i].val << "," << m_szVex[p->adjvex].val << "> 的信息为: ";
			}
			else {
				cout << "第 " << ++num << " 条边 (" << m_szVex[i].val << "," << m_szVex[p->adjvex].val << ") 的信息为: ";
			}

			if (m_graphKind == UDN) {
				cout << "<--无向网没有权值信息-->" << endl;
			}
			else if (m_graphKind == DN) {
				cout << "<--有向网没有权值信息-->" << endl;
			}
			else {
				cout << p->info << endl;
			}

			p = p->nextarc;
		}
	}

	// 内存排布
	cout << "邻接表内存排列：" << endl;
	for (int i = 0; i < m_vexnum; i++) {
		cout << "[" << i << "]";
		EdgeNode<EdgeInfo>* p = m_szVex[i].firstarc;
		if (p == NULL) {
			cout << "->NULL";
		}
		else {
			while (p) {
				cout << "->" << p->adjvex;
				p = p->nextarc;
			}
		}
		cout << endl;
	}
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::deleteEdge(int i, int j)
{
	if (i < 0 || i > m_vexnum || j < 0 || j > m_vexnum) {
		return FALSE;
	}

	if (!ExistEdgeByIndex(i, j)) {
		return FALSE;
	}

	EdgeNode<EdgeInfo>* p = NULL;
	EdgeNode<EdgeInfo>* q = NULL;

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