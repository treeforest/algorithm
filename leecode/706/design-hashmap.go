package leetcode

type MyHashMap struct {
	store [][]KV
}

type KV struct {
	k, v int
}

func Constructor() MyHashMap {
	store := make([][]KV, 99)
	for i := 0; i < 99; i++ {
		store[i] = make([]KV, 0)
	}
	return MyHashMap{store: store}
}

func (this *MyHashMap) hash(key int) int {
	return key % 99
}

func (this *MyHashMap) Put(key int, value int) {
	k := this.hash(key)
	for i, kv := range this.store[k] {
		if kv.k == key {
			this.store[k][i].v = value
			return
		}
	}
	this.store[k] = append(this.store[k], KV{k: key, v: value})
}

func (this *MyHashMap) Get(key int) int {
	k := this.hash(key)
	for _, kv := range this.store[k] {
		if kv.k == key {
			return kv.v
		}
	}
	return -1
}

func (this *MyHashMap) Remove(key int) {
	k := this.hash(key)
	for i, kv := range this.store[k] {
		if kv.k == key {
			this.store[k] = append(this.store[k][:i], this.store[k][i+1:]...)
			return
		}
	}
}

/**
 * Your MyHashMap object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Put(key,value);
 * param_2 := obj.Get(key);
 * obj.Remove(key);
 */
