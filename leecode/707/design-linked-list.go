package leetcode

type MyLinkedList struct {
	list []int
}

func Constructor() MyLinkedList {
	return MyLinkedList{list: make([]int, 0)}
}

func (this *MyLinkedList) Get(index int) int {
	if index < 0 || index >= len(this.list) {
		return -1
	}
	return this.list[index]
}

func (this *MyLinkedList) AddAtHead(val int) {
	this.list = append([]int{val}, this.list...)
}

func (this *MyLinkedList) AddAtTail(val int) {
	this.list = append(this.list, val)
}

func (this *MyLinkedList) AddAtIndex(index int, val int) {
	if index > len(this.list) {
		return
	}
	if index < 0 {
		this.AddAtHead(val)
	} else if index == len(this.list) {
		this.AddAtTail(val)
	} else {
		for i, _ := range this.list {
			if index == i {
				this.list = append(this.list[:i], append([]int{val}, this.list[i:]...)...)
				break
			}
		}
	}
}

func (this *MyLinkedList) DeleteAtIndex(index int) {
	if index >= 0 && index < len(this.list) {
		this.list = append(this.list[:index], this.list[index+1:]...)
	}
}

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * obj := Constructor();
 * param_1 := obj.Get(index);
 * obj.AddAtHead(val);
 * obj.AddAtTail(val);
 * obj.AddAtIndex(index,val);
 * obj.DeleteAtIndex(index);
 */
