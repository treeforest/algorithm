#pragma once
#include <cstdlib>

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
	FibHeapNode<Key>* parent;
	FibHeapNode<Key>* child;
	FibHeapNode<Key>* left;
	FibHeapNode<Key>* right;
};

/*
 * 斐波那契堆
 *
 * 模板变量
 *  Key：斐波那契堆的关键字
 *  Compare：关键字的比较函数类型
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
	FibHeap(Compare cmp, Key minKey);
	~FibHeap();

	virtual void Insert(FibHeapNode<Key>* x);
	virtual void Delete(FibHeapNode<Key>* x);
	virtual void DecreaseKey(FibHeapNode<Key>* x, Key _newKey);
	virtual FibHeapNode<Key>* ExtractMin();

protected:
	typedef FibHeapNode<Key> __fib_heap_node;
	typedef Key __fib_key;

	void consolidate();
	void heap_link(__fib_heap_node* y, __fib_heap_node* x);
	void exchange(__fib_heap_node*y, __fib_heap_node* x);

	void cut(__fib_heap_node* x, __fib_heap_node* y);
	void cascading_cut(__fib_heap_node* y);

private:
	__fib_heap_node* m_min;
	size_t m_count;
	Key m_minKey;
	Compare compare;
};

/*
 * 构造函数
 *
 * 参数
 *  cmp：关键字 Key 的比较函数
 *  minKey：最小的关键字值
 */
template<typename Key, typename Compare>
inline FibHeap<Key, Compare>::FibHeap(Compare cmp, Key minKey)
{
	m_count = 0;
	m_min = NULL;
	compare = cmp;
	m_minKey = minKey;
}

template<typename Key, typename Compare>
inline FibHeap<Key, Compare>::~FibHeap()
{
	__fib_heap_node* x = NULL;
	while (m_min){
		x = ExtractMin();
		if (x) {
			delete x;
		}
	}
}

/*
 * 插入一个结点
 *
 * 参数
 *  _Key：插入结点的关键字
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::Insert(FibHeapNode<Key>* x)
{
	x->degree = 0;
	x->parent = NULL;
	x->child = NULL;
	x->mark = false;

	if (m_min == NULL) {
		x->left = x;
		x->right = x;
		m_min = x;
	}
	else {
		x->left = m_min->left;
		x->right = m_min;
		m_min->left->right = x;
		m_min->left = x;
		if (compare(x->key, m_min->key) < 0) {
			m_min = x;
		}
	}

	m_count++;
}

/*
 * 删除一个结点
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::Delete(FibHeapNode<Key>* x)
{
	DecreaseKey(x, m_minKey);
	__fib_heap_node* y = ExtractMin();
	if (y) {
		delete y;
	}
}

/*
 * 关键字减值
 *
 * 参数
 *  x：减值的结点
 *  _newKey：新的关键字值
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::DecreaseKey(FibHeapNode<Key>* x, Key _newKey)
{
	if (compare(_newKey, x->key) > 0) {
		// error: new key is greater than current key
		return;
	}

	__fib_heap_node* y = NULL;

	x->key = _newKey;
	y = x->parent;
	if (y != NULL && compare(x->key, y->key) < 0) {
		cut(x, y);
		cascading_cut(y);// x 可能是其父节点 y 被链接到另一个结点后被切掉的第二个孩子
	}

	if (compare(x->key, m_min->key) < 0) {
		m_min = x;
	}
}

/*
 * 抽取最小结点
 *
 * 返回值
 *  FibHeapNode<Key>*：指向最小结点的指针；若斐波那契堆为空，则返回 NULL
 */
template<typename Key, typename Compare>
inline FibHeapNode<Key>* FibHeap<Key, Compare>::ExtractMin()
{
	__fib_heap_node* z = m_min;

	if (z != NULL) {
		// add each child x of z to the root list
		if (z->child) {
			__fib_heap_node* p = NULL;
			__fib_heap_node* x = z->child;
			do 
			{
				p = x->right;
				x->left = m_min->left;
				x->right = m_min;
				x->parent = NULL;
				m_min->left->right = x;
				m_min->left = x;
				x = p;
			} while (x != z->child);
		}
		
		// remove z from the root list
		z->left->right = z->right;
		z->right->left = z->left;
		m_count--;

		if (z == z->right) {
			m_min = NULL;
		}
		else {
			m_min = z->right;
			consolidate();
		}
	}

	return z;
}

template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::consolidate()
{
	__fib_heap_node** A = NULL; 
	__fib_heap_node* x = NULL;
	__fib_heap_node* y = NULL;
	__fib_heap_node* w = NULL;
	__fib_heap_node* p = NULL;
	int d = 0;
	int count = 0;

	A = new __fib_heap_node*[m_count]();
	for (size_t i = 0; i < m_count; ++i) {
		A[i] = NULL;
	}

	p = m_min;
	do 
	{
		count++;
		p = p->right;
	} while (p != m_min);

	w = m_min;
	while (count > 0){
		x = w;
		w = w->right;
		d = x->degree;
		while (A[d] != NULL) {
			y = A[d];// another node with the same degree as x
			if (compare(x->key, y->key) > 0) {
				p = y;
				y = x;
				x = p;
			}
			heap_link(y, x);
			A[d] = NULL;
			d = d + 1;
		}
		A[d] = x;

		count--;
	}

	m_min = NULL;
	for (size_t i = 0; i < m_count; ++i){
		if (A[i] != NULL) {
			if (m_min == NULL) {
				m_min = A[i];
			}
			else {
				if (compare(A[i]->key, m_min->key) < 0) {
					m_min = A[i];
				}
			}
		}
	}

	delete[] A;
}

/*
 * 将 y 链接到 x
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::heap_link(__fib_heap_node * y, __fib_heap_node * x)
{
	// remove y from the root list
	y->right->left = y->left;
	y->left->right = y->right;

	// make y a child of x, incrementing x.degree
	__fib_heap_node* c = x->child;
	if (c == NULL) {
		y->left = y;
		y->right = y;
		x->child = y;
	}
	else {
		y->left = c->left;
		y->right = c;
		c->left->right = y;
		c->left = y;
	}

	y->parent = x;
	y->mark = false;
	x->degree++;
}

template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::exchange(__fib_heap_node * y, __fib_heap_node * x)
{
	__fib_key tmp = y->key;
	y->key = x->key;
	x->key = tmp;
}

/*
 * 切断 x 与父节点 y 之间的链接，使 x 成为根节点
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::cut(__fib_heap_node * x, __fib_heap_node * y)
{
	// remove x from the child list of y, decrementing y.degree
	if (x->left != x /* || x->right != x*/){
		x->left->right = x->right;
		x->right->left = x->left;
		y->child = x->left;
	}
	else {
		y->child = x->child;
		if (x->child){
			x->child->parent = y;
		}
	}
	y->degree--;

	// add x to the root list
	x->left = m_min->left;
	x->right = m_min;
	m_min->left->right = x;
	m_min->left = x;
	x->parent = NULL;
	x->mark = false;
}

/*
 * 级联切断
 */
template<typename Key, typename Compare>
inline void FibHeap<Key, Compare>::cascading_cut(__fib_heap_node * y)
{
	__fib_heap_node* z = NULL;
	z = y->parent;
	if (z) {
		if (y->mark == false) {
			y->mark = true;
		}
		else {
			cut(y, z);
			cascading_cut(z);// 递归向上
		}
	}
}
