#pragma once
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

/*
 * 红黑颜色
 */
enum ColorType 
{
	RED, BLACK,
};

/*
 * 树结点
 *
 * 成员变量
 *  val ：树结点保存的信息值
 *	lchild ：指向树结点左孩子结点的指针
 *  rchild ：指向树结点右孩子结点的指针
 *  parent ：指向树结点双亲结点的指针
 */
template<typename KeyType, typename ValueType>
struct RBNode
{
	KeyType key;
	ValueType val;
	ColorType color;
	struct RBNode<KeyType, ValueType>* lchild;
	struct RBNode<KeyType, ValueType>* rchild;
	struct RBNode<KeyType, ValueType>* parent;
};

/*
 * 二叉树(二叉搜索树)，左子树“小于”根结点，右子树“大于”根结点，不允许存在相同信息的结点
 *
 * 红黑树性质
 *  1、每个结点或是红色的，或是黑色的
 *  2、根结点是黑色的
 *  3、每个叶结点（NIL）是黑色的
 *  4、如果一个结点是红色的，则它的两个子结点都是黑色的
 *  5、对每个结点，从该节点都其所有后代叶结点的简单路径上，均包含相同数目的黑色结点
 *
 * 模板类型
 *  KeyType ：红黑树实现应用于有序集合set的 key 值类型
 *  ValueType ：红黑树实现应用于有序集合set的 value 值类型
 *  Compare: 元素 KeyType 的比较函数，
 *			函数原型为：int (*Compare)(KeyType v, KeyType w)
 *			返回值类型：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename KeyType, typename ValueType, typename Compare>
class RBTree
{
public:
	RBTree(Compare cmp);
	virtual ~RBTree();

	virtual bool Insert(const KeyType& _Key, const KeyType, ValueType& _Val);
	virtual bool Delete(const KeyType& _Key);

	virtual void PreOrder(void (*visit)(const KeyType& _Key, const ValueType& _Val));
	virtual void InOrder(void (*visit)(const KeyType& _Key, const ValueType& _Val));
	virtual void PostOrder(void (*visit)(const KeyType& _Key, const ValueType& _Val));
	virtual void LevelOrder(void (*visit)(const KeyType& _Key, const ValueType& _Val));

	virtual ValueType Minimum();
	virtual ValueType Maximum();

	virtual size_t Size() const;
	virtual size_t Depth() const;
	virtual bool Empty() const;

private:
	void Destroy(RBNode<KeyType, ValueType>* T);
	RBNode<KeyType, ValueType>* search(const KeyType& _Key);
	RBNode<KeyType, ValueType>* minimum(RBNode<KeyType, ValueType>* T);
	RBNode<KeyType, ValueType>* maximun(RBNode<KeyType, ValueType>* T);

	void InsertFixup(RBNode<KeyType, ValueType>* T);
	void LeftRotate(RBNode<KeyType, ValueType>* T);
	void RightRotate(RBNode<KeyType, ValueType>* T);

	void DeleteFixup(RBNode<KeyType, ValueType>* T);
	void Transplant(RBNode<KeyType, ValueType>* told, RBNode<KeyType, ValueType>* tnew);

private:
	RBNode<KeyType, ValueType>* m_root;
	RBNode<KeyType, ValueType>* m_nil;// 哨兵空结点（为了便于处理红黑树代码中的边界条件，使之满足循环不定式）
	size_t m_size;
	Compare m_cmp;
};

/*
 * 构造函数
 *
 * 参数
 *  cmp ：为元素 KeyType, ValueType 的比较函数的指针
 *        函数原型为：size_t (*Compare)(KeyType, ValueType v, KeyType, ValueType w)
 *	      Compare 返回值要求：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename KeyType, typename ValueType, typename Compare>
inline RBTree<KeyType, ValueType, Compare>::RBTree(Compare cmp)
{
	m_nil = new RBNode<KeyType, ValueType>();
	if (!m_nil) {
		abort();
	}
	m_nil->color = BLACK;
	m_nil->lchild = NULL;
	m_nil->rchild = NULL;
	m_nil->parent = NULL;

	m_root = NULL;
	m_size = 0;
	m_cmp = cmp;
}

/*
 * 析构函数
 */
template<typename KeyType, typename ValueType, typename Compare>
RBTree<KeyType, ValueType, Compare>::~RBTree()
{
	destroy(m_root);

	if (m_nil) {
		delete m_nil;
	}
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
template<typename KeyType, typename ValueType, typename Compare>
bool RBTree<KeyType, ValueType, Compare>::Insert(const KeyType& _Key, const KeyType, ValueType& _Val)
{
	RBNode<KeyType, ValueType>* p = NULL;
	RBNode<KeyType, ValueType>* q = NULL;
	RBNode<KeyType, ValueType>* newnode = NULL;
	int n = 0;

	// 查找到插入结点的叶子位置
	p = m_root;
	while (p) {
		q = p;
		n = m_cmp(_Key, p->key);
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

	newnode = new RBNode<KeyType, ValueType>();
	newnode->lchild = m_nil;
	newnode->rchild = m_nil;
	newnode->key = _Key;
	newnode->val = _Val;
	newnode->parent = q;
	newnode->color = RED;

	if (q == NULL) {
		newnode->color = BLACK;
		newnode->parent = m_nil;
		m_root = newnode; // 树为空
	}
	else {
		if (n < 0) {
			q->lchild = newnode;
		}
		else if (n > 0) {
			q->rchild = newnode;
		}
		
		InsertFixup(newnode);
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
 *  bool ：如果删除成功(当存在该值为_Val的结点)，返回 true
 *         如果删除失败，返回 false
 */
template<typename KeyType, typename ValueType, typename Compare>
bool RBTree<KeyType, ValueType, Compare>::Delete(const KeyType& _Key)
{
	RBNode<KeyType, ValueType>* p = NULL;
	RBNode<KeyType, ValueType>* q = NULL;
	RBNode<KeyType, ValueType>* t = NULL;
	ColorType tcolor;

	// p 为待删除的结点 
	p = search(_Key);
	if (!p) {
		return false;
	}

	// 始终维持 t 是从树中删除的结点或者移至树内的结点
	t = p;
	tcolor = t->color;

	// 情况一：当 p 的子结点少于2时：如果 p 是黑色结点，移除后将导致黑高减一，需对 q 进行 DeleteFixup
	if (!p->lchild) {
		q = p->rchild;
		Transplant(p, p->rchild);
	}
	else if (!p->rchild) {
		q = p->lchild;
		Transplant(p, p->lchild);
	}
	// 情况二：当 p 的子结点等于2时：如果替换的结点 t 为黑色，则将导致右子树黑高减一，需要对 t->rchild 进行 DeleteFixup
	else {
		// 获取 p 的后继结点
		t = minimum(p->rchild);
		tcolor = t->color;

		// 用 q 记录 t 的右孩子(该结点将替换 t 的位置)。将 t 替换 p 的位置后，如果 t 为黑色，将导致红黑性质的破坏
		q = t->rchild;

		if (t->parent == p) {
			// p 的右孩子没有左孩子
			q->parent = t;
		}
		else {
			// t 的右孩子替换 t 的位置
			Transplant(t, t->rchild);
			t->rchild = p->rchild;
			t->rchild->parent = t;
		}

		// t 替换 p 的位置
		Transplant(p, t);
		t->lchild = p->lchild;
		t->lchild->parent = t;

		// 给替换 p 位置的 t 设置和 p 相同的颜色，确保被替换结点 p 原所在的黑高性质不变
		t->color = p->color;
	}
	
	// 如果 t 是黑色节点，删除或移动结点会引起红黑性质的破坏
	if (tcolor == BLACK) {
		DeleteFixup(q);
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
 *  visit ：该参数为访问树结点的函数指针，以实现对树结点的相关操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::PreOrder(void(*visit)(const KeyType& _Key, const ValueType& _Val))
{
	stack<RBNode<KeyType, ValueType>*> st;
	RBNode<KeyType, ValueType>* p = m_root;

	while (p != m_nil || !st.empty()) {
		if (p != m_nil) {
			visit(p->key, p->val);
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
 *  visit ：该参数为访问树结点的函数指针，以实现对树结点的相关操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::InOrder(void(*visit)(const KeyType& _Key, const ValueType& _Val))
{
	stack<RBNode<KeyType, ValueType>*> st;
	RBNode<KeyType, ValueType>* p = m_root;

	while (p != m_nil || !st.empty()) {
		if (p != m_nil) {
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			visit(p->key, p->val);
			st.pop();
			p = p->rchild;
		}
	}
}

/*
 * 二叉树后序遍历
 *
 * 参数
 *  visit ：该参数为访问树结点的函数指针，以实现对树结点的相关操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::PostOrder(void(*visit)(const KeyType& _Key, const ValueType& _Val))
{
	stack<RBNode<KeyType, ValueType>*> st;
	RBNode<KeyType, ValueType>* r = NULL;
	RBNode<KeyType, ValueType>* p = m_root;

	while (p != m_nil || !st.empty()) {
		if (p != m_nil) {
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			if (p->rchild && p->rchild != r) {
				p = p->rchild;
			}
			else {
				visit(p->key, p->val);
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
 *  visit ：该参数为访问树结点的函数指针，以实现对树结点的相关操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::LevelOrder(void(*visit)(const KeyType& _Key, const ValueType& _Val))
{
	queue<RBNode<KeyType, ValueType>*> qu;
	RBNode<KeyType, ValueType>* p = NULL;
	qu.push(m_root);

	while (!qu.empty()) {
		p = qu.front();
		visit(p->key, p->val);
		qu.pop();

		if (p->lchild != m_nil) {
			qu.push(p->lchild);
		}
		if (p->rchild != m_nil) {
			qu.push(p->rchild);
		}
	}
}

/*
 * 获取二叉树中的最小值
 *
 * 返回值
 *  KeyType, ValueType ：如果树不为空，返回最小的元素值
 *             如果树为空，则中断运行（获取最小值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename KeyType, typename ValueType, typename Compare>
inline ValueType RBTree<KeyType, ValueType, Compare>::Minimum()
{
	RBNode<KeyType, ValueType>* p = minimum(m_root);
	if (!p) {
		abort();
	}

	return p->val;
}

/*
 * 获取二叉树中的最大值
 *
 * 返回值
 *  KeyType, ValueType ：如果树不为空，返回最大的元素值
 *             如果树为空，则中断运行（获取最大值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename KeyType, typename ValueType, typename Compare>
inline ValueType RBTree<KeyType, ValueType, Compare>::Maximum()
{
	RBNode<KeyType, ValueType>* p = maximun(m_root);
	if (!p) {
		abort();
	}

	return p->val;
}

/*
 * 获取树的结点个数
 */
template<typename KeyType, typename ValueType, typename Compare>
inline size_t RBTree<KeyType, ValueType, Compare>::Size() const
{
	return m_size;
}

/*
 * 获取树的深度
 */
template<typename KeyType, typename ValueType, typename Compare>
size_t RBTree<KeyType, ValueType, Compare>::Depth() const
{
	if (!m_root) {
		return 0;
	}

	size_t level = 0;
	size_t n = 0;
	RBNode<KeyType, ValueType>* p = NULL;
	queue<RBNode<KeyType, ValueType>*> qu;
	qu.push(m_root);

	while (!qu.empty()) {
		n = qu.size();
		++level;

		while (n--) {
			p = qu.front();
			qu.pop();
			if (p->lchild != m_nil) {
				qu.push(p->lchild);
			}
			if (p->rchild != m_nil) {
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
template<typename KeyType, typename ValueType, typename Compare>
inline bool RBTree<KeyType, ValueType, Compare>::Empty() const
{
	return m_size == 0 ? true : false;
}

/*
 * 销毁一棵子树
 *
 * 参数
 *  T ：待销毁的子树根结点
 */
template<typename KeyType, typename ValueType, typename Compare>
void RBTree<KeyType, ValueType, Compare>::Destroy(RBNode<KeyType, ValueType>* T)
{
	if (T) {
		destroy(T->lchild);
		destroy(T->rchild);
		delete T;
		T = NULL;
	}
}

/*
 * 查找元素所对应的结点指针
 *
 * 参数：
 *  _Val ：待查找的元素值
 *
 * 返回值
 *  BTNode<KeyType, ValueType>* ：如果存在该元素值，则返回对应的结点指针
 *                      如果不存在该元素值，则返回 NULL
 */
template<typename KeyType, typename ValueType, typename Compare>
RBNode<KeyType, ValueType>* RBTree<KeyType, ValueType, Compare>::search(const KeyType& _Key)
{
	RBNode<KeyType, ValueType>* p = m_root;
	int n = 0;

	while (p != m_nil) {
		n = m_cmp(_Key, p->key);
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
 * 获取子树 T 中的最左结点(最小值结点)
 */
template<typename KeyType, typename ValueType, typename Compare>
RBNode<KeyType, ValueType>* RBTree<KeyType, ValueType, Compare>::minimum(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	if (p) {
		while (p->lchild != m_nil) {
			p = p->lchild;
		}
	}

	return p;
}

/*
 * 获取子树 T 的右结点(最大值结点)
 */
template<typename KeyType, typename ValueType, typename Compare>
RBNode<KeyType, ValueType>* RBTree<KeyType, ValueType, Compare>::maximun(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	if (p) {
		while (p->rchild != m_nil) {
			p = p->rchild;
		}
	}

	return p;
}

/*
 * 插入结点时修正红黑树（对结点重新着色并旋转），使得新的树依旧满足红黑树的5个性质 
 *
 * while 循环在每次迭代的开头保持下列3个部分的不变式：
 *  a.结点 p 是红结点
 *  b.如果 p->parent 是根结点，则 p->parent 是黑结点
 *  c.如果有任何红黑性质被破坏，则至多只有一条被破坏，或是性质2，或是性质4。
 *    如果性质2被破坏，其原因是根结点是红结点。
 *    如果性质4被破坏，其原因为 p 和 p->parent 都是红结点。
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::InsertFixup(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	RBNode<KeyType, ValueType>* q = NULL;

	// 性质4 被破坏
	while (p->parent->color == RED) {
		// p 的双亲结点是左孩子的情况
		if (p->parent == p->parent->parent->lchild) {
			q = p->parent->parent->rchild;// 叔结点
			if (q->color == RED) {
				// 情况一：叔结点是红色的
				q->color = BLACK;
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				p = p->parent->parent;
			}
			else {
				// 情况二：叔结点是黑色的，且 p 是一个右孩子
				if (p == p->parent->rchild) {
					p = p->parent;
					LeftRotate(p);
				}
				// 情况三：叔结点是黑色的，且 p 是一个左孩子 
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				RightRotate(p->parent->parent);
			}
		}
		// p 的双亲结点是右孩子的情况（与是左孩子的情形相反）
		else {
			q = p->parent->parent->lchild;
			if (q->color == RED) {
				q->color = BLACK;
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				p = p->parent->parent;
			}
			else {
				if (p == p->parent->lchild) {
					p = p->parent;
					RightRotate(p);
				}
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				LeftRotate(p->parent->parent);
			}
		}
	}

	// 性质2 被破坏
	m_root->color = BLACK;
}

/*
 * 结点的左旋操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::LeftRotate(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	RBNode<KeyType, ValueType>* q = NULL;

	q = p->rchild;
	p->rchild = q->lchild;

	if (q->lchild != m_nil) {
		q->lchild->parent = p;
	}

	q->parent = p->parent;

	if (p->parent == m_nil) {
		m_root = q;
	}
	else if (T == T->parent->lchild) {
		p->parent->lchild = q;
	}
	else {
		p->parent->rchild = q;
	}

	q->lchild = p;
	p->parent = q;
}

/*
 * 结点的右旋操作
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::RightRotate(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	RBNode<KeyType, ValueType>* q = NULL;

	q = p->lchild;
	p->lchild = q->rchild;

	if (q->rchild != m_nil) {
		q->rchild->parent = p;
	}

	q->parent = p->parent;

	if (p->parent == m_nil) {
		m_root = q;
	}
	else if (p == p->parent->lchild) {
		p->parent->lchild = q;
	}
	else if (p == p->parent->rchild) {
		p->parent->rchild = q;
	}

	q->rchild = p;
	p->parent = q;
}

/*
 * 删除结点时修正红黑树（对结点重新着色并旋转），使得新的树依旧满足红黑树的5个性质
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::DeleteFixup(RBNode<KeyType, ValueType>* T)
{
	RBNode<KeyType, ValueType>* p = T;
	RBNode<KeyType, ValueType>* q = NULL;

	while (p != m_root && p->color == BLACK) {

		if (p == p->parent->lchild) {

			q = p->parent->rchild;
			if (q->color == RED) {
				// 情况一：p 的兄弟结点 q 是红色的。转至 情况二 或 情况三 或 情况四
				q->color = BLACK; // 兄弟结点置为黑色
				p->parent->color = RED;
				LeftRotate(p->parent);
				q = p->parent->rchild;
			}
			
			if (q->lchild->color == BLACK && q->rchild->color == BLACK) {
				// 情况二：p 的兄弟结点 q 是黑色的，且 q 的两个子节点都是黑色的
				q->color = RED;
				p = p->parent;
			}
			else {
				if (q->rchild->color == BLACK) {
					// 情况三：p 的兄弟结点 q 是黑色的，且 q 的左孩子是红色的，q 的右孩子是黑色的。转为情况四
					q->lchild->color = BLACK;
					q->color = RED;
					RightRotate(q);
					q = p->parent->rchild;
				}

				// 情况四：p 的兄弟结点是 q 是黑色的，且 q 的右孩子是红色的
				q->color = p->parent->color;
				p->parent->color = BLACK;
				q->rchild->color = BLACK;
				LeftRotate(p->parent);
				p = m_root;
			}
		}

		else {
			q = p->parent->lchild;
			if (q->color == RED) {
				q->color = BLACK;
				p->parent->color = RED;
				RightRotate(p->parent);
				q = p->parent->lchild;
			}
			if (q->rchild->color == BLACK && q->rchild->color == BLACK) {
				q->color = RED;
				p = p->parent;
			}
			else {
				if (q->lchild->color == BLACK) {
					q->rchild->color = BLACK;
					q->color = RED;
					LevelOrder(q);
					q = q->parent->lchild;
				}

				q->color = p->parent->color;
				p->parent->color = BLACK;
				q->lchild->color = BLACK;
				RightRotate(p->parent);
				p = m_root;
			}
		}
	}

	p->color = BLACK;
}

/*
 * 进行对子树的移动，使用子树 told 替换子树 told
 *
 * 参数
 *  told ：被替换的子树
 *  tnew ：替换的子树
 */
template<typename KeyType, typename ValueType, typename Compare>
inline void RBTree<KeyType, ValueType, Compare>::Transplant(RBNode<KeyType, ValueType>* told, RBNode<KeyType, ValueType>* tnew)
{
	if (told->parent == m_nil) {
		m_root = tnew;
	}
	else if (told == told->parent->lchild) {
		told->parent->lchild = tnew;
	}
	else {
		told->parent->rchild = tnew;
	}

	tnew->parent = told->parent;
}
