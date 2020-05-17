#pragma once

/*
 * 森林节点定义
 */
template <typename Value>
struct FNode
{
	Value val;
	int rank;					// 代表 x 的高度
	FNode<Value>* p;			// 父节点
};

/*
 * 不相交集合的森林表示
 *
 * 模板参数
 *  Value: 集合中存放的值
 *  Compare: 用于比较 Value 之间是否大小的函数
 *    函数类型：int Compare(Value v1， Value v2);若 v1==v2，则返回 =0;若 v1<v2，则返回 <0;若 v1>v2，则返回 >0.
 */
template <typename Value>
class FSet
{
public:
	static void MakeSet(FNode<Value>* x);
	static void Union(FNode<Value>* x, FNode<Value>* y);
	static FNode<Value>* FindSet(FNode<Value>* x);

private:
	static void Link(FNode<Value>* x, FNode<Value>* y);
};

/*
 * 创建一个新集合，它的唯一成员是 x
 */
template<typename Value>
inline void FSet<Value>::MakeSet(FNode<Value>* x)
{
	x->p = x;
	x->rank = 0;
}

/*
 * 合并两个集合 x 与 y
 */
template<typename Value>
inline void FSet<Value>::Union(FNode<Value>* x, FNode<Value>* y)
{
	Link(FindSet(x), FindSet(y));
}

/*
 * 返回指向集合代表的指针
 */
template<typename Value>
inline FNode<Value>* FSet<Value>::FindSet(FNode<Value>* x)
{
	if (x != x->p) {
		x->p = FindSet(x->p);
	}
	return x->p;
}

template<typename Value>
inline void FSet<Value>::Link(FNode<Value>* x, FNode<Value>* y)
{
	if (x->rank > y->rank) {
		y->p = x;
	}
	else {
		x->p = y;
		if (x->rank == y->rank) {
			y->rank = y->rank + 1;
		}
	}
}
