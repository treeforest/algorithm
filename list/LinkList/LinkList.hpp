#pragma once
#include <memory>

template<typename ElemType>
struct LNode
{
	ElemType data;
	struct LNode* next;
};

template<typename ElemType>
class LinkList
{
public:
	LinkList();
	~LinkList();

	bool Insert(int i, const ElemType e);
	bool Delete(int i, ElemType& e);
	bool Modify(int i, ElemType e);
	bool Get(int i, ElemType& e);
	int Cap() const { return m_cap; };

private:
	LNode<ElemType>* Prior(int i);
	LNode<ElemType>* Find(int i);

private:
	int m_cap;
	LNode<ElemType>* m_head;
	LNode<ElemType>* m_tail;
};

template<typename ElemType>
LinkList<ElemType>::LinkList()
{
	m_head = new LNode<ElemType>();
	if (!m_head) {
		exit(OVERFLOW);
	}

	m_head->next = NULL;
	m_tail = m_head;
	m_cap = 0;
}

template<typename ElemType>
LinkList<ElemType>::~LinkList()
{
	LNode<ElemType>* p = m_head;
	LNode<ElemType>* q;
	while (p != NULL) {
		q = p;
		p = q->next;
		delete q;
	}
	m_head = NULL;
	m_tail = NULL;
}

template<typename ElemType>
inline bool LinkList<ElemType>::Insert(int i, const ElemType e)
{
	LNode<ElemType>* pre = Prior(i);
	if (pre == NULL) {
		return false;
	}

	LNode<ElemType>* q = new LNode<ElemType>();
	q->data = e;
	q->next = pre->next;
	pre->next = q;
	++m_cap;

	return true;
}

template<typename ElemType>
inline bool LinkList<ElemType>::Delete(int i, ElemType& e)
{
	LNode<ElemType>* pre = Prior(i);
	if (pre == NULL) {
		return false;
	}

	LNode<ElemType>* q = pre->next;
	pre->next = q->next;
	delete q;
	--m_cap;

	return true;
}

template<typename ElemType>
inline bool LinkList<ElemType>::Modify(int i, ElemType e)
{
	LNode<ElemType>* p = Find(i);
	if (p == NULL) {
		return false;
	}

	p->data = e;

	return true;
}

template<typename ElemType>
inline bool LinkList<ElemType>::Get(int i, ElemType& e)
{
	LNode<ElemType>* p = Find(i);
	if (p == NULL) {
		return false;
	}

	e = p->data;

	return true;
}

template<typename ElemType>
inline LNode<ElemType>* LinkList<ElemType>::Prior(int i)
{
	if (i < 1 || i > m_cap + 1) {
		return NULL;
	}

	LNode<ElemType>* p = m_head;
	while (i > 1 && p != NULL) {
		p = p->next;
		--i;
	}

	return p;
}

template<typename ElemType>
inline LNode<ElemType>* LinkList<ElemType>::Find(int i)
{
	if (i < 1 || i > m_cap) {
		return NULL;
	}

	LNode<ElemType>* p = m_head;
	while (i > 0) {
		p = p->next;
		--i;
	}

	return p;
}
