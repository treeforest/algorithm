#pragma once

/*
 * 排序结点定义
 */
template <typename Key, typename Value>
struct ElemType {
    Key key;
    Value val;
};

/*
 * 直接插入排序(基于key的升序排列)
 *
 * 参数
 *  buf ：待排序的数组。规定 buf[0] 为哨兵位，不存储数据
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 * 
 * 其他
 *  时间复杂度 ：最好 T = O(N)， 最坏 T = O(N^2)，平均 T = O(N^2)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：稳定排序
 *  适用性 ：适用于顺序存储于链式存储
 */
template <typename Key, typename Value>
void InsertSort(ElemType<Key, Value> buf[], int len, int (*compare)(Key v, Key w)) {
	int i, j;
	for (i = 2; i <= len; ++i) {
        if (compare(buf[i].key, buf[i - 1].key) < 0) {
            buf[0] = buf[i];
            for (j = i - 1; compare(buf[j].key, buf[0].key) > 0; --j) {
                buf[j + 1] = buf[j];
            }
            buf[j + 1] = buf[0];
        }
	}
}