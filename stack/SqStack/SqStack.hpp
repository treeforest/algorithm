#pragma once
#include <stdlib.h>

#define STACKINITSIZE 16
#define STACKINCREMENT 16

template <typename ElemType>
class SqStack
{
public:
	SqStack(int initlen = STACKINITSIZE);
	~SqStack();

	void push(const ElemType& _Val);
	void pop();
	ElemType top();
	size_t size() const;
	bool empty() const;

private:
	ElemType* m_base;
	ElemType* m_top;
	size_t m_size;
};

template <typename ElemType>
bool SqStack<ElemType>::empty() const
{
	return m_base == m_top ? true : false;
}

template <typename ElemType>
size_t SqStack<ElemType>::size() const
{
	return m_size;
}

template <typename ElemType>
ElemType SqStack<ElemType>::top()
{
	if (m_base == m_top) {
		abort();
	}

	return *m_top;
}

template <typename ElemType>
void SqStack<ElemType>::pop()
{
	if (m_base != m_top) {
		--m_top;
	}
}

template <typename ElemType>
void SqStack<ElemType>::push(const ElemType& _Val)
{
	if (m_top - m_base == m_size) {
		m_base = (ElemType*)realloc(m_base, (m_size + STACKINCREMENT) * sizeof(ElemType));
		if (!m_base) {
			abort();
		}
		m_top = m_base;
	}

	*m_top = _Val;
	++m_top;
	++m_size;
}

template <typename ElemType>
SqStack<ElemType>::~SqStack()
{
	if (m_base) {
		free(m_base);
		m_base = NULL;
		m_top = NULL;
		m_size = 0;
	}
}

template <typename ElemType>
SqStack<ElemType>::SqStack(int initlen)
{
	m_base = (ElemType*)calloc(initlen, sizeof(ElemType));
	if (!m_base) {
		abort();
	}

	m_top = m_base;
	m_size = 0;
}
