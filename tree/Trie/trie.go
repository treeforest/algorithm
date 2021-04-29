package trie

// trieNode trie节点
type TrieNode struct {
	// data 当前节点存储的值
	data rune
	// isEnd 标记一个关键字结尾
	isEnd bool
	// children 该节点的子节点
	children map[rune]*TrieNode
}

func NewTrieNode(data rune) *TrieNode {
	return &TrieNode{
		data:     data,
		isEnd:    false,
		children: make(map[rune]*TrieNode),
	}
}

// Trie trie树
type Trie struct {
	// root trie根节点
	root *TrieNode
}

func NewTrie() *Trie {
	return &Trie{root: NewTrieNode(rune('/'))}
}

// Insert 插入一个关键字
func (trie *Trie) Insert(key string) {
	node := trie.root
	for _, v := range key { // 注：for range采用Unicode字符遍历
		child, ok := node.children[v]
		if !ok {
			child = NewTrieNode(v)
			node.children[v] = child
		}
		node = child
	}
	node.isEnd = true
}

// Find 查找关键字，存在返回true，否则返回false
func (trie *Trie) Find(key string) bool {
	node := trie.root
	for _, v := range key {
		child, ok := node.children[v]
		if !ok {
			return false
		}
		node = child
	}
	return node.isEnd
}
