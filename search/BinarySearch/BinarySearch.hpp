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
	__elem_type* elem;
	size_t m_len;

public:
	SSTable(size_t initlen = DEFAULTSIZE) {
		elem = new __elem_type[initlen]();
		if (!elem) throw "new failed.";
		m_len = initlen;
	}

	~SSTable() {
		if (elem) delete elem;
	}

	size_t Len() const { return m_len; };

	/*
	 * 重载下标运算符
	 *
	 * 参数
	 *  _n ：元素的下标，下标范围为 0~m_len-1
	 */
	__elem_type& operator[] (size_t _n) {
		if (_n >= m_len) {
			throw "out of range.";
		}
		return elem[_n];
	}

	/*
	 * 顺序表的查找
	 *
	 * 参数
	 *  _key ：查找的key值
	 *  equal ：比较值的函数指针
	 *        1、如果 v = w,返回值 = 0
	 *		  2、如果 v > w,返回值 > 0
	 *		  3、如果 v < w,返回值 < 0
	 *
	 * 时间复杂度 
	 *  T = O(log2n)
	 */
	int search_binary(__elem_key _key, int (*compare)(__elem_key v, __elem_key w)) {
		size_t low = 0, high = m_len - 1, mid;
		int ret;

		while (low <= high) {
			mid = (low + high) / 2;
			ret = compare(elem[mid].key, _key);
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

		return -1;
	}
};