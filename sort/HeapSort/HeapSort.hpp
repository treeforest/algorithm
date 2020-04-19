#pragma once

#define DEFAULTSIZE 32
#define INCREASE 16

/*
 * 排序结点定义
 */
template <typename Key, typename Value>
struct ElemType {
    Key key;
    Value val;
};

/*
 * 大根堆
 *
 * 模板参数
 *  Key ：模板元素结点 key
 *  Value ： 模板元素结点 value
 *  Compare ：元素的比较函数。当 v > w 返回 > 0; 当 v < w 返回 < 0; 当 v == w 返回 = 0
 */
template <typename Key, typename Value, typename Compare>
class Heap
{
public:
    Heap(Compare cmp):compare(cmp){}

    virtual bool InsertUnique(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e);
    virtual bool InsertEqual(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e);

    virtual void Delete(ElemType<Key, Value> A[], int& len, const Key& _key);

    virtual void HeapSort(ElemType<Key, Value> A[], int len);

    virtual void BuildMaxHeap(ElemType<Key, Value> A[], int len);

private:
    bool insert(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e);

    void adjust_down(ElemType<Key, Value> A[], int k, int len);
    void adjust_up(ElemType<Key, Value> A[], int k);

    void swap(ElemType<Key, Value> A[], int i, int j);

    int parent(int i) const { return i / 2; }
    int lchild(int i) const { return 2 * i; }
    int rchild(int i) const { return 2 * i + 1; }

private:
    Compare compare;
};

/*
 * 插入一个元素，保证 key 值唯一
 */
template<typename Key, typename Value, typename Compare>
inline bool Heap<Key, Value, Compare>::InsertUnique(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e)
{
    int i;
    A[0] = e;
    for (i = len; compare(A[i].key, e.key) != 0; --i);
    if (i == 0) {
        return false;
    }

    return insert(A, len, cap, e);
}

/*
 * 插入一个元素，允许 key 重复
 */
template<typename Key, typename Value, typename Compare>
inline bool Heap<Key, Value, Compare>::InsertEqual(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e)
{
    return insert(A, len, cap, e);
}

/*
 * 根据 key 删除一个元素
 *
 * 删除值之后，在对堆进行调整
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::Delete(ElemType<Key, Value> A[], int& len, const Key& _key)
{
    bool flag = false;

    for (int i = 1; i <= len; ++i) {
        if (compare(A[i].key, _key) == 0) {
            swap(A, i, len);
            --len;
            flag = true;
        }
    }

    // 删除元素后破坏了堆
    if (flag == true) {
        BuildMaxHeap(A, len);
    }
}

/*
 * 堆排序(基于key的升序排列)
 *
 * 关于
 *  时间复杂度 ：T = O(log2n)
 *  空间复杂度 ：S = O(1)
 *  稳定性 ：不稳定排序
 *  适用性 ：适用于顺序存储
 */
template <typename Key, typename Value, typename Compare>
void Heap<Key, Value, Compare>::HeapSort(ElemType<Key, Value> A[], int len)
{
    BuildMaxHeap(A, len);
    for (int i = len; i > 1; --i) {
        swap(A, 1, i);// 将堆顶元素放到当前堆排序的末尾
        adjust_down(A, 1, i - 1); // 调整堆
    }
}

/*
 * 插入一个元素
 *
 * 参数
 *  A ：存放堆的数组
 *  len ：当前堆中元素个数
 *  cap ：数组A的容量
 *  e ：插入的元素
 *
 * 返回值
 *  bool ：插入成功，进行堆的调整，并返回true；否则返回false
 */
template <typename Key, typename Value, typename Compare>
bool Heap<Key, Value, Compare>::insert(ElemType<Key, Value> A[], int& len, int cap, const ElemType<Key, Value>& e)
{
    if (len >= cap) {
        return false;
    }

    len = len + 1;
	A[len] = e;
	adjust_up(A, len);
    return true;
}

/*
 * 建立大根堆
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::BuildMaxHeap(ElemType<Key, Value> A[], int len)
{
    for (int i = len / 2; i > 0; --i) {
        adjust_down(A, i, len);
    }
}

/*
 * 向下调整堆
 *
 * 参数
 *  k ：待调整的元素的下标
 */
template <typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::adjust_down(ElemType<Key, Value> A[], int k, int len) {
    A[0] = A[k];
    int i = lchild(k);

    for (i; i <= len; i = lchild(i)) {
        if (i < len && compare(A[i].key, A[i + 1].key) < 0) {
            ++i;
        }

        if (compare(A[0].key, A[i].key) >= 0) {
            break;
        }
        else {
            A[k] = A[i];
            k = i;
        }
    }

    A[k] = A[0];
}

/*
 * 向上调整堆
 *
 * 参数
 *  k ：待调整的元素的下标
 */
template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::adjust_up(ElemType<Key, Value> A[], int k)
{
    A[0] = A[k];
    int i = parent(k);
    while (i > 0 && compare(A[i].key, A[0].key) < 0) {
        A[k] = A[i];
        k = i;
        i = parent(k);
    }
    A[k] = A[0];
}

template<typename Key, typename Value, typename Compare>
inline void Heap<Key, Value, Compare>::swap(ElemType<Key, Value> A[], int i, int j)
{
    ElemType<Key, Value> tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}
