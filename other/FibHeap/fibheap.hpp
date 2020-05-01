#pragma once

/* 
 * 斐波那契堆结点定义
 * 
 * 成员变量
 *  key：关键字
 *  degree：结点孩子链表中的孩子数目
 *  mark：标记节点自上次成为另一个结点的孩子后，是否失去过孩子
 *  parent：指向双亲结点的指针
 *  child：指向孩子结点的指针
 *  left：指向左兄弟的指针
 *  right：指向右兄弟的指针
 */
template<typename Key>
struct FibHeapNode 
{
	Key key;
	size_t degree;
	bool mark;
	FibHeapNode<Key, Value>* parent;
	FibHeapNode<Key, Value>* child;
	FibHeapNode<Key, Value>* left;
	FibHeapNode<Key, Value>* right;
};

/*
 * 斐波那契堆
 *
 * 模板变量
 *  Key：斐波那契堆的关键字
 *  Compare：关键字的比较函数类型。
 *    函数类型：int Compare(Key k1, Key k2){ //... };
 *    返回值：当 k1<k2,返回值 <0; 当 k1==k2,返回值 =0; 当 k1>k2,返回值 >0
 *
 * 成员变量
 *  m_min：斐波那契堆的最小结点（若堆为空，则为NULL）
 *  m_num：当前斐波那契堆中的结点个数
 */
template<typename Key, typename Compare>
class FibHeap
{
public:
	FibHeap(Compare cmp);
	~FibHeap();

	void Insert(Key _Key);
	FibHeapNode<Key>* ExtractMin();

protected:
	typedef FibHeapNode<Key> __fib_heap_node;

private:
	FibHeapNode<Key>* m_min;
	size_t m_count;
	Compare compare;
};

template<typename Key, typename Compare>
inline FibHeap<Key>::FibHeap(Compare cmp)
{
	m_count = 0;
	m_min = NULL;
	compare = cmp;
}

template<typename Key, typename Compare>
inline FibHeap<Key>::~FibHeap()
{
	
}

template<typename Key, typename Compare>
inline void FibHeap<Key>::Insert(Key _Key)
{
	__fib_heap_node* node = new __fib_heap_node();
	node->key = _Key;
	node->degree = 0;
	node->parent = NULL;
	node->mark = false;
	node->child = NULL;

	if (m_min == NULL) {
		node->left = node;
		node->right = node;
		m_min = node;
	}
	else {
		node->left = m_min->left;
		node->right = m_min;
		m_min->left = node;
		if (compare(node->key, m_min->key) < 0) {
			m_min = node;
		}
	}

	++m_count;
}

template<typename Key, typename Compare>
inline FibHeapNode<Key>* FibHeap<Key, Compare>::ExtractMin()
{
	__fib_heap_node* z = m_min;

	if (z != NULL) {
		// add each child x of z to the root list
		__fib_heap_node* x = z->child;
		__fib_heap_node* p = NULL;
		while (x->left != NULL) x = x->left;
		while (x) {
			p = x->right;
			x->left = m_min->left;
			x->right = m_min;
			x->parent = NULL;
			m_min->left = x;
			x = p;
		}

		// remove z from the root list
		z->left->right = z->right;
		z->right->left = z->left;

		if (z == z->right) {
			m_min = NULL;
		}
		else {
			// TODO
		}

		m_count--;
	}

	return z;
}
