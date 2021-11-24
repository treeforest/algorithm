package leetcode

type MyHashSet struct {
	set     [][]int
	hashKey int
}

func Constructor() MyHashSet {
	hashKey := 111
	set := make([][]int, hashKey)
	for i, _ := range set {
		set[i] = make([]int, 0)
	}
	return MyHashSet{
		set:     set,
		hashKey: hashKey,
	}
}

func (this *MyHashSet) hash(key int) int {
	return key % this.hashKey
}

func (this *MyHashSet) Add(key int) {
	i := this.hash(key)
	for _, v := range this.set[i] {
		if v == key {
			return
		}
	}
	this.set[i] = append(this.set[i], key)
}

func (this *MyHashSet) Remove(key int) {
	i := this.hash(key)
	for j, v := range this.set[i] {
		if v == key {
			this.set[i] = append(this.set[i][:j], this.set[i][j+1:]...)
			return
		}
	}
}

func (this *MyHashSet) Contains(key int) bool {
	i := this.hash(key)
	for _, v := range this.set[i] {
		if v == key {
			return true
		}
	}
	return false
}

/**
 * Your MyHashSet object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Add(key);
 * obj.Remove(key);
 * param_3 := obj.Contains(key);
 */
