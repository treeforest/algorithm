#pragma once
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

/*
 * 树节点
 *
 * 成员变量
 *  val ：树节点保存的信息值
 *	lchild ：指向树节点左孩子节点的指针
 *  rchild ：指向树节点右孩子节点的指针
 *  parent ：指向树节点双亲节点的指针
 */
template<typename ElemType>
struct BTNode
{
	ElemType val;
	struct BTNode<ElemType>* lchild;
	struct BTNode<ElemType>* rchild;
	struct BTNode<ElemType>* parent;
};

/*
 * 二叉树(二叉搜索树)，左子树“小于”根节点，右子树“大于”根节点，不允许存在相同信息的节点
 *
 * 模板类型
 *  ElemType 二叉树存储的数据类型
 *  Compare: 元素 ElemType 的比较函数，
 *			函数原型为：int (*Compare)(ElemType v, ElemType w)
 *			返回值类型：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename ElemType, typename Compare>
class BTree
{
public:
	BTree(Compare cmp);
	virtual ~BTree();

	virtual bool Insert(const ElemType& _Val);
	virtual bool Delete(const ElemType& _Val);

	virtual void PreOrder(void (*visit)(const ElemType& _Val));
	virtual void InOrder(void (*visit)(const ElemType& _Val));
	virtual void PostOrder(void (*visit)(const ElemType& _Val));
	virtual void LevelOrder(void (*visit)(const ElemType& _Val));

	virtual ElemType Minimum();
	virtual ElemType Maximum();

	virtual size_t Size() const;
	virtual size_t Depth() const;
	virtual bool Empty() const;

private:
	void destroy(BTNode<ElemType>* T);
	BTNode<ElemType>* search(const ElemType& _Val);
	BTNode<ElemType>* minimum(BTNode<ElemType>* T);
	BTNode<ElemType>* maximun(BTNode<ElemType>* T);

	void Transplant(BTNode<ElemType>* p, BTNode<ElemType>* q);

private:
	BTNode<ElemType>* m_root;
	size_t m_size;
	Compare m_cmp;
};

/*
 * 构造函数
 *
 * 参数
 *  cmp ：为元素 ElemType 的比较函数的指针
 *        函数原型为：size_t (*Compare)(ElemType v, ElemType w)
 *	      Compare 返回值要求：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename ElemType, typename Compare>
inline BTree<ElemType, Compare>::BTree(Compare cmp)
{
	m_root = NULL;
	m_size = 0;
	m_cmp = cmp;
}

/*
 * 析构函数
 */
template<typename ElemType, typename Compare>
BTree<ElemType, Compare>::~BTree()
{
	destroy(m_root);
}

/*
 * 在二叉树中插入一个元素
 *
 * 参数
 *  _Val ：插入的元素值
 *
 * 返回值
 *  bool ：如果插入成功(即树中不存在该元素)，则返回 true
 *         如果插入失败，返回 false
 */
template<typename ElemType, typename Compare>
bool BTree<ElemType, Compare>::Insert(const ElemType& _Val)
{
	BTNode<ElemType>* p = NULL;
	BTNode<ElemType>* q = NULL;
	BTNode<ElemType>* node = NULL;
	int n = 0;

	// 查找到插入节点的叶子位置
	p = m_root;
	while (p) {
		q = p;
		n = m_cmp(_Val, p->val);
		if (n < 0) {
			p = p->lchild;
		}
		else if (n > 0) {
			p = p->rchild;
		}
		else {
			return false;
		}
	}

	node = new BTNode<ElemType>();
	node->lchild = NULL;
	node->rchild = NULL;
	node->val = _Val;
	node->parent = q;

	if (q == NULL) {
		m_root = node; // 树为空
	}
	else if (n < 0) {
		q->lchild = node;
	}
	else {
		q->rchild = node;
	}

	++m_size;
	return true;
}

/*
 * 删除二叉树中的元素
 *
 * 参数
 *  _Val ：删除的元素值
 *
 * 返回值
 *  bool ：如果删除成功(当存在该值为_Val的节点)，返回 true
 *         如果删除失败，返回 false
 */
template<typename ElemType, typename Compare>
bool BTree<ElemType, Compare>::Delete(const ElemType& _Val)
{
	BTNode<ElemType>* p = NULL;
	BTNode<ElemType>* q = NULL;

	// Search the node 
	p = search(_Val);
	if (!p) {
		return false;
	}

	if (!p->lchild) {
		Transplant(p, p->rchild);
	}
	else if (!p->rchild) {
		Transplant(p, p->lchild);
	}
	else {
		q = minimum(p->rchild);
		if (q->parent != p) {
			Transplant(q, q->rchild);
			q->rchild = p->rchild;
			q->rchild->parent = q;
		}
		Transplant(p, q);
		q->lchild = p->lchild;
		p->lchild->parent = q;
	}

	delete p;
	p = NULL;
	--m_size;

	return true;
}

/*
 * 二叉树前序遍历
 *
 * 参数
 *  visit ：该参数为访问树节点的函数指针，以实现对树节点的相关操作
 */
template<typename ElemType, typename Compare>
inline void BTree<ElemType, Compare>::PreOrder(void(*visit)(const ElemType& _Val))
{
	stack<BTNode<ElemType>*> st;
	BTNode<ElemType>* p = m_root;

	while (p || !st.empty()) {
		if (p) {
			visit(p->val);
			if (p->rchild) {
				st.push(p->rchild);
			}
			p = p->lchild;
		}
		else {
			p = st.top();
			st.pop();
		}
	}
}

/*
 * 二叉树中序遍历
 *
 * 参数
 *  visit ：该参数为访问树节点的函数指针，以实现对树节点的相关操作
 */
template<typename ElemType, typename Compare>
inline void BTree<ElemType, Compare>::InOrder(void(*visit)(const ElemType& _Val))
{
	stack<BTNode<ElemType>*> st;
	BTNode<ElemType>* p = m_root;

	while (p || !st.empty()) {
		if (p) {
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			visit(p->val);
			st.pop();
			p = p->rchild;
		}
	}
}

/*
 * 二叉树后序遍历
 *
 * 参数
 *  visit ：该参数为访问树节点的函数指针，以实现对树节点的相关操作
 */
template<typename ElemType, typename Compare>
inline void BTree<ElemType, Compare>::PostOrder(void(*visit)(const ElemType& _Val))
{
	stack<BTNode<ElemType>*> st;
	BTNode<ElemType>* r = NULL;
	BTNode<ElemType>* p = m_root;

	while (p || !st.empty()) {
		if (p) {
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
			}
			else {
				visit(p->val);
				st.pop();
				r = p;
				p = NULL;
			}
		}
	}
}

/*
 * 二叉树层次遍历
 *
 * 参数
 *  visit ：该参数为访问树节点的函数指针，以实现对树节点的相关操作
 */
template<typename ElemType, typename Compare>
inline void BTree<ElemType, Compare>::LevelOrder(void(*visit)(const ElemType& _Val))
{
	queue<BTNode<ElemType>*> qu;
	BTNode<ElemType>* p = NULL;
	qu.push(m_root);

	while (!qu.empty()) {
		p = qu.front();
		visit(p->val);
		qu.pop();

		if (p->lchild) {
			qu.push(p->lchild);
		}
		if (p->rchild) {
			qu.push(p->rchild);
		}
	}
}

/*
 * 获取二叉树中的最小值
 *
 * 返回值
 *  ElemType ：如果树不为空，返回最小的元素值
 *             如果树为空，则中断运行（获取最小值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename ElemType, typename Compare>
inline ElemType BTree<ElemType, Compare>::Minimum()
{
	BTNode<ElemType>* p = minimum(m_root);
	if (!p) {
		abort();
	}

	return p->val;
}

/*
 * 获取二叉树中的最大值
 *
 * 返回值
 *  ElemType ：如果树不为空，返回最大的元素值
 *             如果树为空，则中断运行（获取最大值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename ElemType, typename Compare>
inline ElemType BTree<ElemType, Compare>::Maximum()
{
	BTNode<ElemType>* p = maximun(m_root);
	if (!p) {
		abort();
	}

	return p->val;
}

/*
 * 获取树的节点个数
 */
template<typename ElemType, typename Compare>
inline size_t BTree<ElemType, Compare>::Size() const
{
	return m_size;
}

/*
 * 获取树的深度
 */
template<typename ElemType, typename Compare>
size_t BTree<ElemType, Compare>::Depth() const
{
	if (!m_root) {
		return 0;
	}

	size_t level = 0;
	size_t n = 0;
	BTNode<ElemType>* p = NULL;
	queue<BTNode<ElemType>*> qu;
	qu.push(m_root);

	while (!qu.empty()) {
		n = qu.size();
		++level;

		while (n--) {
			p = qu.front();
			qu.pop();
			if (p->lchild) {
				qu.push(p->lchild);
			}
			if (p->rchild) {
				qu.push(p->rchild);
			}
		}
	}

	return level;
}

/*
 * 树是否为空
 *
 * 返回值
 *  bool ：树为空，返回 true
 *         树不为空，返回 false
 */
template<typename ElemType, typename Compare>
inline bool BTree<ElemType, Compare>::Empty() const
{
	return m_size == 0 ? true : false;
}

/*
 * 销毁一棵子树
 *
 * 参数
 *  T ：待销毁的子树根节点
 */
template<typename ElemType, typename Compare>
void BTree<ElemType, Compare>::destroy(BTNode<ElemType>* T)
{
	if (T) {
		destroy(T->lchild);
		destroy(T->rchild);
		delete T;
		T = NULL;
	}
}

/*
 * 查找元素所对应的节点指针
 *
 * 参数：
 *  _Val ：待查找的元素值
 *
 * 返回值
 *  BTNode<ElemType>* ：如果存在该元素值，则返回对应的节点指针
 *                      如果不存在该元素值，则返回 NULL
 */
template<typename ElemType, typename Compare>
BTNode<ElemType>* BTree<ElemType, Compare>::search(const ElemType& _Val)
{
	BTNode<ElemType>* p = m_root;
	int n = 0;

	while (p) {
		n = m_cmp(_Val, p->val);
		if (n == 0) {
			break;
		}
		else if (n < 0) {
			p = p->lchild;
		}
		else {
			p = p->rchild;
		}
	}

	return p;
}

/*
 * 获取子树 T 中的最左节点(最小值节点)
 */
template<typename ElemType, typename Compare>
BTNode<ElemType>* BTree<ElemType, Compare>::minimum(BTNode<ElemType>* T)
{
	BTNode<ElemType>* p = T;
	if (p) {
		while (p->lchild) {
			p = p->lchild;
		}
	}

	return p;
}

/*
 * 获取子树 T 的右节点(最大值节点)
 */
template<typename ElemType, typename Compare>
BTNode<ElemType>* BTree<ElemType, Compare>::maximun(BTNode<ElemType>* T)
{
	BTNode<ElemType>* p = T;
	if (p) {
		while (p->rchild) {
			p = p->rchild;
		}
	}

	return p;
}

/*
 * 进行对子树的移动，使用子树 told 替换子树 told
 *
 * 参数
 *  told ：被替换的子树
 *  tnew ：替换的子树
 */
template<typename ElemType, typename Compare>
inline void BTree<ElemType, Compare>::Transplant(BTNode<ElemType>* told, BTNode<ElemType>* tnew)
{
	if (told->parent == NULL) {
		m_root = tnew;
	}
	else if (told == told->parent->lchild) {
		told->parent->lchild = tnew;
	}
	else {
		told->parent->rchild = tnew;
	}

	if (tnew != NULL) {
		tnew->parent = told->parent;
	}
}
