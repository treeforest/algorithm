#pragma once
#include <stdlib.h>

template<typename ElemType>
struct QNode
{
	ElemType val;
	struct QNode<ElemType>* next;
};

template <typename ElemType>
class LQueue
{
public:
	LQueue();
	~LQueue();

	void push(const ElemType& _Val);
	void pop();
	const ElemType& front() const;
	const ElemType& back() const;
	bool empty() const;
	size_t size() const;

private:
	QNode<ElemType>* m_front;
	QNode<ElemType>* m_back;
	QNode<ElemType>* m_free;// ø’œ–¡¥±Ì
	size_t m_size;
};

template <typename ElemType>
size_t LQueue<ElemType>::size() const
{
	return m_size;
}

template <typename ElemType>
bool LQueue<ElemType>::empty() const
{
	return m_size == 0 ? true : false;
}

template <typename ElemType>
const ElemType& LQueue<ElemType>::back() const
{
	if (m_front == m_back) {
		abort();
	}

	return m_back->val;
}

template <typename ElemType>
const ElemType& LQueue<ElemType>::front() const
{
	if (!m_front->next) {
		abort();
	}

	return m_front->next->val;
}

template <typename ElemType>
void LQueue<ElemType>::pop()
{
	if (m_front->next) {
		QNode<ElemType>* p = m_front->next;
		if (p == m_back) {
			m_back = m_front;
		}

		m_front->next = p->next;

		p->next = m_free->next;
		m_free->next = p;

		--m_size;
	}
}

template <typename ElemType>
void LQueue<ElemType>::push(const ElemType& _Val)
{
	QNode<ElemType>* p = NULL;

	if (m_free->next) {
		p = m_free->next;
		m_free->next = p->next;
	}
	else {
		p = new QNode<ElemType>();
	}

	p->val = _Val;
	p->next = NULL;
	m_back->next = p;
	m_back = p;
	++m_size;
}

template <typename ElemType>
LQueue<ElemType>::~LQueue()
{
	QNode<ElemType>* p = NULL;
	QNode<ElemType>* q = NULL;

	p = m_front;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}

	p = m_free;
	while (p) {
		q = p;
		p = p->next;
		delete q;
	}

	m_front = NULL;
	m_back = NULL;
	m_front = NULL;
	m_size = 0;
}

template <typename ElemType>
LQueue<ElemType>::LQueue()
{
	m_front = new QNode<ElemType>();
	if (!m_front) {
		abort();
	}

	m_free = new QNode<ElemType>();
	if (!m_free) {
		abort();
	}

	m_front->next = NULL;
	m_back = m_front;
	m_free->next = NULL;
	m_size = 0;
}
