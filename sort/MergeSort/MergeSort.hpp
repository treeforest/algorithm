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
 * 归并排序(基于key的升序排列)
 *
 * 参数
 *  buf ：待排序的数组
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 其他
 *  时间复杂度 ：T = O(nlog2n)
 *  空间复杂度 ：S = O(n)
 *  稳定性 ：稳定排序
 *  适用性 ：适用于顺序存储
 */
template <typename Key, typename Value>
void MergeSort(ElemType<Key, Value> buf[], int len, int (*compare)(Key v, Key w)) {
    ElemType<Key, Value>* szTmp = new ElemType<Key, Value>[len + 1]();
    if (!szTmp) return;

    merge_sort(buf, szTmp, 0, len - 1, compare);

    delete szTmp;
}
template <typename Key, typename Value>
void merge_sort(ElemType<Key, Value> buf[], ElemType<Key, Value> szTmp[], int low, int high, int (*compare)(Key v, Key w)) {
    if (low < high) {
        int mid = (low + high) / 2;
        merge_sort(buf, szTmp, low, mid, compare);
        merge_sort(buf, szTmp, mid + 1, high, compare);
        merge(buf, szTmp, low, mid, high, compare);
    }
}
template <typename Key, typename Value>
void merge(ElemType<Key, Value> buf[], ElemType<Key, Value> szTmp[], int low, int mid, int high, int (*compare)(Key v, Key w)) {
    int i, j, k;

    for (k = low; k <= high; ++k) {
        szTmp[k] = buf[k];
    }

    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; ++k) {
        if (compare(szTmp[i].key, szTmp[j].key) < 0) {
            buf[k] = szTmp[i];
            ++i;
        }
        else {
            buf[k] = szTmp[j];
            ++j;
        }
    }

    while (i <= mid) buf[k++] = szTmp[i++];
    while (j <= mid) buf[k++] = szTmp[j++];
}