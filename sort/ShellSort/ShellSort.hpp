#pragma once
#include <iostream>
using namespace std;
/*
 * 排序结点定义
 */
template <typename Key, typename Value>
struct ElemType {
    Key key;
    Value val;
};

/*
 * 希尔排序 或 缩小增量排序（基于key的升序排列）
 *
 * 参数
 *  buf ：待排序的数组。规定 buf[0] 为哨兵位，不存储数据
 *  len ：数组的长度
 *  compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 *
 * 其他
 *  时间复杂度 ：最坏时间复杂度 T = O(N^2)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：不稳定排序
 *  适用性 ：仅适用于顺序存储
 */
template <typename Key, typename Value>
void ShellSort(ElemType<Key, Value> buf[], int len, int (*compare)(Key v, Key w)) {
    int i, j;
    int dk; // 增量

    for (dk = len / 2; dk >= 1; dk = dk / 2) {
        for (i = dk + 1; i <= len; ++i) {
            if (compare(buf[i].key, buf[i - dk].key) < 0) {
                buf[0] = buf[i];
                for (j = i - dk; j > 0 && compare(buf[j].key, buf[0].key) > 0; j = j - dk) {
                    buf[j + dk] = buf[j];
                }
                buf[j + dk] = buf[0];
            }
        }
        //test
//         cout << "\ndk = " << dk << ": ";
//         for (i = 1; i <= len; ++i) {
//             cout << buf[i].key << " ";
//         }
    }
}