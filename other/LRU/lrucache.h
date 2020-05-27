#pragma once

typedef int Value;
struct Cache;

class LRUCache 
{
public:
	LRUCache(int capacity);
	~LRUCache();

	Value Get(int key);
	void Put(int key, Value value);

private:
	int m_cap;
	int m_count;
	int m_len;
	int m_size;
	Cache** m_szCache;
};