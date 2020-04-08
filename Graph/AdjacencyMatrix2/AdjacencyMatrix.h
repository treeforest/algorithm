#ifndef __ADJACENCYMATRIX_H__
#define __ADJACENCYMATRIX_H__

#include "define.h"
#include <memory>

class MGraph
{
public:
	MGraph(GraphKind typ = UDG);
	virtual ~MGraph();

	// 在图G中插入顶点, 返回当前顶点的索引号; len: 顶点v所占用的空间大小
	virtual int InsertVex(const VexType v, size_t len);

	// 设置顶点信息. 如果顶点不存在，则返回FALSE；否则记录顶点信息
	// modify 字段: = TRUE,则当顶点信息存在时，就修改顶点信息；否则在顶点信息存在的情况下，直接返回 FALSE
	virtual BOOL SetVex(const VexType v, size_t vLen, const VexInfo info, size_t infoLen, BOOL modify = TRUE);
	virtual BOOL SetVexByIndex(int i, const VexInfo info, size_t infolen, BOOL modify = TRUE);
	
	// 获取顶点信息
	virtual VexInfo GetVex(const VexType v, size_t len);
	virtual VexInfo GetVexByIndex(int i);

	// 在图G中删除顶点
	virtual BOOL DeleteVex(const VexType v, size_t len);
	virtual BOOL DeleteVexByIndex(const int loc);

	// 若无向边(x, y)或有向边<x, y>不存在，则向图G中添加该边。
	// 如果 modify == true，则在存在 Edge 的情况下进行修改该边的弧信息；如果 modify 为 false，在边已经存在的请款下会返回 FALSE
	virtual BOOL InsertArc(const VexType v, size_t vlen, const VexType w, size_t wlen, ArcInfo info = NULL, size_t infolen = 0, BOOL modify = TRUE);
	virtual BOOL InsertArcByIndex(int i, int j, ArcInfo info = NULL, size_t infolen = 0, BOOL modify = TRUE);

	// 若无向边(x, y)或有向边<x, y>存在，则从图G中删除该边。若边不存在则返回 FALSE，设置成功返回 TRUE。
	virtual BOOL DeleteArc(const VexType v, size_t vlen, const VexType w, size_t wlen);
	virtual BOOL DeleteArcByIndex(int i, int j);

	// 求图G中顶点 x 的第一个邻接点。若有，则返回顶点号；若 x 没有邻接点或不存在 x，则返回-1。
	virtual int FirstAdjVex(const VexType v, size_t len);
	virtual int FirstAdjVexByIndex(int i);

	// 假设图G中顶点 y 是顶点 x 的一个邻接点，返回除 y 之外顶点 x 的下一个邻接点的顶点号；若 y 是 x 的最后一个邻接点，则返回 -1。
	virtual int NextAdjVex(const VexType v, size_t vlen, const VexType w, size_t wlen);
	virtual int NextAdjVexByIndex(int i, int j);

	// 获取图G中边(x, y)或<x, y>对应的权值。
	virtual ArcInfo GetArc(const VexType v, size_t vlen, const VexType w, size_t wlen);
	virtual ArcInfo GetArcByIndex(int i, int j);

	// 设置图G中边(x, y)或<x, y>对应的权值 value。若边不存在则返回 FALSE，设置成功返回 TRUE。
	virtual BOOL SetArc(const VexType v, size_t vlen, const VexType w, size_t wlen, ArcInfo info);
	virtual BOOL SetArcByIndex(int i, int j, ArcInfo info);

	// 若图中存在顶点 value,则返回该顶点在图中位置；否则返回-1
	virtual int LocateVex(const VexType v, size_t len);

	// 若图中存在顶点 value，则返回 TRUE，否则返回 FALSE
	virtual BOOL ExistVex(const VexType v, size_t len);
	virtual BOOL ExistVexByIndex(const int i);

	// 是否存在边（v, w）或 <v, w>
	virtual BOOL ExistArc(const VexType v, size_t vlen, const VexType w, size_t wlen);
	virtual BOOL ExistArcByIndex(int i, int j);

	// 获取索引为 i 的顶点信息
	virtual VexType GetVexVal(int i) const { return m_szVex[i].vex; }

	// 获取当前图的类型
	virtual GraphKind GetGraphKind() const { return m_graphKind; }

	// 获取当前顶点数量
	virtual int GetVexNum() const { return m_vexnum; }

	// 无向图中边的偏移地址
	virtual int ArcOffsetLoc(const VexType v, size_t vlen, const VexType w, size_t wlen);
	virtual int ArcOffsetLocByIndex(int i, int j);

	// 打印测试
	virtual void PrintInfo();

private:
	// 顶点表
	VNode m_szVex[MAX_VERTEX_NUM];
	
	// 有向图邻接矩阵
	ArcCell** m_pDArcs;

	// 无向图,采用上三角压缩存储
	ArcCell* m_pUDArcs;

	// 图的当前顶点数
	int m_vexnum;

	// 图的弧数
	int m_arcnum;

	// 图类型，有向图 或 无向图
	GraphKind m_graphKind;
};

#endif // !__ADJACENCYMATRIX_H__