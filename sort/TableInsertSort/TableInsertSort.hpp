#pragma once

/*
 * 排序结点定义
 */
template <typename Key, typename Value>
struct ElemType {
    Key key;
    Value val;
    int next;
};

/*
 * 表插入排序
 *
 * 参数
 *  buf ：待排序的数组。buf[0]作为链表头结点，不存储真实的数据，其中buf[0].next指向key最大的结点下标
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 排序后的buf不能进行随机访问，只能顺序访问。通过 Arrange 重新排列之后，就可以顺序访问了
 */
template <typename Key, typename Value>
void TableInsertSort(ElemType<Key, Value> buf[], size_t len, int (*compare)(Key v, Key w)) {
    if (len < 2) return;

    size_t i, p, q;
    buf[0].next = 1;
    buf[1].next = 0;
    for (i = 2; i <= len; ++i) {
        for (p = 0; buf[p].next != 0; p = buf[p].next) {
            q = buf[p].next;
            if (compare(buf[q].key, buf[i].key) > 0) {
                break;
            }
        }
		buf[i].next = buf[p].next;
		buf[p].next = i;
    }

    Arrange(buf, len);
}

//重新排列函数
template <typename Key, typename Value>
void Arrange(ElemType<Key, Value> buf[], size_t len) {
    size_t p, q, i;
    ElemType<Key, Value> tmp;

    p = buf[0].next;
    for (i = 1; i < len; ++i) {
        while (p < i) p = buf[p].next;
        q = buf[p].next;
        if (p != i) {
            tmp = buf[p];
            buf[p] = buf[i];
            buf[i] = tmp;
            buf[i].next = p;
        }
        p = q;
    }
}