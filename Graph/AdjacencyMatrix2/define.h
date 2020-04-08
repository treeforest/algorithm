#ifndef __DEFINE_H__
#define __DEFINE_H__
#include "sds.h"

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

typedef sds VexType;
typedef sds VexInfo;
typedef sds ArcInfo;

/*
 * 保存边节点对象的结构
*/
struct ArcCell
{
	// 该边存在 exist = EXIST; 不存在则 exist = NOTEXIST
	unsigned int exist : 1;

	// 该边的相关信息
	ArcInfo info;
};

/*
 * 保存顶点节点对象的结构
 */
struct VNode
{
	// 顶点值
	VexType vex;

	// 顶点信息
	VexInfo info;
};

#endif // !__DEFINE_H__
