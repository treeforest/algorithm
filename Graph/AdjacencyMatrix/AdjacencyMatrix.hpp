#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include <memory.h>
#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 64

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

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define EXIST 0x1
#define NOTEXIST 0x0

#define VALID 0x1
#define INVALID 0x0

/*
 * 边表节点
*/
template<typename EdgeInfo>
struct EdgeNode
{
	// 该边存在 exist = EXIST; 不存在则 exist = NOTEXIST
	// 若图为 DG/UDG,则在边存在的情况下，info不为空。反之为 DN/UDN 不存在权值
	unsigned int exist : 1;

	// 该边的相关信息
	EdgeInfo info;
};

/*
 * 顶点节点
 */
template<typename VertexType, typename VertexInfo>
struct VNode
{
	// 顶点值
	VertexType val;

	// 顶点信息
	VertexInfo info;

	// info 有记录时 valid = VALID; 没记录 valid = INVALID
	unsigned int valid : 1;
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

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
class MGraph
{
public:
	MGraph(CompareFunc func, GraphKind typ = UDG);
	virtual ~MGraph();

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
	virtual BOOL DeleteVexByIndex(const int loc);

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

	// 求图G中顶点 x 的第一个邻接点。若有，则返回顶点号；若 x 没有邻接点或不存在 x，则返回-1。
	virtual int FirstAdjVex(VertexType v);
	virtual int FirstAdjVexByIndex(int i);

	// 假设图G中顶点 y 是顶点 x 的一个邻接点，返回除 y 之外顶点 x 的下一个邻接点的顶点号；若 y 是 x 的最后一个邻接点，则返回 -1。
	virtual int NextAdjVex(VertexType v, VertexType w);
	virtual int NextAdjVexByIndex(int i, int j);

	// 若图中存在顶点 value,则返回该顶点在图中位置；否则返回-1
	virtual int LocateVex(const VertexType v);

	// 若图中存在顶点 value，则返回 TRUE，否则返回 FALSE
	virtual BOOL ExistVex(const VertexType v);
	virtual BOOL ExistVexByIndex(const int i);

	// 获取索引为 i 的顶点信息
	virtual VertexType GetVexVal(int i) const { return m_szVex[i].val; }

	// 获取当前图的类型
	virtual GraphKind GetGraphKind() const { return m_graphKind; }

	// 获取当前顶点数量
	virtual int GetVexNum() const { return m_vexnum; }

	// 打印测试
	virtual void PrintInfo();

private:
	// 屏蔽默认构造函数
	MGraph() {}

	// 无向图中边的偏移地址
	virtual int EdgeOffsetLoc(VertexType v, VertexType w);
	virtual int EdgeOffsetLocByIndex(int i, int j);

private:
	// 顶点表
	VNode<VertexType, VertexInfo> m_szVex[MAX_VERTEX_NUM];
	
	// 有向图邻接矩阵
	EdgeNode<EdgeInfo>** m_pDArcs;

	// 无向图,采用上三角压缩存储
	EdgeNode<EdgeInfo>* m_pUDArcs;

	// 图的当前顶点数
	int m_vexnum;

	// 图的弧数
	int m_arcnum;

	// 图类型，有向图 或 无向图
	GraphKind m_graphKind;

	// 顶点的比较函数
	CompareFunc compare;
};


template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::MGraph(CompareFunc func, GraphKind kind)
{
	if (kind == DG || kind == DN) {

		// 创建有向图或有向网的邻接矩阵
		m_pDArcs = new EdgeNode<EdgeInfo> * [MAX_VERTEX_NUM]();
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			m_pDArcs[i] = new EdgeNode<EdgeInfo>[MAX_VERTEX_NUM]();
		}
		m_pUDArcs = NULL;
	}
	else if(kind == UDG || kind == UDN){

		// 创建无向图或无向网的下三角压缩矩阵
		int nUDSize = (1 + MAX_VERTEX_NUM) * MAX_VERTEX_NUM / 2;
		m_pUDArcs = new EdgeNode<EdgeInfo>[nUDSize]();
		m_pDArcs = NULL;
	}

	//memset(m_szVex, 0, sizeof(VNode<VertexType, VertexInfo>) * MAX_VERTEX_NUM);
	m_vexnum = 0;
	m_arcnum = 0;
	m_graphKind = kind;

	compare = func;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::~MGraph()
{
	if (m_pDArcs) {
		delete[] m_pDArcs;
		m_pDArcs = NULL;
	}

	if (m_pUDArcs) {
		delete[] m_pUDArcs;
		m_pUDArcs = NULL;
	}
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertVex(const VertexType v)
{
	int loc = -1;

	do 
	{
		if (m_vexnum >= MAX_VERTEX_NUM) {
			break;
		}

		if (LocateVex(v) != -1) {
			break;
		}

		VNode<VertexType, VertexInfo> node;
		node.val = v;
		node.valid = INVALID;
		
		m_szVex[m_vexnum] = node;
		
		loc = m_vexnum++;

	} while (0);

	return loc;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVex(const VertexType v, const VertexInfo info, BOOL modify /*=TRUE*/)
{
	return SetVexByIndex(LocateVex(v), info, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVexByIndex(int i, const VertexInfo info, BOOL modify /*=TRUE*/)
{
	if (i < 0 || i >= m_vexnum) {
		return FALSE;
	}

	if (m_szVex[i].valid == VALID && modify == FALSE){
		return FALSE;
	}

	m_szVex[i].info = info;
	m_szVex[i].valid = VALID;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVex(const VertexType v, VertexInfo& info)
{
	return GetVexByIndex(LocateVex(v), info);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexByIndex(int i, VertexInfo& info)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVex(const VertexType v)
{
	return DeleteVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVexByIndex(const int loc)
{
	if (loc < 0 || loc >= m_vexnum) {
		return FALSE;
	}

	// 删除 m_szVex 中索引为 loc 的顶点
	for (int j = loc; j < m_vexnum; ++j) {
		m_szVex[j] = m_szVex[j + 1];
	}

	int l; // 行
	int c; // 列
	// 删除图中索引为 loc 的顶点所相关的边
	/*
	若为有向图

		 例如：删除如下图中索引为2的顶点
		   0 1 2 3 4
		 0 0 1 1 0 1
		 1 1 0 0 0 0
		 2 1 1 0 1 0
		 3 1 1 0 0 0
		 4 0 0 1 1 0

		 删除后的结果（*即为需要删除的位置）： loc = 2
		   0 1 2 3 4
		 0 0 1 * 0 1 // l < loc
		 1 1 0 * 0 0
		 2 * * * * * // l == loc
		 3 1 1 * 0 0 // l > loc
		 4 0 0 * 1 0
	*/
	if (m_graphKind == DG || m_graphKind == DN) {
		for (l = 0; l < m_vexnum; ++l) {
			if (l < loc) {

				if (m_pDArcs[l][loc].exist == EXIST) {
					--m_arcnum;
				}

				for (c = loc; c < m_vexnum - 1; ++c) {
					m_pDArcs[l][c] = m_pDArcs[l][c + 1];
				}
			}
			else if (l == loc) {

				for (c = 0; c < m_vexnum; ++c) {
					if (m_pDArcs[l][c].exist == EXIST) {
						--m_arcnum;
					}
				}

				continue;
			}
			else if (l > loc) {

				for (c = 0; c < m_vexnum; ++c) {
					if (c < loc) {
						m_pDArcs[l - 1][c] = m_pDArcs[l][c];
					}
					else if (c == loc) {
						if (m_pDArcs[l][c].exist == EXIST) {
							--m_arcnum;
						}
					}
					else {
						m_pDArcs[l - 1][c - 1] = m_pDArcs[l][c];
					}
				}
			}
		}
	}
	/*
	若为无向图（压缩的上三角矩阵）

			 0 ----- 1
			 | \     |
			 2  4    |
			 |   \  /
			 |____3

		 例如：删除如下图中索引为 2 的顶点
		   0 1 2 3 4
		 0 0
		 1 1 0
		 2 1 0 0
		 3 0 1 1 0
		 4 1 0 0 1 0

		 删除后的结果（*即为需要删除的位置）：
		   0 1 2 3 4
		 0 0
		 1 1 0
		 2 * * *
		 3 0 1 * 0
		 4 1 0 * 1 0
	*/
	else if (m_graphKind == UDG || m_graphKind == UDN) {

		if (loc == m_vexnum - 1) {
			// 最后一行，不用做任何操作
		}
		else {
			int usedSpace = (m_vexnum + 1) * m_vexnum / 2;// 已经使用的空间
			int index = 0;// 待移动元素的索引 
			int delCnt = 0;// 已删除的元素个数
			int toDelNum = 0;// 待删除个数

			for (l = loc; l < m_vexnum; ++l) {
				index = (1 + l) * l / 2 + (loc + 1) - delCnt;

				if (l == loc) {
					toDelNum = loc + 1;
				}
				else if (l > loc) {
					toDelNum = 1;
				}

				// 更新当前边的数量
				for (int i = index - toDelNum; i < index; i++) {
					if (m_pUDArcs[i].exist == EXIST) {
						--m_arcnum;
					}
				}

				// move elements
				for (int i = index; i < usedSpace; ++i) {
					m_pUDArcs[i - toDelNum] = m_pUDArcs[i];
				}

				delCnt = delCnt + toDelNum;
				usedSpace = usedSpace - toDelNum;
			}
		}
	}

	--m_vexnum;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdge(VertexType v, VertexType w, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
{
	return InsertEdgeByIndex(LocateVex(v), LocateVex(w), pInfo, modify);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdgeByIndex(int i, int j, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
{
	if (i < 0 || i >= m_vexnum || j < 0 || j >= m_vexnum) {
		return FALSE;
	}

	BOOL exist = ExistEdgeByIndex(i, j);
	EdgeNode<EdgeInfo> node;

	// 有向网 或 无向网
	if (m_graphKind == DN || m_graphKind == UDN) {
		
		if (exist == TRUE) {
			return TRUE;
		}
		
		node.exist = EXIST;
	}
	// 有向图 或 无向图
	else {
		
		if ((exist == TRUE && modify == FALSE) || pInfo == NULL) {
			return FALSE;
		}

		node.exist = EXIST;
		node.info = *pInfo;
	}

	if (m_graphKind == DG || m_graphKind == DN) {
		m_pDArcs[i][j] = node;
	}
	else if (m_graphKind == UDG || m_graphKind == UDN) {
		m_pUDArcs[EdgeOffsetLocByIndex(i, j)] = node;
	}

	++m_arcnum;

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdge(VertexType v, VertexType w)
{
	return DeleteEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdgeByIndex(int i, int j)
{
	BOOL bRet = FALSE;

	do 
	{
		if (i < 0 || i >= m_vexnum || j < 0 || j >= m_vexnum) {
			break;
		}

		if (m_graphKind == DG || m_graphKind == DN) {

			if (m_pDArcs[i][j].exist == EXIST) {
				m_pDArcs[i][j].exist = NOTEXIST;
				--m_arcnum;
				bRet = TRUE;
			}
		}
		else if (m_graphKind == UDG || m_graphKind == UDN) {

			int loc = EdgeOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				m_pUDArcs[loc].exist = NOTEXIST;
				--m_arcnum;
				bRet = TRUE;
			}
		}
	} while (0);

	return bRet;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVex(VertexType v)
{
	return FirstAdjVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVexByIndex(int i)
{
	if (i < 0 || i >= m_vexnum) {
		return -1;
	}

	int k = 0;// 返回的顶点索引值

	if (m_graphKind == DG || m_graphKind == DN) {

		// 不考虑环
		for (k = 0; (m_pDArcs[i][k]).exist == NOTEXIST && k < m_vexnum; ++k);

		if (k < m_vexnum) {
			return k;
		}
	}
	/*
		无向图的邻接顶点检索示意图(下三角)：
			  a b c d e

			  0 1 2 3 4
		a	0 0
		b	1 1 0
		c	2 * * *
		d	3 0 1 + 0
		e	4 1 0 + 1 0

	*/
	else if (m_graphKind == UDG || m_graphKind == UDN) {

		// 检索上述 * 号位置 
		for (k = 0; m_pUDArcs[(i + 1) * i / 2 + k].exist == NOTEXIST && k < i; ++k);

		if (k < i) {
			return k;
		}

		// 检索上述 + 号位置
		for (k = i + 1; m_pUDArcs[(k + 1) * k / 2 + i].exist == NOTEXIST && k < m_vexnum; k++);

		if (k < m_vexnum) {
			return k;
		}
	}

	return -1;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVex(VertexType v, VertexType w)
{
	return NextAdjVexByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVexByIndex(int i, int j)
{
	if (i >= m_vexnum || i < 0 || j >= m_vexnum || j < 0) {
		return -1;
	}

	int k = 0;

	if (m_graphKind == DG || m_graphKind == DN) {

		for (k = j + 1; (m_pDArcs[i][k]).exist == NOTEXIST && k < m_vexnum; ++k);

		if (k < m_vexnum) {
			return k;
		}
	} 
	else if (m_graphKind == UDG || m_graphKind == UDN) {

		k = j + 1;

		if (k < i) {

			for (k; m_pUDArcs[(i + 1) * i / 2 + k].exist == NOTEXIST && k < i; ++k);

			if (k < i) {
				return k;
			}

			for (k = i + 1; m_pUDArcs[(k + 1) * k / 2 + i].exist == NOTEXIST && k < m_vexnum; k++);

			if (k < m_vexnum) {
				return k;
			}
		}
		else {

			for (k; m_pUDArcs[(k + 1) * k / 2 + i].exist == NOTEXIST && k < m_vexnum; k++);

			if (k < m_vexnum) {
				return k;
			}
		}
	}

	return -1;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdge(VertexType v, VertexType w, EdgeInfo& info)
{
	return GetEdgeByIndex(LocateVex(v), LocateVex(w), info);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdgeByIndex(int i, int j, EdgeInfo& info)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {

		if (m_graphKind == DG) {

			if ((m_pDArcs[i][j]).exist == EXIST) {
				info = m_pDArcs[i][j].info;
				return TRUE;
			}
		}
		else if (m_graphKind == UDG) {

			int loc = EdgeOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				info = m_pUDArcs[loc].info;
				return TRUE;
			}
		}
		// m_graphKind == DN || m_graphKind == UDN
		else {
			// DN 与 UDN 不存在权值信息
		}
	}
	
	return FALSE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdge(VertexType v, VertexType w, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(LocateVex(v), LocateVex(w), pInfo, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdgeByIndex(int i, int j, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(i, j, pInfo, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::LocateVex(const VertexType v)
{
	for (int i = 0; i < m_vexnum; ++i) {

		if (TRUE == compare(m_szVex[i].val, v)) {
			return i;
		}
	}

	return -1;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVex(const VertexType v)
{
	return ExistVexByIndex(LocateVex(v));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}

	return TRUE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdge(VertexType v, VertexType w)
{
	return ExistEdgeByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdgeByIndex(int i, int j)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {

		if (m_graphKind == DG || m_graphKind == DN) {
			if ((m_pDArcs[i][j]).exist == EXIST) {
				return TRUE;
			}
		}
		else if (m_graphKind == UDG || m_graphKind == UDN) {

			int loc = EdgeOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
void MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::PrintInfo()
{
	cout << "当前顶点已使用空间：" << m_vexnum << endl;
	cout << "当前边所使用的空间：";
	if (m_graphKind == DG || m_graphKind == DN) {
		cout << m_vexnum * m_vexnum << endl;
	}
	else {
		cout << (1 + m_vexnum) * m_vexnum / 2 << endl;
	}

	// 打印顶点信息
	cout << "当前顶点信息如下：(共有 " << m_vexnum << " 个顶点)" << endl;
	for (int i = 0; i < m_vexnum; i++) {
		cout << "第 " << i + 1 << " 个顶点的值:" << m_szVex[i].val << "   顶点的信息为:";
		if (m_szVex[i].valid == VALID) {
			cout << m_szVex[i].info << endl;
		}
		else {
			cout << "<当前没有记录顶点信息>" << endl;
		}
	}

	// 打印边信息
	if (m_graphKind == DG || m_graphKind == DN) {
		cout << "当前有向边共有：" << m_arcnum << "条" << endl;
		int num = 0;
		for (int i = 0; i < m_vexnum; i++) {
			for (int j = 0; j < m_vexnum; j++) {
				if (m_pDArcs[i][j].exist == EXIST) {
					cout << "第 " << ++num << " 条边 <" << GetVexVal(i) << "," << GetVexVal(j) << "> 的信息为:";
					if (m_graphKind == DG){
						cout << m_pDArcs[i][j].info;
					}
					else {
						cout << "<有向网没有权值信息>";
					}
					cout << endl;
				}
			}
		}
	}
	else {
		cout << "当前无向边共有：" << m_arcnum * 2 << "条" << endl;
		int num = 0;
		int loc = 0;
		for (int i = 0; i < m_vexnum; i++) {
			for (int j = 0; j < m_vexnum; j++) {
				loc = EdgeOffsetLocByIndex(i, j);
				if (m_pUDArcs[loc].exist == EXIST) {
					cout << "第 " << ++num << " 条边 (" << GetVexVal(i) << "," << GetVexVal(j) << ") 的信息为:";
					if (m_graphKind == UDG) {
						cout << m_pUDArcs[loc].info;
					}
					else {
						cout << "<无向网没有权值信息>";
					}
					cout << endl;
				}

			}
		}
	}

	// 打印有向图与无向图的存储结构
	cout << endl;
	int n = 0;
	int j = 0;

	if (m_graphKind == DG || m_graphKind == DN) {
		cout << "有向图矩阵存储内存排列（1：有边；0：无边）：" << endl;

		cout << "  ";
		for (int i = 0; i < m_vexnum; i++) {
			cout << m_szVex[i].val << " ";
		}
		cout << endl;

		for (j = 0; j < m_vexnum; j++) {
			cout << m_szVex[j].val << " ";
			for (int i = 0; i < m_vexnum; ++i) {
				if (m_pDArcs[j][i].exist == EXIST) {
					cout << "1 ";
				}
				else {
					cout << "0 ";
				}
			}
			cout << endl;
		}
			
	}
	else {
		n = 0;
		j = 0;

		cout << "无向图 下三角压缩存储内存排列（1：有边；0：无边）：" << endl;
		if (m_vexnum == 0) { 
			return;
		}

		cout << "  ";
		for (int i = 0; i < m_vexnum; i++) {
			cout << m_szVex[i].val << " ";
		}
		cout << endl;

		cout << m_szVex[n].val << " ";
		for (int i = 0; i < (1 + m_vexnum) * m_vexnum / 2; i++) {

			if (m_pUDArcs[i].exist == EXIST) {
				cout << "1 ";
			}
			else {
				cout << "0 ";
			}

			if (n == j) {
				n++;
				j = 0;
				cout << endl;
				cout << m_szVex[n].val << " ";
			}
			else {
				j++;
			}
		}
	}
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::EdgeOffsetLoc(VertexType v, VertexType w)
{
	return EdgeOffsetLocByIndex(LocateVex(v), LocateVex(w));
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::EdgeOffsetLocByIndex(int i, int j)
{
	int loc = -1;

	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		if (j > i) {
			loc = (j + 1) * j / 2 + i;
		}
		else {
			loc = (i + 1) * i / 2 + j;
		}
	}

	return loc;
}

#endif // !__ADJACENCYMATRIX_H__