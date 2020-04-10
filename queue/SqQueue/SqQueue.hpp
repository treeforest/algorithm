#pragma once
#include <stdlib.h>

#define QUEUEINITSIZE 16
#define QUEUEINCREMENT 16

template<typename ElemType>
class SqQueue
{
public:
	SqQueue(size_t initlen = QUEUEINITSIZE);
	~SqQueue();

	void push(const ElemType& _Val);
	void pop();
	const ElemType& front() const;
	const ElemType& back() const;
	bool empty() const;
	size_t size() const;

private:
	ElemType* m_base;
	size_t m_front; // 循环队列头指针
	size_t m_back; // 循环队列尾指针
	size_t m_size;// 存储的元素个数
	size_t m_cap;// 数组容量大小
};

template<typename ElemType>
size_t SqQueue<ElemType>::size() const
{
	return m_size;
}

template<typename ElemType>
bool SqQueue<ElemType>::empty() const
{
	return m_size == 0 ? true : false;
}

template<typename ElemType>
const ElemType& SqQueue<ElemType>::back() const
{
	if (m_front == m_back) {
		abort();
	}

	return m_base[m_back - 1];
}

template<typename ElemType>
const ElemType& SqQueue<ElemType>::front() const
{
	if (m_front == m_back) {
		abort();
	}

	return m_base[m_front];
}

template<typename ElemType>
void SqQueue<ElemType>::pop()
{
	if (m_front != m_back) {
		m_front = (m_front + 1) % m_cap;
		--m_size;
	}
}

template<typename ElemType>
void SqQueue<ElemType>::push(const ElemType& _Val)
{
	if ((m_back + 1) % m_cap == m_front) {
		// 队满，则扩容
		ElemType* newbase = new ElemType[m_cap + QUEUEINCREMENT]();
		if (!newbase) {
			abort();
		}

		size_t i = 0;
		while (m_front != m_back) {
			newbase[i++] = m_base[m_front];
			m_front = (m_front + 1) % m_cap;
		}

		delete[] m_base;
		m_base = newbase;
		m_front = 0;
		m_back = i;
		m_cap = m_cap + QUEUEINCREMENT;
	}

	m_base[m_back] = _Val;
	m_back = (m_back + 1) % m_cap;
	++m_size;
}


template<typename ElemType>
SqQueue<ElemType>::~SqQueue()
{
	if (m_base) {
		delete[] m_base;
		m_base = NULL;
	}
}

template<typename ElemType>
SqQueue<ElemType>::SqQueue(size_t initlen)
{
	m_base = new ElemType[initlen]();
	if (!m_base) {
		abort();
	}

	m_front = 0;
	m_back = 0;
	m_size = 0;
	m_cap = initlen;
}
