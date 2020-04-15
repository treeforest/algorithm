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
 * 冒泡排序(基于key的升序排列)
 *
 * 参数
 *  buf ：待排序的数组
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 其他
 *  时间复杂度 ：最好 T = O(N)， 最坏 T = O(N^2)，平均 T = O(N^2)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：稳定排序
 *  适用性 ：适用于顺序存储与链式存储
 */
template <typename Key, typename Value>
void BubbleSort(ElemType<Key, Value> buf[], int len, int (*compare)(Key v, Key w)) {
    int i, j;
    bool flag;
    ElemType<Key, Value> tmp;

    for (i = 0; i < len - 1; ++i) {
        flag = false;
        for (j = len - 1; j > i; --j) {
            if (compare(buf[j].key, buf[j - 1].key) < 0) {
                tmp = buf[j];
                buf[j] = buf[j - 1];
                buf[j - 1] = tmp;
                flag = true;
            } 
		}
        if (!flag) {
			return;
		}
    }
}