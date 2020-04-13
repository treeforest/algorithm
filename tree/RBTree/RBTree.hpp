#pragma once
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

/*
 * 红黑颜色
 */
typedef bool RBColor;
const RBColor RED = true;
const RBColor BLACK = false;

/*
 * 树结点
 *
 * 成员变量
 *  val ：树结点保存的信息值
 *	lchild ：指向树结点左孩子结点的指针
 *  rchild ：指向树结点右孩子结点的指针
 *  parent ：指向树结点双亲结点的指针
 */
template<typename Key, typename Value>
struct RBNode
{
	Key key;
	Value val;
	RBColor color;
	struct RBNode<Key, Value>* lchild;
	struct RBNode<Key, Value>* rchild;
	struct RBNode<Key, Value>* parent;
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
 *  Key ：红黑树实现应用于有序集合set的 key 值类型
 *  Value ：红黑树实现应用于有序集合set的 value 值类型
 *  Compare: 元素 Key 的比较函数，
 *			函数原型为：int (*Compare)(Key v, Key w)
 *			返回值类型：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename Key, typename Value, typename Compare>
class RBTree
{
public:
	RBTree(Compare cmp);
	virtual ~RBTree();

	virtual bool InsertUnique(const Key& _Key, const Value& _Val);
	virtual bool InsertEqual(const Key& _Key, const Value& _Val);

	virtual bool Delete(const Key& _Key);
	virtual bool Modify(const Key& _Key, const Value& _Val);
	virtual Value* Search(const Key& _Key);

	virtual void PreOrder(void (*visit)(const Key& _Key, const Value& _Val));
	virtual void InOrder(void (*visit)(const Key& _Key, const Value& _Val));
	virtual void PostOrder(void (*visit)(const Key& _Key, const Value& _Val));
	virtual void LevelOrder(void (*visit)(const Key& _Key, const Value& _Val));

	virtual Value Minimum();
	virtual Value Maximum();

	virtual size_t Count() const;
	virtual size_t Depth() const;
	virtual bool Empty() const;

private:
	void destroy(RBNode<Key, Value>* T);
	bool insert(const Key& _Key, const Value& _Val, bool key_unique);
	RBNode<Key, Value>* search(const Key& _Key);
	RBNode<Key, Value>* minimum(RBNode<Key, Value>* T);
	RBNode<Key, Value>* maximun(RBNode<Key, Value>* T);

	void insert_fixup(RBNode<Key, Value>* T);

	void left_rotate(RBNode<Key, Value>* T);
	void right_rotate(RBNode<Key, Value>* T);

	void delete_fixup(RBNode<Key, Value>* T);
	void transplant(RBNode<Key, Value>* told, RBNode<Key, Value>* tnew);

private:
	RBNode<Key, Value>* m_root;
	RBNode<Key, Value>* NIL;// 哨兵空结点（为了便于处理红黑树代码中的边界条件，使之满足循环不定式）
	size_t m_count;
	Compare m_cmp;
};

/*
 * 构造函数
 *
 * 参数
 *  cmp ：为元素 Key 的比较函数的指针
 *        函数原型为：size_t (*Compare)(Key v, Key w)
 *	      Compare 返回值要求：
 *					(1)当 v > w 时返回 >0
 *					(2)当 v = w 时返回 =0
 *					(3)当 v < w 时返回 <0
 */
template<typename Key, typename Value, typename Compare>
inline RBTree<Key, Value, Compare>::RBTree(Compare cmp)
{
	NIL = new RBNode<Key, Value>();
	if (!NIL) {
		abort();
	}
	NIL->color = BLACK;
	NIL->lchild = NULL;
	NIL->rchild = NULL;
	NIL->parent = NULL;

	m_root = NIL;
	m_count = 0;
	m_cmp = cmp;
}

/*
 * 析构函数
 */
template<typename Key, typename Value, typename Compare>
RBTree<Key, Value, Compare>::~RBTree()
{
	destroy(m_root);

	if (NIL) {
		delete NIL;
	}
}

/*
 * 在二叉树中插入一个元素，key值唯一
 *
 * 参数
 *  _Key ：插入的key值
 *  _Val ：插入的key对应的value值
 *
 * 返回值
 *  bool ：如果插入成功(即树中不存在该元素)，则返回 true
 *         如果插入失败，返回 false
 */
template<typename Key, typename Value, typename Compare>
bool RBTree<Key, Value, Compare>::InsertUnique(const Key& _Key, const Value& _Val)
{
	return insert(_Key, _Val, true);
}


/*
 * 在二叉树中插入一个元素，允许key值重复
 *
 * 参数
 *  _Key ：插入的key值
 *  _Val ：插入的key对应的value值
 *
 * 返回值
 *  bool ：如果插入成功，则返回 true
 *         如果插入失败，返回 false
 */
template<typename Key, typename Value, typename Compare>
inline bool RBTree<Key, Value, Compare>::InsertEqual(const Key& _Key, const Value& _Val)
{
	return insert(_Key, _Val, false);
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
template<typename Key, typename Value, typename Compare>
bool RBTree<Key, Value, Compare>::Delete(const Key& _Key)
{
	RBNode<Key, Value>* p = NULL;
	RBNode<Key, Value>* q = NULL;
	RBNode<Key, Value>* t = NULL;
	RBColor tcolor;

	// p 为待删除的结点 
	p = search(_Key);
	if (p == NIL) {
		return false;
	}

	// 始终维持 t 是从树中删除的结点或者移至树内的结点
	t = p;
	tcolor = t->color;

	// 情况一：当 p 的子结点少于2时：如果 p 是黑色结点，移除后将导致黑高减一，需对 q 进行 DeleteFixup
	if (p->lchild == NIL) {
		q = p->rchild;
		transplant(p, p->rchild);
	}
	else if (p->rchild == NIL) {
		q = p->lchild;
		transplant(p, p->lchild);
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
			transplant(t, t->rchild);
			t->rchild = p->rchild;
			t->rchild->parent = t;
		}

		// t 替换 p 的位置
		transplant(p, t);
		t->lchild = p->lchild;
		t->lchild->parent = t;

		// 给替换 p 位置的 t 设置和 p 相同的颜色，确保被替换结点 p 原所在的黑高性质不变
		t->color = p->color;
	}
	
	// 如果 t 是黑色节点，删除或移动结点会引起红黑性质的破坏
	if (tcolor == BLACK) {
		delete_fixup(q);
	}

	delete p;
	p = NULL;
	--m_count;

	return true;
}

/*
 * 根据键(key)修改对应的值(val)
 *
 * 参数
 *  _Key ：准备修改的键
 *  _Val ：键所对应的新的值信息
 *
 * 返回值
 *  bool ：修改成功（存在_Key值），则返回 true
 *         修改失败，返回 false
 */
template<typename Key, typename Value, typename Compare>
bool RBTree<Key, Value, Compare>::Modify(const Key& _Key, const Value& _Val)
{
	RBNode<Key, Value>* p = search(_Key);
	if (p == NIL) {
		return false;
	}

	p->val = _Val;
	return true;
}

/*
 * 根据键(key)查找对应的值(val)
 *
 * 参数
 *  _Key ：准备查找的键
 *
 * 返回值
 *  Value* ：查找成功（存在_Key值），则返回拷贝的对应值的指针
 *               查找失败，返回 NULL
 */
template<typename Key, typename Value, typename Compare>
inline Value* RBTree<Key, Value, Compare>::Search(const Key& _Key)
{
	RBNode<Key, Value>* p = search(_Key);
	if (p == NIL) {
		return NULL;
	}

	Value* _Val = new Value();
	*_Val = p->val;
	return _Val;
}

/*
 * 二叉树前序遍历
 *
 * 参数
 *  visit ：该参数为访问树结点的函数指针，以实现对树结点的相关操作
 */
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::PreOrder(void(*visit)(const Key& _Key, const Value& _Val))
{
	stack<RBNode<Key, Value>*> st;
	RBNode<Key, Value>* p = m_root;

	while (p != NIL || !st.empty()) {
		if (p != NIL) {
			visit(p->key, p->val);
			if (p->rchild != NIL) {
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::InOrder(void(*visit)(const Key& _Key, const Value& _Val))
{
	stack<RBNode<Key, Value>*> st;
	RBNode<Key, Value>* p = m_root;

	while (p != NIL || !st.empty()) {
		if (p != NIL) {
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::PostOrder(void(*visit)(const Key& _Key, const Value& _Val))
{
	stack<RBNode<Key, Value>*> st;
	RBNode<Key, Value>* r = NIL;
	RBNode<Key, Value>* p = m_root;

	while (p != NIL || !st.empty()) {
		if (p != NIL) {
			st.push(p);
			p = p->lchild;
		}
		else {
			p = st.top();
			if (p->rchild != NIL && p->rchild != r) {
				p = p->rchild;
			}
			else {
				visit(p->key, p->val);
				st.pop();
				r = p;
				p = NIL;
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::LevelOrder(void(*visit)(const Key& _Key, const Value& _Val))
{
	queue<RBNode<Key, Value>*> qu;
	RBNode<Key, Value>* p = NULL;
	qu.push(m_root);

	while (!qu.empty()) {
		p = qu.front();
		visit(p->key, p->val);
		qu.pop();

		if (p->lchild != NIL) {
			qu.push(p->lchild);
		}
		if (p->rchild != NIL) {
			qu.push(p->rchild);
		}
	}
}

/*
 * 获取二叉树中的最小值
 *
 * 返回值
 *  Value ：如果树不为空，返回最小的元素值
 *          如果树为空，则中断运行（获取最小值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename Key, typename Value, typename Compare>
inline Value RBTree<Key, Value, Compare>::Minimum()
{
	RBNode<Key, Value>* p = minimum(m_root);
	if (p == NIL) {
		abort();
	}

	return p->val;
}

/*
 * 获取二叉树中的最大值
 *
 * 返回值
 *  Value ：如果树不为空，返回最大的元素值
 *          如果树为空，则中断运行（获取最大值前，先调用 Empty() 方法判断树是否为空）
 */
template<typename Key, typename Value, typename Compare>
inline Value RBTree<Key, Value, Compare>::Maximum()
{
	RBNode<Key, Value>* p = maximun(m_root);
	if (p == NIL) {
		abort();
	}

	return p->val;
}

/*
 * 获取树的结点个数
 */
template<typename Key, typename Value, typename Compare>
inline size_t RBTree<Key, Value, Compare>::Count() const
{
	return m_count;
}

/*
 * 获取树的深度
 */
template<typename Key, typename Value, typename Compare>
size_t RBTree<Key, Value, Compare>::Depth() const
{
	if (m_root == NIL) {
		return 0;
	}

	size_t level = 0;
	size_t n = 0;
	RBNode<Key, Value>* p = NULL;
	queue<RBNode<Key, Value>*> qu;
	qu.push(m_root);

	while (!qu.empty()) {
		n = qu.size();
		++level;

		while (n--) {
			p = qu.front();
			qu.pop();
			if (p->lchild != NIL) {
				qu.push(p->lchild);
			}
			if (p->rchild != NIL) {
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
template<typename Key, typename Value, typename Compare>
inline bool RBTree<Key, Value, Compare>::Empty() const
{
	return m_count == 0 ? true : false;
}

/*
 * 销毁一棵子树
 *
 * 参数
 *  T ：待销毁的子树根结点
 */
template<typename Key, typename Value, typename Compare>
void RBTree<Key, Value, Compare>::destroy(RBNode<Key, Value>* T)
{
	if (T) {
		destroy(T->lchild);
		destroy(T->rchild);
		delete T;
		T = NULL;
	}
}

template<typename Key, typename Value, typename Compare>
inline bool RBTree<Key, Value, Compare>::insert(const Key& _Key, const Value& _Val, bool key_unique)
{
	RBNode<Key, Value>* p = NULL;
	RBNode<Key, Value>* q = NULL;
	RBNode<Key, Value>* newnode = NULL;
	int n = 0;

	// 查找到插入结点的叶子位置
	p = m_root;
	if (key_unique == true) {
		while (p != NIL) {
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
	}
	else {
		while (p != NIL) {
			q = p;
			n = m_cmp(_Key, p->key);
			if (n < 0) {
				p = p->lchild;
			}
			else{
				p = p->rchild;
			}
		}
	}

	newnode = new RBNode<Key, Value>();
	newnode->lchild = NIL;
	newnode->rchild = NIL;
	newnode->key = _Key;
	newnode->val = _Val;
	newnode->parent = q;
	newnode->color = RED;

	if (q == NULL) {
		newnode->color = BLACK;
		newnode->parent = NIL;
		m_root = newnode; // 树为空
	}
	else {
		if (n < 0) {
			q->lchild = newnode;
		}
		else if (n > 0) {
			q->rchild = newnode;
		}

		insert_fixup(newnode);
	}

	++m_count;
	return true;
}

/*
 * 查找元素所对应的结点指针
 *
 * 参数：
 *  _Val ：待查找的元素值
 *
 * 返回值
 *  BTNode<Key, Value>* ：如果存在该元素值，则返回对应的结点指针
 *                                如果不存在该元素值，则返回 NULL 或者 m_nil 
 */
template<typename Key, typename Value, typename Compare>
RBNode<Key, Value>* RBTree<Key, Value, Compare>::search(const Key& _Key)
{
	RBNode<Key, Value>* p = m_root;
	int n = 0;

	while (p != NIL) {
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
template<typename Key, typename Value, typename Compare>
RBNode<Key, Value>* RBTree<Key, Value, Compare>::minimum(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	if (p && p != NIL) {
		while (p->lchild != NIL) {
			p = p->lchild;
		}
	}

	return p;
}

/*
 * 获取子树 T 的右结点(最大值结点)
 */
template<typename Key, typename Value, typename Compare>
RBNode<Key, Value>* RBTree<Key, Value, Compare>::maximun(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	if (p && p != NIL) {
		while (p->rchild != NIL) {
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::insert_fixup(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	RBNode<Key, Value>* q = NULL;

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
					left_rotate(p);
				}
				// 情况三：叔结点是黑色的，且 p 是一个左孩子 
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				right_rotate(p->parent->parent);
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
					right_rotate(p);
				}
				p->parent->color = BLACK;
				p->parent->parent->color = RED;
				left_rotate(p->parent->parent);
			}
		}
	}

	// 性质2 被破坏
	m_root->color = BLACK;
}

/*
 * 结点的左旋操作
 */
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::left_rotate(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	RBNode<Key, Value>* q = NULL;

	q = p->rchild;
	p->rchild = q->lchild;

	if (q->lchild != NIL) {
		q->lchild->parent = p;
	}

	q->parent = p->parent;

	if (p->parent == NIL) {
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::right_rotate(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	RBNode<Key, Value>* q = NULL;

	q = p->lchild;
	p->lchild = q->rchild;

	if (q->rchild != NIL) {
		q->rchild->parent = p;
	}

	q->parent = p->parent;

	if (p->parent == NIL) {
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
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::delete_fixup(RBNode<Key, Value>* T)
{
	RBNode<Key, Value>* p = T;
	RBNode<Key, Value>* q = NULL;

	while (p != m_root && p->color == BLACK) {

		if (p == p->parent->lchild) {

			q = p->parent->rchild;
			if (q->color == RED) {
				// 情况一：p 的兄弟结点 q 是红色的。转至 情况二 或 情况三 或 情况四
				q->color = BLACK; // 兄弟结点置为黑色
				p->parent->color = RED;
				left_rotate(p->parent);
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
					right_rotate(q);
					q = p->parent->rchild;
				}

				// 情况四：p 的兄弟结点是 q 是黑色的，且 q 的右孩子是红色的
				q->color = p->parent->color;
				p->parent->color = BLACK;
				q->rchild->color = BLACK;
				left_rotate(p->parent);
				p = m_root;
			}
		}

		else {
			q = p->parent->lchild;
			if (q->color == RED) {
				q->color = BLACK;
				p->parent->color = RED;
				right_rotate(p->parent);
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
					left_rotate(q);
					q = q->parent->lchild;
				}

				q->color = p->parent->color;
				p->parent->color = BLACK;
				q->lchild->color = BLACK;
				right_rotate(p->parent);
				p = m_root;
			}
		}
	}

	p->color = BLACK;
}

/*
 * 进行对子树的移动，使用子树 told 替换子树 tnew
 *
 * 参数
 *  told ：被替换的子树
 *  tnew ：替换的子树
 */
template<typename Key, typename Value, typename Compare>
inline void RBTree<Key, Value, Compare>::transplant(RBNode<Key, Value>* told, RBNode<Key, Value>* tnew)
{
	if (told->parent == NIL) {
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
