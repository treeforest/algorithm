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
 * 2-路插入排序
 *
 * 参数
 *  buf ：待排序的数组
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
void TwoWayInsertSort(ElemType<Key, Value> buf[], size_t len, int (*compare)(Key v, Key w)) {
    ElemType<Key, Value>* tmp = new ElemType<Key, Value>[len]();
    size_t front, rear, k, i;
    front = rear = 0;
    tmp[0] = buf[0];

    for (i = 1; i < len; ++i) {
        if (compare(buf[i].key, tmp[front].key) < 0) {// 小于最小值
            front = (front - 1 + len) % len;
            tmp[front] = buf[i];
        }
        else if (compare(buf[i].key, tmp[rear].key) > 0) {// 大于最大值
            rear = (rear + 1 + len) % len;
            tmp[rear] = buf[i];
        }
        else {// 介于最大值于最小值之间
            k = (rear + 1 + len) % len;
            while (compare(tmp[(k - 1 + len) % len].key, buf[i].key) > 0) {
                tmp[(k + len) % len] = tmp[(k - 1 + len) % len];
                k = (k - 1 + len) % len;
            }
            tmp[(k + len) % len] = buf[i];
            rear = (rear + 1) % len;
        }
    }

    // copy to buf
    for (i = 0; i < len; ++i) {
        buf[i] = tmp[(front + i + len) % len];
    }

    delete[] tmp;
}