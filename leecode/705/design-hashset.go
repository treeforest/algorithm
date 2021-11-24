package leetcode

type MyHashSet struct {
	keys []bool
}

func Constructor() MyHashSet {
	return MyHashSet{keys: make([]bool, 1000001, 1000001)}
}

func (this *MyHashSet) Add(key int) {
	this.keys[key] = true
}

func (this *MyHashSet) Remove(key int) {
	this.keys[key] = false
}

func (this *MyHashSet) Contains(key int) bool {
	return this.keys[key]
}

/**
 * Your MyHashSet object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Add(key);
 * obj.Remove(key);
 * param_3 := obj.Contains(key);
 */
