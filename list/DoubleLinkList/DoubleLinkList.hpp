#pragma once
#include <memory>

template<typename ElemType>
struct DuLNode 
{
	ElemType data;
	struct DuLNode* prior;
	struct DuLNode* next;
};

template<typename ElemType>
class DuLList
{
public:
	DuLList();
	~DuLList();

	bool Insert(int i, const ElemType e);
	bool Delete(int i, ElemType& e);
	bool Modify(int i, const ElemType e);
	bool Get(int i, ElemType& e);

	int Len() const { return m_len; }
	bool Empty() const { return m_len == 0 ? true : false; }

private:
	// 获取第 i 个元素的前驱指针
	DuLNode<ElemType>* PriorPointer(int i);
	// 获取指向第 i 个元素的指针
	DuLNode<ElemType>* Pointer(int i);

private:
	DuLNode<ElemType>* m_head;
	DuLNode<ElemType>* m_tail;
	int m_len;
};

template<typename ElemType>
bool DuLList<ElemType>::Get(int i, ElemType& e)
{
	DuLNode<ElemType>* p = Pointer(i);
	if (!p) {
		return false;
	}

	e = p->data;
	return true;
}

template<typename ElemType>
bool DuLList<ElemType>::Modify(int i, const ElemType e)
{
	DuLNode<ElemType>* p = Pointer(i);
	if (!p) {
		return false;
	}

	p->data = e;
	return true;
}

template<typename ElemType>
inline bool DuLList<ElemType>::Delete(int i, ElemType& e)
{	
	DuLNode<ElemType>* p = Pointer(i);
	if (!p) {
		return false;
	}

	e = p->data;
	p->prior->next = p->next;
	if (p == m_tail) {
		m_tail = p->prior;
	}
	else {
		p->next->prior = p->prior;
	}
	
	delete p;
	p = NULL;
	--m_len;
	return true;
}


template<typename ElemType>
bool DuLList<ElemType>::Insert(int i, const ElemType e)
{
	DuLNode<ElemType>* p = NULL;
	DuLNode<ElemType>* q = NULL;

	p = PriorPointer(i);
	if (!p) {
		return false;
	}

	q = new DuLNode<ElemType>();

	q->data = e;
	q->prior = p;
	q->next = p->next;
	if (p == m_tail) {
		p->next = q;
		m_tail = q;
	}
	else {
		// 非链尾节点
		p->next->prior = q;
		p->next = q;
	}
	
	++m_len;
	return true;
}

template<typename ElemType>
inline DuLNode<ElemType>* DuLList<ElemType>::PriorPointer(int i)
{
	if (i < 1 || i > m_len + 1) {
		return NULL;
	}

	DuLNode<ElemType>* p = m_head;
	for (int j = 1; j < i; j++) {
		p = p->next;
	}

	return p;
}

template<typename ElemType>
inline DuLNode<ElemType>* DuLList<ElemType>::Pointer(int i)
{
	DuLNode<ElemType>* p = PriorPointer(i);
	if (!p) {
		return NULL;
	}

	return p->next;
}

template<typename ElemType>
inline DuLList<ElemType>::DuLList()
{
	m_head = new DuLNode<ElemType>();
	m_head->prior = NULL;
	m_head->next = NULL;
	m_tail = m_head;
	m_len = 0;
}

template<typename ElemType>
inline DuLList<ElemType>::~DuLList()
{
	DuLNode<ElemType>* p = m_head;
	DuLNode<ElemType>* q = NULL;

	while (p) {
		q = p;
		p = p->next;
		delete q;
	}

	m_len = 0;
	m_head = NULL;
	m_tail = NULL;
}
