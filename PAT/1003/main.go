package main

import (
	"fmt"
	"math"
)

func main() {
	var N, M, C1, C2 int
	fmt.Scanf("%d%d%d%d", &N, &M, &C1, &C2)
	weight := make([]int, N)
	for i := 0; i < N; i++ {
		fmt.Scanf("%d", &weight[i])
	}

	edge := make([][]int, M)
	for i := 0; i < M; i++ {
		edge[i] = make([]int, M)
		for j := 0; j < M; j++ {
			edge[i][j] = math.MaxInt32
		}
	}
	var c1, c2, L int
	for i := 0; i < M; i++ {
		fmt.Scanf("%d%d%d", &c1, &c2, &L)
		edge[c1][c2] = L
		edge[c2][c1] = L
	}

	// Dijkstra
	teams := make([]int, N)   // 到点i的最大权重
	roads := make([]int, N)   // 到点i的最短路径个数
	visited := make([]int, N) // 访问标志
	dist := make([]int, N)    // 到点i的最短距离
	for i := 0; i < N; i++ {
		dist[i] = math.MaxInt32
	}

	dist[C1] = 0
	teams[C1] = weight[C1]
	roads[C1] = 1

	for i := 0; i < N; i++ {
		min := math.MaxInt32
		u := -1
		for j := 0; j < N; j++ {
			if visited[j] == 0 && dist[j] < min {
				min = dist[j]
				u = j
			}
		}
		if u == -1 {
			break
		}
		visited[u] = 1
		for j := 0; j < N; j++ {
			if visited[j] == 0 && edge[u][j] != math.MaxInt32 {
				if dist[u]+edge[u][j] < dist[j] {
					dist[j] = dist[u] + edge[u][j]
					roads[j] = roads[u]
					teams[j] = teams[u] + weight[j]
				} else if dist[u]+edge[u][j] == dist[j] {
					roads[j] = roads[j] + roads[u]
					if teams[u]+weight[j] > teams[j] {
						teams[j] = teams[u] + weight[j]
					}
				}
			}
		}
	}

	fmt.Printf("%d %d", roads[C2], teams[C2])
}
