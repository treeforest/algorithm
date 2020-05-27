#include "lrucache.h"
#include <cstdlib>

struct Cache
{
	int key;
	Value value;
	int count;
	Cache* next;
};

LRUCache::LRUCache(int capacity)
{
	m_szCache = new Cache*[capacity / 10 + 1]();
	if (!m_szCache) {
		abort();
	}
	m_cap = capacity;
	m_count = 0;
	m_len = 0;
	m_size = capacity / 10 + 1;
}

LRUCache::~LRUCache()
{
	if (m_szCache) {
		delete[] m_szCache;
	}
}

/*
 * 获取数据
 * 
 * 如果密钥 (key) 存在于缓存中，则获取密钥的值（总是正数），否则返回 -1。
 */
Value LRUCache::Get(int key)
{
	Cache* cache = m_szCache[key % m_size];
	Cache* tmp = NULL;
	Value ret = -1;

	while (cache) {
		if (cache->key == key) {
			m_count++;
			cache->count = m_count;
			ret = cache->value;
			if (cache->next) {
				Cache* t = cache;
				if (!tmp) {
					m_szCache[key%m_size] = cache->next;
				}
				else {
					tmp->next = cache->next;
				}
				while (cache->next) {
					cache = cache->next;
				}
				cache->next = t;
				t->next = NULL;
			}
			break;
		}
		tmp = cache;
		cache = cache->next;
	}

	return ret;
}

/*
 * 写入数据
 * 
 * 如果密钥(key)不存在，则写入其数据值。当缓存容量达到上限时，它应该在写入新数据
 * 之前删除最近最少使用的数据值，从而为新的数据值留出空间。
 */
void LRUCache::Put(int key, Value value)
{
	Cache* cache = m_szCache[key % m_size];
	Cache* tmp = NULL;

	while (cache) {
		// key 已存在
		if (cache->key == key) {
			m_count++;
			cache->count = m_count;
			cache->value = value;
			// 放到最后
			if (cache->next) {
				Cache* t = cache;
				if (!tmp) {
					m_szCache[key % m_size] = cache->next;
				}
				else {
					tmp->next = cache->next;
				}
				while (cache->next) {
					cache = cache->next;
				}
				cache->next = t;
				t->next = NULL;
			}
			return;
		}
		tmp = cache;
		cache = cache->next;
	}

	// 不存在key，但是有cache
	while (tmp && tmp->next) {
		tmp = tmp->next;
	}

	// 缓存已满
	if (m_len == m_cap) {
		int min = m_count + 1;
		int pin = 0;
		// 找到最少访问的队列
		for (int i = 0; i < m_size; i++) {
			if (m_szCache[i] && m_szCache[i]->count < min) {
				min = m_szCache[i]->count;
				pin = i;
			}
		}
		// tmp是和key一条队列的最后一个，如果满足这种情况，说明队列只有tmp
		if (tmp && m_szCache[pin]->key == tmp->key) {
			tmp = NULL;
		}
		// 删除最少使用的key
		m_szCache[pin] = m_szCache[pin]->next;
	}
	else {
		m_len++;
	}

	m_count++;
	Cache* t = new Cache;
	t->key = key;
	t->value = value;
	t->count = m_count;
	t->next = NULL;

	// 成为对应队列的第一个
	if (!tmp) {
		m_szCache [key % m_size] = t;
	}
	else {
		tmp->next = t;
	}
}
