package leetcode

func checkInclusion(s1 string, s2 string) bool {
	cnt, store := 0, make(map[byte]int)
	for i := 0; i < len(s1); i++ {
		store[s1[i]]++
		cnt++
	}
	l, r, n := 0, 0, len(s2)
	for r < n {
		if m, ok := store[s2[r]]; ok {
			if m == 0 && cnt != 0 {
				for s2[l] != s2[r] {
					if _, ok = store[s2[l]]; ok {
						store[s2[l]]++
						cnt++
					}
					l++
				}
				l++
			} else if m > 0 {
				store[s2[r]]--
				cnt--
				if cnt == 0 {
					return true
				}
			}
		} else {
			for l < r {
				if _, ok := store[s2[l]]; ok {
					store[s2[l]]++
					cnt++
				}
				l++
			}
		}
		r++
	}
	return false
}
