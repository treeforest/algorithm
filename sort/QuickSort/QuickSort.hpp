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
 * 快速排序(基于key的升序排列)
 *
 * 参数
 *  buf ：待排序的数组
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 其他
 *  时间复杂度 ：最坏 T = O(N^2)
 *  空间复杂度 ：最坏 S = O(N)
 *  稳定性 ：不稳定排序
 *  适用性 ：适用于顺序存储
 */
template <typename Key, typename Value>
void QuickSort(ElemType<Key, Value> buf[], int len, int (*compare)(Key v, Key w)) {
    quick_sort(buf, 0, len - 1, compare);
}

template <typename Key, typename Value>
void quick_sort(ElemType<Key, Value> buf[], int low, int high, int (*compare)(Key v, Key w)) {
    if (low < high) {
        int pivotpos = partition(buf, low, high, compare);
        quick_sort(buf, low, pivotpos - 1, compare);
        quick_sort(buf, pivotpos + 1, high, compare);
    }
}

template <typename Key, typename Value>
int partition(ElemType<Key, Value> buf[], int low, int high, int (*compare)(Key v, Key w)) {
    ElemType<Key, Value> pivot = buf[low];
    while (low < high) {
        while (low < high && compare(buf[high].key, pivot.key) >= 0)
            --high;
        buf[low] = buf[high];
        while (low < high && compare(buf[low].key, pivot.key) <= 0)
            ++low;
        buf[high] = buf[low];
    }
    buf[low] = pivot;
    return low;
}
