package trie

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestTrie(t *testing.T) {
	keys := []string{
		"hi",
		"hello",
		"world",
		"height",
		"he",
		"him",
		"Hi",
		"中国",
		"成都",
		"北京欢迎您",
	}

	trie := NewTrie()
	for _, key := range keys {
		trie.Insert(key)
	}

	assert.Equal(t, true, trie.Find("hi"))
	assert.Equal(t, true, trie.Find("中国"))
	assert.Equal(t, false, trie.Find("h"))
	assert.Equal(t, false, trie.Find("北京"))
	assert.Equal(t, false, trie.Find("heigh"))

	

}