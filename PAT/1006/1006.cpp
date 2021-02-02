#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int inf = 99999999;
int cmax, n, sp, m;
int e[510][510], weight[510], dist[510];
bool visit[510];
vector<int> pre[510], path, temppath;
int minNeed = inf, minBack= inf;

void dfs(int v) {
	temppath.push_back(v);
	if (v == 0) {
		int need = 0, back = 0;
		for (int i = temppath.size() - 1; i >= 0; i--) {
			int u = temppath[i];
			if (weight[u] > 0) {
				back += weight[u];
			}
			else {
				if (back > (0 - weight[u])) {
					back += weight[u];
				}
				else {
					need += (0 - weight[u]) - back;
					back = 0;
				}
			}
		}
		if (need < minNeed) {
			minNeed = need;
			minBack = back;
			path = temppath;
		}
		else if (need == minNeed && back < minBack) {
			minBack = back;
			path = temppath;
		}
		temppath.pop_back();
		return;
	}
	for (unsigned int i = 0; i < pre[v].size(); i++) {
		dfs(pre[v][i]);
	}
	temppath.pop_back();
}

int main() {
	fill(e[0], e[0] + 510 * 510, inf);
	fill(dist, dist + 510, inf);
	scanf("%d %d %d %d", &cmax, &n, &sp, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &weight[i]);
		weight[i] = weight[i] - cmax / 2;
	}
	for (int i = 0; i < m; i++) {
		int a, b, t;
		scanf("%d %d %d", &a, &b, &t);
		e[a][b] = e[b][a] = t;
	}
	dist[0] = 0;
	for (int i = 0; i <= n; i++) {
		int u = -1, minn = inf;
		for (int j = 0; j <= n; j++) {
			if (visit[j] == false && dist[j] < minn) {
				minn = dist[j];
				u = j;
			}
		}
		if (u == -1) break;
		visit[u] = true;
		for (int j = 0; j <= n; j++) {
			if (visit[j] == false && e[u][j] != inf) {
				if (dist[j] > dist[u] + e[u][j]) {
					dist[j] = dist[u] + e[u][j];
					pre[j].clear();
					pre[j].push_back(u);
				}
				else if (dist[j] == dist[u] + e[u][j]) {
					pre[j].push_back(u);
				}
			}
		}
	}
	dfs(sp);
	printf("%d 0", minNeed);
	for (int i = path.size() - 2; i >= 0; i--) {
		printf("->%d", path[i]);
	}
	printf(" %d", minBack);
	return 0;
}
