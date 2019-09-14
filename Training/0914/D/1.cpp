#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

vector<pair<int, int> >G[maxn];

int nowSize, nowRoot;
int subSize[maxn];
int cutSize[maxn];
bool solved[maxn];

void getRoot(int u, int f) {
	subSize[u] = 1;
	cutSize[u] = 0;
	for (auto e : G[u]) {
		int v = e.first;
		if (v == f || solved[v]) continue;
		getRoot(v, u);
		cutSize[u] = max(cutSize[u], subSize[v]);
		subSize[u] += subSize[v];
	}
	cutSize[u] = max(cutSize[u], nowSize - subSize[u]);
	if (nowRoot == -1 || cutSize[nowRoot] > cutSize[u])
		nowRoot = u;
}

int getSize(int u, int f) {
	int size = 1;
	for (auto e : G[u]) {
		int v = e.first;
		if (v == f || solved[v]) continue;
		size += getSize(v, u);
	} return size;
}

const int MOD = 1e9 + 7;

ll Sum[3], Cnt[3];

int Ans[3];

void calc(int u, int f, int d) {	
	for (int i = 0; i < 3; i++) {
		int m = (d + i) % 3;
		Ans[m] = (Ans[m] + Sum[i] + 1ll * Cnt[i] * d) % MOD;
	}
	for (auto e : G[u]) {
		int v = e.first, w = e.second;
		if (v == f || solved[v]) continue;
		calc(v, u, d + w);
	}
}

void add(int u, int f, int d) {
	(Sum[d % 3] += d) %= MOD; Cnt[d % 3]++;
	for (auto e : G[u]) {
		int v = e.first, w = e.second;
		if (v == f || solved[v]) continue;
		add(v, u, d + w);
	}
}

void solve(int u) {
	solved[u] = true;
	
	for (int i = 0; i < 3; i++) Sum[i] = Cnt[i] = 0;
	Sum[0] = 0; Cnt[0] = 1;
	
	for (auto e : G[u]) {
		int v = e.first, w = e.second;
		if (solved[v]) continue;
		calc(v, u, w); add(v, u, w);
	}
	
	for (auto e : G[u]) {
		int v = e.first;
		if (solved[v]) continue;
		nowRoot = -1;
		nowSize = getSize(v, -1);
		getRoot(v, -1);
		solve(nowRoot);
	}
}

int main() {
	int n; while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i < n; i++) {
			int u, v, w; 
			scanf("%d%d%d", &u, &v, &w);
			u++, v++;
			G[u].emplace_back(v, w);
			G[v].emplace_back(u, w);
		}
		for (int i = 0; i < 3; i++) Ans[i] = 0;
		for (int i = 1; i <= n; i++) solved[i] = false;
		nowRoot = -1;
		nowSize = n;
		getRoot(1, -1);
		solve(nowRoot);
		for (int i = 0; i < 3; i++) printf("%d ", (Ans[i] << 1) % MOD);
		puts("");
	}
	return 0;
}
