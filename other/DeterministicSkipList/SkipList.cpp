#include "SkipList.h"
#include <iostream>
using namespace std;

CSkipList::CSkipList()
{
	m_bottom = new SkipNode();
	if (!m_bottom) {
		cerr << "new error: out of space!" << endl;
	}
	m_bottom->right = m_bottom->down = m_bottom;

	m_tail = new SkipNode();
	if (!m_tail) {
		cerr << "new error: out of space!" << endl;
	}
	m_tail->elem = ININITY;
	m_tail->right = m_tail;

	m_skiplist = new SkipNode();
	if (!m_skiplist) {
		cerr << "new error: out of space!" << endl;
	}
	m_skiplist->elem = ININITY;
	m_skiplist->right = m_tail;
	m_skiplist->down = m_bottom;
}


CSkipList::~CSkipList()
{
}

Position CSkipList::Find(ElementType elem)
{
	Position current = m_skiplist;

	m_bottom->elem = elem;
	while (elem != current->elem) {
		if (elem < current->elem) {
			current = current->down;
		}
		else {
			current = current->right;
		}
	}

	return current;
}

void CSkipList::Insert(ElementType elem)
{
	Position current = m_skiplist;
	Position newNode;

	m_bottom->elem = elem;
	while (current != m_bottom) {
		while (elem > current->elem) {
			current = current->right;
		}

		/* If gap size is 3 or at bottom level */
		/* and must insert, then promote the middle element */
		if (current->elem > current->down->right->right->elem) {
			newNode = new SkipNode();
			if (!newNode) {
				cerr << "new error: out of space!" << endl;
			}
			newNode->right = current->right;
			newNode->down = current->down->right->right;
			current->right = newNode;
			newNode->elem = current->elem;
			current->elem = current->down->right->elem;
		}
		else {
			current = current->down;
		}
	}

	/* Raise height of DSL if necessary */
	if (m_skiplist->right != m_tail) {
		newNode = new SkipNode();
		if (!newNode) {
			cerr << "new error: out of space!" << endl;
		}
		newNode->down = m_skiplist;
		newNode->right = m_tail;
		newNode->elem = ININITY;
		m_skiplist = newNode;
	}
}

void CSkipList::Delete(ElementType elem)
{
	// TODO
}
