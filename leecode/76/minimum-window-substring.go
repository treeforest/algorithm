package leetcode

func minWindow(s string, t string) string {
	l, r, n, need, needCnt := 0, 0, len(s), make(map[byte]int), len(t)
	from, to := 0, 100001
	for i := 0; i < len(t); i++ {
		need[t[i]] += 1
	}
	for r < n {
		k := s[r]
		if cnt, ok := need[k]; ok {
			need[k]--
			if cnt > 0 {
				needCnt--
			}
		}
		if needCnt == 0 {
			for {
				k = s[l]
				if cnt, ok := need[k]; ok {
					if cnt == 0 {
						break
					}
					need[k]++
				}
				l++ // 求解最优
			}
			if to-from > r-l {
				from, to = l, r
			}
			need[s[l]]++
			l++
			needCnt++
		}
		r++
	}
	if to == 100001 {
		return ""
	}
	return s[from : to+1]
}
