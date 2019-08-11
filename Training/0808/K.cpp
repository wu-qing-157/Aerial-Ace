#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int oo = 2e9;

vector<pair<int, int> >G[maxn], _G[maxn];

int f[maxn][2], g[maxn][2];
int L[maxn][2], R[maxn][2];



void dfs1(int u, int fa) {
	for (auto e : G[u])
		if (e.first != fa) dfs1(e.first, u);
	
	int n = G[u].size();
	for (int i = 0; i < n; i++) 
		L[i][0] = L[i][1] = R[i][0] = R[i][1] = oo;
	
	f[u][0] = 0;
	
	for (int i = 0; i < n; i++)
		f[u][0] = max(f[u][0], f[G[u][i].first][0] + G[u][i].second);
	
	for (int i = 0; i < n; i++) {
		int v = G[u][i].first;
		int w = G[u][i].second;
		if (i != 0) {
			L[i][0] = max(f[v][0] + w, L[i - 1][0]);
			L[i][1] = min(
				{max(f[v][0] + w, L[i - 1][1]),
				max(f[v][1] + w, L[i - 1][0]),
				max(f[v][0], L[i - 1][0])}
			);
		}
		else {
			L[i][0] = f[v][0] + w;
			L[i][1] = min(
				f[v][0],
				f[v][1] + w
			);
		}
	}
	
	for (int i = n - 1; i >= 0; i--) {
		int v = G[u][i].first;
		int w = G[u][i].second;
		if (i != n - 1) {
			R[i][0] = max(f[v][0] + w, R[i + 1][0]);
			R[i][1] = min(
				{max(f[v][0] + w, R[i + 1][1]),
				max(f[v][1] + w, R[i + 1][0]),
				max(f[v][0], R[i + 1][0])}
			);
		}
		else {
			R[i][0] = f[v][0] + w;
			R[i][1] = min(
				f[v][0],
				f[v][1] + w
			);
		}
	}
	f[u][1] = f[u][0];	
	if (n) f[u][1] = min(f[u][1], R[0][1]);
}

void dfs2(int u, int fa) {
	int n = G[u].size();
	for (int i = 0; i < n; i++) 
		L[i][0] = L[i][1] = R[i][0] = R[i][1] = oo;
		
	for (int i = 0; i < n; i++) {
		int v = G[u][i].first;
		int w = G[u][i].second;
		if (i != 0) {
			L[i][0] = max(f[v][0] + w, L[i - 1][0]);
			L[i][1] = min({
				max(f[v][0] + w, L[i - 1][1]),
				max(f[v][1] + w, L[i - 1][0]),
				max(f[v][0], L[i - 1][0])
			});
		}
		else {
			L[i][0] = f[v][0] + w;
			L[i][1] = min(
				f[v][0],
				f[v][1] + w
			);
		}
	}
	
	for (int i = n - 1; i >= 0; i--) {
		int v = G[u][i].first;
		int w = G[u][i].second;
		if (i != n - 1) {
			R[i][0] = max(f[v][0] + w, R[i + 1][0]);
			R[i][1] = min({
				max(f[v][0] + w, R[i + 1][1]),
				max(f[v][1] + w, R[i + 1][0]),
				max(f[v][0], R[i + 1][0])
			});
		}
		else {
			R[i][0] = f[v][0] + w;
			R[i][1] = min(
				f[v][0],
				f[v][1] + w
			);
		}
	}
	
	for (int i = 0; i < n; i++) {
		int v = G[u][i].first;
		int w = G[u][i].second;
		g[v][0] = max(g[u][0], max((i == 0 ? 0 : L[i - 1][0]), (i == n - 1 ? 0 : R[i + 1][0]))) + w;
		g[v][1] = g[v][0];
		g[v][1] = min(g[v][1], max(g[u][0], max((i == 0 ? 0 : L[i - 1][0]), (i == n - 1 ? 0 : R[i + 1][0]))));
		g[v][1] = min(g[v][1], max(g[u][1], max((i == 0 ? 0 : L[i - 1][0]), (i == n - 1 ? 0 : R[i + 1][0]))) + w);
		g[v][1] = min(g[v][1], max(g[u][0], max((i == 0 ? 0 : L[i - 1][1]), (i == n - 1 ? 0 : R[i + 1][0]))) + w);
		g[v][1] = min(g[v][1], max(g[u][0], max((i == 0 ? 0 : L[i - 1][0]), (i == n - 1 ? 0 : R[i + 1][1]))) + w);
	}
	
	for (auto e : G[u])
		if (e.first != fa) dfs2(e.first, u);
}

void dfs(int u, int fa) {
	for (auto e : _G[u])
		if (e.first != fa) {
			G[u].push_back(e);
			dfs(e.first, u);
		}
}

void work() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) _G[i].clear(), G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		_G[u].emplace_back(v, w);
		_G[v].emplace_back(u, w);
	}
	dfs(1, -1);
	dfs1(1, -1);
	g[1][0] = 0;
	g[1][1] = 0;
	dfs2(1, -1);
	int u = -1, ans = -1;
	/*
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 2; j++)
			printf("f[%d][%d] = %d\n", i, j, f[i][j]);
	
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 2; j++)
			printf("g[%d][%d] = %d\n", i, j, g[i][j]);
	*/
	for (int i = 1; i <= n; i++) f[i][1] = min(f[i][0], f[i][1]);
	for (int i = 1; i <= n; i++) g[i][1] = min(g[i][0], g[i][1]);
	
	for (int i = 1; i <= n; i++) {
		int tmp = min(max(g[i][0], f[i][1]), max(g[i][1], f[i][0]));
		if (ans == -1 || ans > tmp) 
			ans = tmp, u = i;
	}
	printf("%d %d\n", u, ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
/*
1

5

1 5 1
1 2 1
2 3 2
3 4 1

*/
