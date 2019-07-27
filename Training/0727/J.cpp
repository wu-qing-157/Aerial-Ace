#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 10;
const int P = 1e9 + 7;
const int inf = 1e9;
vector<int>T[maxn];
int val[maxn], siz[maxn];
int n, k, r;
int F[maxn][maxn], G[maxn][maxn];


void dfs(int u, int f) {
	for (int i = 1; i <= k; i++) F[u][i] = -inf;
	for (int i = 1; i <= k; i++) G[u][i] = 0;
	F[u][1] = val[u];
	G[u][1] = 1;
	siz[u] = 1;
	for (auto v : T[u]) {
		if (v == f) continue;
		dfs(v, u);
		for (int s1 = siz[u]; s1 >= 1; s1--)
			for (int s2 = siz[v]; s2 >= 1; s2--) {
				if (s1 + s2 > k) continue;
				if (F[u][s1 + s2] == F[u][s1] + F[v][s2]) {
					(G[u][s1 + s2] += (1ll * G[u][s1] * G[v][s2] % P)) %= P;
				} else 
				if (F[u][s1 + s2] < F[u][s1] + F[v][s2]) {
					F[u][s1 + s2] = F[u][s1] + F[v][s2];
					G[u][s1 + s2] = 1ll * G[u][s1] * G[v][s2] % P;
				}
			}
		siz[u] = min(k, siz[v] + siz[u]);
	}
}

void work() {
	scanf("%d%d%d", &n, &k, &r);
	
	for (int i = 0; i < n; i++) T[i].clear();
	for (int i = 0; i < n; i++) scanf("%d", &val[i]);
	
	for (int i = 1; i <= r; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		T[u].push_back(v);
		T[v].push_back(u);
	}
	
	dfs(0, -1);
	
	int ans = -inf, cnt = 0;
	for (int u = 0; u < n; u++) {
		if (F[u][k] == ans) 
			(cnt += G[u][k]) %= P;
		else 
		if (F[u][k] > ans)
			ans = F[u][k],
			cnt = G[u][k];
	}
	printf("%d %d\n", ans, cnt);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) 
		work();
	return 0;
}
/*
1
2 1 1
10 10
0 1
*/
