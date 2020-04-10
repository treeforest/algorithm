#pragma once
#include <stdlib.h>

template<typename ElemType>
struct LSNode 
{
	ElemType val;
	struct LSNode<ElemType>* next;
};

template<typename ElemType>
class LStack
{
public:
	LStack();
	~LStack();

	void push(const ElemType& _Val);
	void pop();
	ElemType top();
	size_t size() const;
	bool empty() const;

private:
	LSNode<ElemType>* m_stack;
	LSNode<ElemType>* m_free;// ø’œ–¡¥±Ì
	size_t m_size;
};

template<typename ElemType>
bool LStack<ElemType>::empty() const
{
	return m_size == 0 ? true : false;
}

template<typename ElemType>
size_t LStack<ElemType>::size() const
{
	return m_size;
}

template<typename ElemType>
ElemType LStack<ElemType>::top()
{
	if (!(m_stack->next)) {
		abort();
	}

	return m_stack->next->val;
}

template<typename ElemType>
void LStack<ElemType>::pop()
{
	if (m_stack->next) {
		LSNode<ElemType>* p = m_stack->next;
		m_stack->next = p->next;
		p->next = m_free->next;
		m_free->next = p;
		--m_size;
	}
}

template<typename ElemType>
void LStack<ElemType>::push(const ElemType& _Val)
{
	LSNode<ElemType>* p = NULL;

	if (m_free->next) {
		p = m_free->next;
		m_free = p->next;
	}
	else {
		p = new LSNode<ElemType>();
	}

	p->val = _Val;
	p->next = m_stack->next;
	m_stack->next = p;
	++m_size;
}

template<typename ElemType>
LStack<ElemType>::~LStack()
{
	LSNode<ElemType>* p = NULL;
	LSNode<ElemType>* q = NULL;

	p = m_stack;
	while (p){
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

	m_stack = NULL;
	m_free = NULL;
	m_size = 0;
}


template<typename ElemType>
LStack<ElemType>::LStack()
{
	m_stack = new LSNode<ElemType>();
	if (!m_stack) {
		abort();
	}

	m_free = new LSNode<ElemType>();
	if (!m_free) {
		abort();
	}

	m_stack->next = NULL;
	m_free->next = NULL;
	m_size = 0;
}
