#pragma once
#include <memory>

#define LIST_INIT_SIZE 32
#define LISTINCREMENT 32

template<typename ElemType>
class SqList
{
public:
	SqList(int initLen = LIST_INIT_SIZE);
	~SqList();

	bool Free();
	bool Clear();
	bool Empty() const;
	int Length() const;
	int Capacity() const;
	bool Get(int i, ElemType& e);
	int Locate(ElemType e, bool(*compare)(ElemType, ElemType));
	bool Prior(ElemType cur, ElemType& pre, bool(*compare)(ElemType, ElemType));
	bool Next(ElemType cur, ElemType& next, bool(*compare)(ElemType, ElemType));
	bool Insert(int i, const ElemType e);
	bool Delete(int i, ElemType& e);

	static SqList<ElemType>* CreateList(int initLen = LIST_INIT_SIZE);
private:
	bool InitList(int initlen);

private:
	int m_len; // len
	int m_cap; // cap
	ElemType* m_sqlist;
};

template<typename ElemType>
bool SqList<ElemType>::InitList(int initlen)
{
	m_sqlist = (ElemType*)malloc(initlen * sizeof(ElemType));
	if (m_sqlist == NULL) {
		exit(OVERFLOW);
	}

	m_len = 0;
	m_cap = initlen;
	return true;
}

template<typename ElemType>
SqList<ElemType>::SqList(int initLen)
{
	InitList(initLen);
}

template<typename ElemType>
SqList<ElemType>::~SqList()
{
	Free();
}

template<typename ElemType>
SqList<ElemType>* SqList<ElemType>::CreateList(int initlen)
{
	SqList<ElemType>* sq = new SqList<ElemType>();
	if (sq == NULL) {
		return NULL;
	}

	sq->InitList(initlen);
	return sq;
}

template<typename ElemType>
bool SqList<ElemType>::Free()
{
	if (!m_sqlist)
		return false;

	delete[] m_sqlist;
	m_sqlist = NULL;
	m_len = 0;
	m_cap = 0;

	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Clear()
{
	if (!m_sqlist) {
		return false;
	}

	m_sqlist = (ElemType*)malloc(m_cap * sizeof(ElemType));
	m_len = 0;
	return true;
}

template<typename ElemType>
bool SqList<ElemType>::Empty() const
{
	if (m_len == 0) {
		return true;
	}

	return false;
}

template<typename ElemType>
int SqList<ElemType>::Length() const
{
	return m_len;
}

template<typename ElemType>
int SqList<ElemType>::Capacity() const
{
	return m_cap;
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
	if (i < 0 || i >= m_len)
		return false;

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