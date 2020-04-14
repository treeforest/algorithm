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
 * 折半插入排序（基于key的升序排列）
 *
 * 参数
 *  buf ：待排序的数组。规定 buf[0] 为哨兵位，不存储数据
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 其他
 *  时间复杂度 ：T = O(N^2)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：稳定排序
 *  适用性 ：仅适用于顺序存储
 */
template <typename Key, typename Value>
void BinaryInsertSort(ElemType<Key, Value> buf[], size_t len, int (*compare)(Key v, Key w)) {
    size_t i, j, low, high, mid;

    for (i = 2; i <= len; ++i) {
        if (compare(buf[i].key, buf[i - 1].key) < 0) {
            buf[0] = buf[i];
            low = 1;
            high = i - 1;
            while (low <= high) {
                mid = (low + high) / 2;
                if (compare(buf[mid].key, buf[0].key) > 0) {
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            for (j = i - 1; j >= high + 1; --j) {
                buf[j + 1] = buf[j];
            }
            buf[high + 1] = buf[0];
        }
    }
}