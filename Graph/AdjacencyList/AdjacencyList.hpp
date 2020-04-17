#ifndef __ADJACENCYLIST_H__
#define __ADJACENCYLIST_H__

#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 64

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define EXIST 0x1
#define NOTEXIST 0x0

#define VALID 0x1
#define INVALID 0x0

/*
 * 图的种类类型
 *
 * 类型
 *  DG ：有向图（带权值）
 *  DN ：有向网
 *  UDG ：无向图（带权值）
 *  UDN ：无向网
 */
enum GraphKind {
	DG,
	DN,
	UDG,
	UDN,
};


/*
 * 边表节点
 *
 * 成员变量
 *  adjvex ：该边所指向的顶点的位置
 *  info ：该边相关的信息
 *  valid ：该边是否存在 info 记录。VALID：说明存在info信息；INVALID说明不存在info信息
 *  nextarc ：指向下一条边的指针
 */
template<typename EdgeInfo>
struct EdgeNode
{
    int adjvex;
    EdgeInfo info;
    unsigned int valid : 1;
    struct EdgeNode<EdgeInfo>* nextarc;
};

/*
 * 顶点节点
 *
 * 成员变量
 *  val ：顶点值
 *  info ：顶点信息
 *  valid ：该边是否存在 info 记录。VALID：说明存在info信息；INVALID说明不存在info信息
 *  firstarc ：指向第一条依附该顶点的弧的指针
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo>
struct VNode 
{
    VertexType val;
	VertexInfo info;
	unsigned int valid : 1;
	EdgeNode<EdgeInfo>* firstarc;
};

/*
 * 邻接表存储结构
 *
 * 模板参数
 *  VertexType ：顶点值类型
 *  VertexInfo ：顶点信息类型
 *  EdgeInfo ：边信息类型
 *  CompareFunc: 比较顶点值的函数指针
 *               函数格式： BOOL FunctionName(VertexType v, VertexType w);
 *               要求：顶点值v、w相同返回TRUE，否则返回FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
class ALGraph 
{
public:
    ALGraph(CompareFunc func, GraphKind kind = DG);
    virtual ~ALGraph();

	virtual int InsertVex(const VertexType& v);

	virtual BOOL SetVex(const VertexType& v, const VertexInfo& info, BOOL modify = TRUE);
	virtual BOOL SetVexByIndex(int i, const VertexInfo& info, BOOL modify = TRUE);

	virtual BOOL GetVex(const VertexType& v, VertexInfo& info);
	virtual BOOL GetVexByIndex(int i, VertexInfo& info);

	virtual BOOL DeleteVex(const VertexType& v);
	virtual BOOL DeleteVexByIndex(int i);

	virtual BOOL InsertEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo = NULL, BOOL modify = TRUE);
	virtual BOOL InsertEdgeByIndex(int i, int j, EdgeInfo* pInfo = NULL, BOOL modify = TRUE);

	virtual BOOL DeleteEdge(const VertexType& v, const VertexType& w);
	virtual BOOL DeleteEdgeByIndex(int i, int j);

	virtual BOOL SetEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo);
	virtual BOOL SetEdgeByIndex(int i, int j, EdgeInfo* pInfo);

	virtual BOOL GetEdge(const VertexType& v, const VertexType& w, EdgeInfo& info);
	virtual BOOL GetEdgeByIndex(int i, int j, EdgeInfo& info);

    virtual BOOL ExistEdge(const VertexType& v, const VertexType& w);
    virtual BOOL ExistEdgeByIndex(int i, int j);

	virtual int LocateVex(const VertexType& v);

	virtual BOOL ExistVex(const VertexType& v);
	virtual BOOL ExistVexByIndex(int i);

	virtual int FirstAdjVex(const VertexType& v);
	virtual int FirstAdjVexByIndex(int i);

	virtual int NextAdjVex(const VertexType& v, const VertexType& w);
	virtual int NextAdjVexByIndex(int i, int j);

	virtual VertexType GetVexVal(int i) const;
	virtual GraphKind GetGraphKind() const;
	virtual int GetVexNum() const;
	virtual const VNode<VertexType, VertexInfo, EdgeInfo>* GetAdjList() const;

	// 测试输出
	void PrintInfo();

private:
	// 屏蔽默认构造函数
	ALGraph() {}
	BOOL deleteEdge(int i, int j);

private:
    VNode<VertexType, VertexInfo, EdgeInfo> m_szVex[MAX_VERTEX_NUM];// 邻接表
    int m_vexnum;// 图当前的顶点数
    int m_arcnum;// 图当前的弧数
    GraphKind m_graphKind;// 图的种类标志
	CompareFunc compare;// 顶点的比较函数
};

/*
 * 构造函数
 *
 * 参数
 *  func ：顶点值比较函数指针
 *  kind ：图类型。默认为有向图 DG
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ALGraph(CompareFunc func, GraphKind kind /*= DG*/)
{
    //memset(m_szVex, 0, sizeof(VNode<VexType, EdgeType>) * MAX_VERTEX_NUM);
    m_arcnum = 0;
    m_vexnum = 0;
    m_graphKind = kind;
	compare = func;
}

/*
 * 析构函数
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::~ALGraph()
{
}

/*
 * 在图中插入一个顶点
 *
 * 参数
 *  v ：插入的顶点值
 *
 * 返回值
 *  int ：如果不存在该顶点值，则插入成功，并返回插入的下标
 *        如果存在该顶点值，返回 -1
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertVex(const VertexType& v)
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

/*
 * 设置顶点的信息
 *
 * 参数
 *  v ：顶点的值
 *  info ：设置的顶点信息
 *  modify ：如果为 TRUE，则当顶点信息存在时，依旧修改顶点信息；
 *           如果为 FALSE，则顶点信息存在时，就不修改顶点信息
 *
 * 返回值
 *  BOOL ：插入/更改值成功，返回TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVex(const VertexType& v, const VertexInfo& info, BOOL modify)
{
	return SetVexByIndex(LocateVex(v), info, modify);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVexByIndex(int i, const VertexInfo& info, BOOL modify)
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

/*
 * 获取图中某一顶点的顶点信息
 *
 * 参数
 *  v ：顶点值
 *  info ：获取的顶点信息。
 *
 * 返回值
 *  BOOL ：如果存在顶点值 v 的顶点信息，则返回 TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVex(const VertexType& v, VertexInfo& info)
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

/*
 * 在图中删除顶点值
 *
 * 参数
 *  v ：删除的顶点的值
 *
 * 返回值
 *  BOOL ：如果存在该顶点值 v，则删除成功，返回 TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVex(const VertexType& v)
{
	return DeleteVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVexByIndex(int i)
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

/*
 * 在图中插入一条边
 *
 * 参数
 *  v，w ：插入边的两个顶点。如果是有向边，则该边为 <v, w>;如果为无向边，则该边为 (v, w)
 *  pInfo ：插入的边的边信息指针
 *  modify ：若为 TRUE，则在边存在的情况下修改该边的信息；若为 FALSE，则在边存在的情况下插入失败
 *
 * 返回值
 *  BOOL ：边插入成功返回 TRUE；插入失败返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
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

/*
 * 在图中删除边
 *
 * 参数
 *  v，w ：删除的边的顶点值。若为无向图，则删除的边为(v, w)；若为有向边，则删除的边为<v, w>
 *
 * 返回值
 *  BOOL ：删除成功返回TRUE；失败返回FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdge(const VertexType& v, const VertexType& w)
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

/*
 * 设置边的信息
 *
 * 参数
 *  v, w ：边的两个顶点。若为无向边，则为(v, w);若为有向边，则为<v, w>
 *  pInfo ：边信息指针，若为NULL，则插入失败
 *
 * 返回值
 *  BOOL ：插入成功，则返回TRUE；否则返回FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo)
{
	return SetEdgeByIndex(LocateVex(v), LocateVex(w), pInfo);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdgeByIndex(int i, int j, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(i, j, pInfo, TRUE);
}

/*
 * 获取边信息
 *
 * 参数
 *  v, w ：边的两个顶点。若为无向边，则为(v, w);若为有向边，则为<v, w>
 *  info ：接收获取的边信息
 *
 * 返回值
 *  BOOL ：若存在边以及对应的边信息，则返回 TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdge(const VertexType& v, const VertexType& w, EdgeInfo& info)
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

/*
 * 是否存在边
 * 
 * 参数
 *  v, w ：边的两个顶点。若为无向边，则为(v, w);若为有向边，则为<v, w>
 *
 * 返回值
 *  BOOL ：如果存在边，则返回 TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdge(const VertexType& v, const VertexType& w)
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

/*
 * 获取顶点的索引位置
 *
 * 参数
 *  v ：顶点值
 * 
 * 返回值
 *  int ：若存在该顶点，则返回顶点所在的索引；若不存在，则返回 -1
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::LocateVex(const VertexType& v)
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

/*
 * 是否存在顶点
 *
 * 参数
 *  v ：顶点值
 *
 * 返回值
 *  BOOL ：若存在该顶点，则返回 TRUE；否则返回 FALSE
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVex(const VertexType& v)
{
    return ExistVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVexByIndex(int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}
	return TRUE;
}

/*
 * 求顶点 v 的第一个邻接点的索引值
 *
 * 参数
 *  v ：顶点值
 *
 * 返回值
 *  int ：第一个邻接点的索引值；若不存在邻接点，则返回 -1
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVex(const VertexType& v)
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

/*
 * 求顶点 v 的邻接顶点 w 的下一个邻接顶点的索引
 *
 * 参数
 *  v ：顶点值
 *  w ：顶点值
 *
 * 返回值
 *  int ：第一个邻接点的索引值；若不存在邻接点，则返回 -1
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVex(const VertexType& v, const VertexType& w)
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

/*
 * 获取索引为 i 的顶点信息
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline VertexType ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexVal(int i) const
{
	if (i < 0 || i >= m_vexnum) {
		throw "out of range";
	}
	return m_szVex[i].val;
}

/*
 * 获取当前图的类型
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline GraphKind ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetGraphKind() const
{
	return m_graphKind;
}

/*
 * 获取当前顶点数量
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexNum() const
{
	return m_vexnum;
}

/*
 * 	获取邻接表。
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline const VNode<VertexType, VertexInfo, EdgeInfo>* ALGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetAdjList() const
{
	return m_szVex;
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