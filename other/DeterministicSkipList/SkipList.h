#pragma once

#define ININITY (~(1 << (sizeof(int) * 8 - 1)))

typedef int ElementType;
typedef struct SkipNode{
	ElementType elem;
	SkipNode *right;
	SkipNode *down;
}SkipNode, *SkipList, *Position;

/*
 * 确定性跳跃表（1-2-3 确定性跳跃表）
 */
class CSkipList
{
public:
	CSkipList();
	~CSkipList();

	Position Find(ElementType elem);
	void Insert(ElementType elem);
	void Delete(ElementType elem);

private:
	SkipList m_skiplist;
	Position m_bottom;
	Position m_tail;
};

