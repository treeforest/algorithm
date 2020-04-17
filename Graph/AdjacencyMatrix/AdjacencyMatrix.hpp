#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include <memory.h>
#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 64

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

typedef int BOOL;
#define TRUE 1
#define FALSE 0

#define EXIST 0x1
#define NOTEXIST 0x0

#define VALID 0x1
#define INVALID 0x0

/*
 * 边表节点
 *
 * 成员变量
 *  info ：该边相关的信息
 *  exist ：该边是否存在 info 记录。EXIST：说明存在info信息；NOTEXIST说明不存在info信息
 */
template<typename EdgeInfo>
struct EdgeNode
{
	unsigned int exist : 1;
	EdgeInfo info;
};

/*
 * 顶点节点
 *
 * 成员变量
 *  val ：顶点值
 *  info ：顶点信息
 *  valid ：该边是否存在 info 记录。VALID：说明存在info信息；INVALID说明不存在info信息
 */
template<typename VertexType, typename VertexInfo>
struct VNode
{
	VertexType val;
	VertexInfo info;
	unsigned int valid : 1;
};

/*
 * 邻接矩阵存储结构
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
class MGraph
{
public:
	MGraph(CompareFunc func, GraphKind typ = UDG);
	virtual ~MGraph();

	virtual int InsertVex(const VertexType& v);

	virtual BOOL SetVex(const VertexType& v, const VertexInfo& info, BOOL modify = TRUE);
	virtual BOOL SetVexByIndex(int i, const VertexInfo& info, BOOL modify = TRUE);
	
	virtual BOOL GetVex(const VertexType& v, VertexInfo& info);
	virtual BOOL GetVexByIndex(int i, VertexInfo& info);

	virtual BOOL DeleteVex(const VertexType& v);
	virtual BOOL DeleteVexByIndex(const int loc);

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

	virtual int FirstAdjVex(const VertexType& v);
	virtual int FirstAdjVexByIndex(int i);

	virtual int NextAdjVex(const VertexType& v, const VertexType& w);
	virtual int NextAdjVexByIndex(int i, int j);

	virtual int LocateVex(const VertexType& v);

	virtual BOOL ExistVex(const VertexType& v);
	virtual BOOL ExistVexByIndex(const int i);

	virtual VertexType GetVexVal(int i) const;
	virtual GraphKind GetGraphKind() const;
	virtual int GetVexNum() const;

	// 打印测试
	virtual void PrintInfo();

private:
	// 屏蔽默认构造函数
	MGraph() {}

	virtual int EdgeOffsetLoc(const VertexType& v, const VertexType& w);
	virtual int EdgeOffsetLocByIndex(int i, int j);

private:
	VNode<VertexType, VertexInfo> m_szVex[MAX_VERTEX_NUM];// 顶点表
	EdgeNode<EdgeInfo>** m_pDArcs;// 有向图邻接矩阵 
	EdgeNode<EdgeInfo>* m_pUDArcs;// 无向图,采用上三角压缩存储
	int m_vexnum;// 图的当前顶点数
	int m_arcnum;// 图的弧数
	GraphKind m_graphKind;// 图类型，有向图 或 无向图
	CompareFunc compare;// 顶点的比较函数
};

/*
 * 构造函数
 *
 * 参数
 *  func ：顶点值比较函数指针
 *  kind ：图类型。默认为无向图 UDG
 */
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

/*
 * 析构函数
 */
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
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertVex(const VertexType& v)
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
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVex(const VertexType& v, const VertexInfo& info, BOOL modify /*=TRUE*/)
{
	return SetVexByIndex(LocateVex(v), info, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetVexByIndex(int i, const VertexInfo& info, BOOL modify /*=TRUE*/)
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
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVex(const VertexType& v, VertexInfo& info)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteVex(const VertexType& v)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::InsertEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo /*=NULL*/, BOOL modify)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::DeleteEdge(const VertexType& v, const VertexType& w)
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
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::FirstAdjVex(const VertexType& v)
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
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::NextAdjVex(const VertexType& v, const VertexType& w)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetEdge(const VertexType& v, const VertexType& w, EdgeInfo& info)
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdge(const VertexType& v, const VertexType& w, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(LocateVex(v), LocateVex(w), pInfo, TRUE);
}

template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::SetEdgeByIndex(int i, int j, EdgeInfo* pInfo)
{
	return InsertEdgeByIndex(i, j, pInfo, TRUE);
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
int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::LocateVex(const VertexType& v)
{
	for (int i = 0; i < m_vexnum; ++i) {

		if (TRUE == compare(m_szVex[i].val, v)) {
			return i;
		}
	}

	return -1;
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
BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistVex(const VertexType& v)
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

/*
 * 获取索引为 i 的顶点信息
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline VertexType MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexVal(int i) const
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
inline GraphKind MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetGraphKind() const
{
	return m_graphKind;
}

/*
 * 获取当前顶点数量
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::GetVexNum() const
{
	return m_vexnum;
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
inline BOOL MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::ExistEdge(const VertexType& v, const VertexType& w)
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

/*
 * 无向图中边的偏移地址
 */
template<typename VertexType, typename VertexInfo, typename EdgeInfo, typename CompareFunc>
inline int MGraph<VertexType, VertexInfo, EdgeInfo, CompareFunc>::EdgeOffsetLoc(const VertexType& v, const VertexType& w)
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