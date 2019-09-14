#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
bool iscandy[maxn];
vector<int>G[maxn];

struct MFS {
	int fa[maxn];
	void init(int n) {
		for (int i = 1; i <= n; i++) fa[i] = i;
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
} mfs;

bool vis[maxn];
int size[maxn];

void dfs(int u) {
	size[u] = 1;
	vis[u] = true;
	for (auto v : G[u]) {
		if (vis[v] || !iscandy[v]) continue;
		dfs(v);
		size[u] += size[v];
	}
}

void work() {
	int n, m, k; 
	scanf("%d%d%d", &n, &m, &k);
	
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i <= n; i++) iscandy[i] = true;
	mfs.init(n);
	
	for (int i = 1; i <= m; i++) {
		int a, b; scanf("%d%d", &a, &b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	
	for (int i = 1; i <= k; i++) {
		int x; scanf("%d", &x);
		iscandy[x] = false;
	}
	
	for (int u = 1; u <= n; u++) if (iscandy[u])
		for (auto v : G[u]) if (iscandy[v]) 
			mfs.merge(u, v);
	
	for (int i = 1; i <= n; i++) vis[i] = false;
	
	for (int u = 1; u <= n; u++) 
		if (iscandy[u] && !vis[u]) 
			dfs(u), size[mfs.find(u)] = size[u];
	
//	for (int i = 1; i <= n; i++) printf("(%d %d) ", i, size[mfs.find(i)]);
	
	double ans1 = size[mfs.find(1)];
	double ans2 = 0;
	for (int u = 1; u <= n; u++) if (mfs.find(1) == mfs.find(u)) 
		for (auto v : G[u]) if (!iscandy[v]) {
			double tmp = 0;
			for (auto w : G[v]) {
				if (mfs.find(w) == mfs.find(1)) continue;
				else 
					tmp += size[mfs.find(w)];
			}
			tmp = tmp / G[v].size();
			ans2 = max(ans2, tmp);
		}
	printf("%lf\n", ans1 + ans2);
}

int main() {
	int t; scanf("%d", &t);
	while (t--) work();
	return 0;
}
