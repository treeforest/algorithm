#include "AdjacencyMatrix.h"
#include <string>
#include <iostream>
using namespace std;


MGraph::MGraph(GraphKind kind)
{
	if (kind == DG || kind == DN) {

		// 创建有向图或有向网的邻接矩阵
		m_pDArcs = new ArcCell * [MAX_VERTEX_NUM]();
		for (int i = 0; i < MAX_VERTEX_NUM; i++) {
			m_pDArcs[i] = new ArcCell[MAX_VERTEX_NUM]();
		}
		m_pUDArcs = NULL;
	}
	else if (kind == UDG || kind == UDN) {

		// 创建无向图或无向网的下三角压缩矩阵
		int nUDSize = (1 + MAX_VERTEX_NUM) * MAX_VERTEX_NUM / 2;
		m_pUDArcs = new ArcCell[nUDSize]();
		m_pDArcs = NULL;
	}

	memset(m_szVex, 0, sizeof(VNode) * MAX_VERTEX_NUM);
	m_vexnum = 0;
	m_arcnum = 0;
	m_graphKind = kind;
}


MGraph::~MGraph()
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


int MGraph::InsertVex(const VexType v, size_t len)
{
	int loc = -1;

	do
	{
		if (len <= 0){
			break;
		}

		if (m_vexnum >= MAX_VERTEX_NUM) {
			break;
		}

		if (LocateVex(v, len) != -1) {
			break;
		}

		VNode node;
		node.vex = sdsnewlen(v, len);
		node.info = sdsempty();

		m_szVex[m_vexnum] = node;

		loc = ++m_vexnum;

	} while (0);

	return loc;
}


inline BOOL MGraph::SetVex(const VexType v, size_t vLen, const VexInfo info, size_t infoLen, BOOL modify /*=TRUE*/)
{
	return SetVexByIndex(LocateVex(v, vLen), info, infoLen, TRUE);
}


inline BOOL MGraph::SetVexByIndex(int i, const VexInfo info, size_t infoLen, BOOL modify /*=TRUE*/)
{
	BOOL bRet = FALSE;

	do 
	{
		if (i < 0 || i >= m_vexnum) {
			break;
		}

		if (infoLen <= 0) {
			break;
		}

		if (sdslen(m_szVex[i].info) != 0 && modify == FALSE) {
			break;
		}

		m_szVex[i].info = sdscpylen(m_szVex[i].info, info, infoLen);
		if (m_szVex[i].info == NULL) {
			// 扩展内存失败
			sdsfree(m_szVex[i].info);
			m_szVex[i].info = sdsempty();
			break;
		}

		bRet = TRUE;

	} while (0);

	return bRet;
}


inline VexInfo MGraph::GetVex(const VexType v, size_t len)
{
	return GetVexByIndex(LocateVex(v, len));
}


inline VexInfo MGraph::GetVexByIndex(int i)
{
	if (i >= 0 && i < m_vexnum) {
		return sdsdup(m_szVex[i].info);
	}

	return NULL;
}


BOOL MGraph::DeleteVex(const VexType v, size_t len)
{
	return DeleteVexByIndex(LocateVex(v, len));
}


inline BOOL MGraph::DeleteVexByIndex(const int loc)
{
	if (loc < 0 || loc >= m_vexnum) {
		return FALSE;
	}

	// 删除 m_szVex 中索引为 loc 的顶点
	sdsfree(m_szVex[loc].vex);
	sdsfree(m_szVex[loc].info);
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
					sdsfree(m_pDArcs[l][loc].info);
					--m_arcnum;
				}

				for (c = loc; c < m_vexnum - 1; ++c) {
					m_pDArcs[l][c] = m_pDArcs[l][c + 1];
				}
			}
			else if (l == loc) {

				for (c = 0; c < m_vexnum; ++c) {
					if (m_pDArcs[l][c].exist == EXIST) {
						sdsfree(m_pDArcs[l][c].info);
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
							sdsfree(m_pDArcs[l][c].info);
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
						sdsfree(m_pUDArcs[i].info);
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


BOOL MGraph::InsertArc(const VexType v, size_t vlen, const VexType w, size_t wlen, ArcInfo info /*= NULL*/, size_t infolen /*= 0*/, BOOL modify)
{
	return InsertArcByIndex(LocateVex(v, vlen), LocateVex(w, wlen), info, infolen, modify);
}


inline BOOL MGraph::InsertArcByIndex(int i, int j, ArcInfo info /*=NULL*/, size_t infolen /*= 0*/, BOOL modify)
{
	if (infolen <= 0) {
		return FALSE;
	}

	if (i < 0 || i >= m_vexnum || j < 0 || j >= m_vexnum) {
		return FALSE;
	}

	if (ExistArcByIndex(i, j) == TRUE && modify == FALSE) {
		return FALSE;
	}

	ArcCell node;
	memset(&node, 0, sizeof(ArcCell));
	node.exist = EXIST;
	node.info = sdsnewlen(info, infolen);

	if (m_graphKind == DG || m_graphKind == DN) {
		m_pDArcs[i][j] = node;
	}
	else if (m_graphKind == UDG || m_graphKind == UDN) {
		m_pUDArcs[ArcOffsetLocByIndex(i, j)] = node;
	}

	++m_arcnum;

	return TRUE;
}


BOOL MGraph::DeleteArc(const VexType v, size_t vlen, const VexType w, size_t wlen)
{
	return DeleteArcByIndex(LocateVex(v, vlen), LocateVex(w, wlen));
}


inline BOOL MGraph::DeleteArcByIndex(int i, int j)
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
				sdsfree((sds)(m_pDArcs[i][j].info));
				--m_arcnum;
				bRet = TRUE;
			}
		}
		else if (m_graphKind == UDG || m_graphKind == UDN) {

			int loc = ArcOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				m_pUDArcs[loc].exist = NOTEXIST;
				sdsfree((sds)(m_pUDArcs[loc].info));
				--m_arcnum;
				bRet = TRUE;
			}
		}
	} while (0);

	return bRet;
}


inline int MGraph::FirstAdjVex(const VexType v, size_t len)
{
	return FirstAdjVexByIndex(LocateVex(v, len));
}


int MGraph::FirstAdjVexByIndex(int i)
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


inline int MGraph::NextAdjVex(const VexType v, size_t vlen, const VexType w, size_t wlen)
{
	return NextAdjVexByIndex(LocateVex(v, vlen), LocateVex(w, wlen));
}


int MGraph::NextAdjVexByIndex(int i, int j)
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


ArcInfo MGraph::GetArc(const VexType v, size_t vlen, const VexType w, size_t wlen)
{
	return GetArcByIndex(LocateVex(v, vlen), LocateVex(w, wlen));
}


inline ArcInfo MGraph::GetArcByIndex(int i, int j)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {
		if (m_graphKind == DG || m_graphKind == DN) {

			if ((m_pDArcs[i][j]).exist == EXIST) {
				return sdsdup(m_pDArcs[i][j].info);
			}
		}
		else if (m_graphKind == UDG || m_graphKind == UDN) {

			int loc = ArcOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				return sdsdup(m_pUDArcs[loc].info);
			}
		}

	}

	return NULL;
}


BOOL MGraph::SetArc(const VexType v, size_t vlen, const VexType w, size_t wlen, ArcInfo info)
{
	return InsertArcByIndex(LocateVex(v, vlen), LocateVex(w, wlen), info, TRUE);
}


inline BOOL MGraph::SetArcByIndex(int i, int j, ArcInfo info)
{
	if (sdslen(info) == 0) {
		return FALSE;
	}

	return InsertArcByIndex(i, j, info, TRUE);
}


int MGraph::LocateVex(const VexType v, size_t len)
{
	if (len <= 0) {
		return -1;
	}

	for (int i = 0; i < m_vexnum; ++i) {
		if (sdscmpstr(m_szVex[i].vex, v, len) == 0) {
			return i;
		}
	}

	return -1;
}


BOOL MGraph::ExistVex(const VexType v, size_t len)
{
	return ExistVexByIndex(LocateVex(v, len));
}


inline BOOL MGraph::ExistVexByIndex(const int i)
{
	if (i < 0 || i > m_vexnum) {
		return FALSE;
	}

	return TRUE;
}


inline BOOL MGraph::ExistArc(const VexType v, size_t vlen, const VexType w, size_t wlen)
{
	return ExistArcByIndex(LocateVex(v, vlen), LocateVex(w, wlen));
}


inline BOOL MGraph::ExistArcByIndex(int i, int j)
{
	if (i >= 0 && i < m_vexnum && j >= 0 && j < m_vexnum) {

		if (m_graphKind == DG || m_graphKind == DN) {
			if ((m_pDArcs[i][j]).exist == EXIST) {
				return TRUE;
			}
		}
		else if (m_graphKind == UDG || m_graphKind == UDN) {

			int loc = ArcOffsetLocByIndex(i, j);
			if (m_pUDArcs[loc].exist == EXIST) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

inline int MGraph::ArcOffsetLoc(const VexType v, size_t vlen, const VexType w, size_t wlen)
{
	return ArcOffsetLocByIndex(LocateVex(v, vlen), LocateVex(w, wlen));
}


int MGraph::ArcOffsetLocByIndex(int i, int j)
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

void MGraph::PrintInfo()
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
		cout << "第 " << i + 1 << " 个顶点的值:" << string(m_szVex[i].vex, sdslen(m_szVex[i].vex)) << "   顶点的信息为:";
		if (0 != sdslen(m_szVex[i].info)) {
			cout << string(m_szVex[i].info, sdslen(m_szVex[i].info));
		}
		cout << endl;
	}

	// 打印边信息
	if (m_graphKind == DG || m_graphKind == DN) {
		cout << "当前有向边共有：" << m_arcnum << "条" << endl;
		int num = 0;
		for (int i = 0; i < m_vexnum; i++) {
			for (int j = 0; j < m_vexnum; j++) {
				if (m_pDArcs[i][j].exist == EXIST) {
					cout << "第 " << ++num << " 条边 <" << GetVexVal(i) << "," << GetVexVal(j) << "> 的信息为:" << m_pDArcs[i][j].info << endl;
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
				loc = ArcOffsetLocByIndex(i, j);
				if (m_pUDArcs[loc].exist == EXIST) {
					cout << "第 " << ++num << " 条边 (" << GetVexVal(i) << "," << GetVexVal(j) << ") 的信息为:" << m_pUDArcs[loc].info << endl;
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

		for (int i = 0; i < m_vexnum; i++) {
			cout << m_szVex[i].vex << " ";
		}
		cout << endl;

		for (j = 0; j < m_vexnum; j++) {
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

		for (int i = 0; i < m_vexnum; i++) {
			cout << m_szVex[i].vex << " ";
		}
		cout << endl;

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
			}
			else {
				j++;
			}
		}
	}
}


