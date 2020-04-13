#pragma once

#define DEFAULTSIZE 36

template<typename Key, typename Value>
struct ElemType {
	Key key;
	Value val;
};

template<typename Key, typename Value>
class SSTable {
protected:
	typedef Key __elem_key;
	typedef Value __elem_value;
	typedef ElemType<__elem_key, __elem_value> __elem_type;

private:
	__elem_type* elem;// 索引下标从 1 开始，0 为哨兵位置
	size_t m_len;

public:
	SSTable(size_t initlen = DEFAULTSIZE) {
		elem = new __elem_type[initlen + 1]();
		if (!elem) throw "new failed.";
		m_len = initlen;
	}

	~SSTable() {
		if (elem) delete[] elem;
	}

	size_t Len() const { return m_len; };

	/*
	 * 重载下标运算符
	 *
	 * 参数
	 *  _n ：元素的下标，下标范围为 1~m_len
	 */
	__elem_type& operator[] (size_t _n) {
		if (_n == 0 || _n > m_len) {
			throw "out of range.";
		}
		return elem[_n];
	}

	/*
	 * 顺序表的查找
	 *
	 * 参数
	 *  _key ：查找的key值
	 *  compare ：比较值是否相等的函数指针
	 */
	int search_seq(__elem_key _key, bool (*equal)(__elem_key v, __elem_key w)) {
		int i = 0;
		elem[0].key = _key;
		for (i = m_len; !equal(elem[i].key, _key); --i);
		return i;
	}
};