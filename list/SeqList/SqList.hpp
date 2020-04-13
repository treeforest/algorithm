#pragma once
#include <memory>

#define LIST_INIT_SIZE 32
#define LISTINCREMENT 32

template<typename ElemType>
class SqList
{
public:
	SqList(int initlen = LIST_INIT_SIZE);
	~SqList();
	
	int Locate(ElemType e, bool(*compare)(ElemType, ElemType));
	
	bool Insert(int i, const ElemType e);
	bool Delete(int i, ElemType& e);
	bool Get(int i, ElemType& e);

	bool Prior(ElemType cur, ElemType& pre, bool(*compare)(ElemType, ElemType));
	bool Next(ElemType cur, ElemType& next, bool(*compare)(ElemType, ElemType));

	bool Clear();

	int Len() const { return m_len; };
	int Cap() const { return m_cap; }
	bool Empty() const { return m_len == 0 ? true : false; }

private:
	int m_len; // len
	int m_cap; // cap
	ElemType* m_sqlist;
};

template<typename ElemType>
SqList<ElemType>::SqList(int initlen)
{
	m_sqlist = (ElemType*)malloc(initlen * sizeof(ElemType));
	if (m_sqlist == NULL) {
		exit(OVERFLOW);
	}

	m_len = 0;
	m_cap = initlen;
}

template<typename ElemType>
SqList<ElemType>::~SqList()
{
	if (m_sqlist) {
		delete[] m_sqlist;
		m_sqlist = NULL;
		m_len = 0;
		m_cap = 0;
	}
}

template<typename ElemType>
bool SqList<ElemType>::Clear()
{
	if (!m_sqlist) {
		return false;
	}

	// 惰性的清理空间，保留已经分配的内存
	m_len = 0;
	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Get(int i, ElemType& e)
{
	if (i < 0 || i >= m_len) {
		return false;
	}

	e = m_sqlist[i];
	return true;
}

template<typename ElemType>
int SqList<ElemType>::Locate(ElemType e, bool(*compare)(ElemType, ElemType))
{
	int i;
	for (i = 0; i < m_len && false == compare(m_sqlist[i], e); ++i);

	if (i < m_len) {
		return i;
	}

	return -1;
}

template<typename ElemType>
bool SqList<ElemType>::Prior(ElemType cur, ElemType& pre, bool(*compare)(ElemType, ElemType))
{
	int i = Locate(cur, compare);
	if (i <= 0) {
		return false;
	}

	pre = m_sqlist[i - 1];
	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Next(ElemType cur, ElemType& next, bool(*compare)(ElemType, ElemType))
{
	int i = Locate(cur, compare);
	if (i < 0 || i >= m_len - 1) {
		return false;
	}

	next = m_sqlist[i + 1];
	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Insert(int i, const ElemType e)
{
	if (i < 0 || i > m_len)
		return false;

	if (m_len == m_cap) {
		ElemType* newbase = NULL;
		newbase = (ElemType*)realloc(m_sqlist, (m_cap + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			return false;

		m_sqlist = newbase;
		m_cap = m_cap + LISTINCREMENT;
	}

	ElemType* p = NULL;
	ElemType* q = NULL;
	q = &(m_sqlist[i]);
	for (p = &(m_sqlist[m_len - 1]); p >= q; --p) {
		*(p + 1) = *p;
	}

	*q = e;
	++m_len;

	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Delete(int i, ElemType& e)
{
	if (i < 0 || i >= m_len) {
		return false;
	}
		
	ElemType* p = NULL;
	ElemType* q = NULL;

	p = &(m_sqlist[i]);
	e = *p;
	q = &(m_sqlist[m_len - 1]);
	++p;

	while (q >= p) {
		*(p - 1) = *p;
		++p;
	}

	--m_len;
	return true;
}