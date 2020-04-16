#pragma once

#include<iostream>
using namespace std;;

#define DEFAULTSIZE 32
#define INCREASE 16

/*
 * 排序结点定义
 */
template <typename Key, typename Value>
struct ElemType {
    Key key;
    Value val;
};

/*
 * 大根堆
 *
 * 模板参数
 *  Key ：模板元素结点 key
 *  Value ： 模板元素结点 value
 *  Compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 */
template <typename Key, typename Value, typename Compare>
class Heap
{
public:
    Heap(Compare cmp, int initlen = DEFAULTSIZE);
    virtual ~Heap();
    
	virtual bool InsertUnique(const ElemType<Key, Value>& elem);
    virtual bool InsertEqual(const ElemType<Key, Value>& elem);
    virtual void Delete(const Key& _key);

    virtual int Search(const Key& _key);
    virtual void HeapSort();

	virtual void Clear() { m_len = 0; }
	virtual int Len() const { return m_len; }
	virtual int Cap() const { return m_cap; }

    ElemType<Key, Value>& operator[] (int i) const{
        if (i < 1 || i > m_len) {
            throw "out of range.";
        }
        return m_szBuf[i];
    }

private:
    bool insert(const ElemType<Key, Value>& elem);
    int search(const Key& _key);
    int search_binary(const Key& _key);
    void build_max_heap();
    void adjust_down(int k, int len);
    void adjust_up(int k);
    void swap(int i, int j);

private:
    Compare m_cmpFunc;
    ElemType<Key, Value>* m_szBuf;
    int m_len;
    int m_cap;
    
    // 标记当前是否依旧排序，排序后的查询采用二分法查找
    bool m_bsort; 
};

template<typename Key, typename Value, typename Compare>
inline Heap<Key, Value, Compare>::Heap(Compare cmp, int initlen)
{
    m_szBuf = new ElemType<Key, Value>[initlen]();
    if (!m_szBuf) {
        throw "init failed";
    }

    m_len = 0;
    m_cap = initlen;
    m_cmpFunc = cmp;
    m_bsort = false;
}

template<typename Key, typename Value, typename Compare>
inline Heap<Key, Value, Compare>::~Heap()
{
    if (m_szBuf) delete[] m_szBuf;
}

/*
 * 插入一个元素，保证 key 值唯一
 */
template<typename Key, typename Value, typename Compare>
inline bool Heap<Key, Value, Compare>::InsertUnique(const ElemType<Key, Value>& elem)
{
    if (Search(elem.key)) {
        return false;
    }

    return insert(elem);
}

/*
 * 插入一个元素，允许 key 重复
 */
template<typename Key, typename Value, typename Compare>
inline bool Heap<Key, Value, Compare>::InsertEqual(const ElemType<Key, Value>& elem)
{
    return insert(elem);
}

/*
 * 根据 key 删除一个元素
 *
 * 删除值之后，在对堆进行调整
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::Delete(const Key& _key)
{
    bool flag = false;

    for (int i = 1; i <= m_len; ++i) {
        if (m_cmpFunc(m_szBuf[i].key, _key) == 0) {
            swap(i, m_len);
            --m_len;
            flag = true;
        }
    }

    // 删除元素后破坏了堆
    if (flag == true) {
        build_max_heap();
    }
}

/*
 * 根据 key 查找元素所在位置的下标
 */
template<typename Key, typename Value, typename Compare>
inline int Heap<Key, Value, Compare>::Search(const Key& _key)
{
    if (!m_bsort) {
        return search(_key);
    }

    return search_binary(_key);
}

/*
 * 堆排序(基于key的升序排列)
 *
 * 关于
 *  时间复杂度 ：T = O(log2n)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：不稳定排序
 *  适用性 ：适用于顺序存储
 */
template <typename Key, typename Value, typename Compare>
void Heap<Key, Value, Compare>::HeapSort()
{
    // 	ElemType<Key, Value> tmp;
    // 	build_max_heap();
    for (int i = m_len; i > 1; --i) {
        swap(1, i);// 将堆顶元素放到当前堆排序的末尾
        adjust_down(1, i - 1); // 调整堆
    }
    m_bsort = true;
}

/*
 * 插入一个元素
 */
template <typename Key, typename Value, typename Compare>
bool Heap<Key, Value, Compare>::insert(const ElemType<Key, Value>& elem)
{
	if (m_len + 1 == m_cap) {
		ElemType<Key, Value>* newbase = new ElemType<Key, Value>[m_cap + INCREASE]();
		if (!newbase) throw "new error.";
		for (int i = 1; i <= m_len; ++i) {
			newbase[i] = m_szBuf[i];
		}
		delete[] m_szBuf;
		m_szBuf = newbase;
		m_cap = m_cap + INCREASE;
	}

	m_len = m_len + 1;
	m_szBuf[m_len] = elem;

	adjust_up(m_len);
    m_bsort = false;

    // test
    for (int i = 1; i <= m_len; i++) {
        cout << m_szBuf[i].key << " ";
    }
    cout << endl;

    return true;
}

/*
 * 顺序查找
 */
template<typename Key, typename Value, typename Compare>
inline int Heap<Key, Value, Compare>::search(const Key& _key)
{
    m_szBuf[0].key = _key;
    int i;
    for (i = m_len; m_cmpFunc(m_szBuf[i].key, _key) != 0; --i);
    return i;
}

template <typename Key, typename Value, typename Compare>
int Heap<Key, Value, Compare>::search_binary(const Key& _key)
{
	size_t low = 1, high = m_len, mid;
	int ret;

	while (low <= high) {
		mid = (low + high) / 2;
		ret = m_cmpFunc(m_szBuf[mid].key, _key);
		if (ret == 0) {
			return mid;
		}
		else if (ret > 0) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}

	return 0;
}

/*
 * 建立大根堆
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::build_max_heap()
{
    for (int i = m_len / 2; i > 0; --i) {
        adjust_down(i, m_len);
    }
}

/*
 * 向下调整堆
 *
 * 参数
 *  k ：待调整的元素的下标
 */
template <typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::adjust_down(int k, int len) {
    m_szBuf[0] = m_szBuf[k];

    for (int i = 2 * k; i <= len; i *= 2) {

        if (i < len && m_cmpFunc(m_szBuf[i].key, m_szBuf[i + 1].key) < 0) {
            ++i;
        }

        if (m_cmpFunc(m_szBuf[0].key, m_szBuf[i].key) >= 0) {
            break;
        }
        else {
            m_szBuf[k] = m_szBuf[i];
            k = i;
        }
    }

    m_szBuf[k] = m_szBuf[0];
}

/*
 * 向上调整堆
 *
 * 参数
 *  k ：待调整的元素的下标
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::adjust_up(int k)
{
    m_szBuf[0] = m_szBuf[k];
    int i = k / 2;
    while (i > 0 && m_cmpFunc(m_szBuf[i].key, m_szBuf[0].key) < 0) {
        m_szBuf[k] = m_szBuf[i];
        k = i;
        i = k / 2;
    }
    m_szBuf[k] = m_szBuf[0];
}

template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::swap(int i, int j)
{
    ElemType<Key, Value> tmp;
    tmp = m_szBuf[i];
    m_szBuf[i] = m_szBuf[j];
    m_szBuf[j] = tmp;
}
