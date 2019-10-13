#include <bits/stdc++.h>

const int maxn = 1e5 + 10;

std::vector<int>G[maxn];

namespace Tree {
	int dep[maxn], top[maxn], fa[maxn], son[maxn], size[maxn];

	void dfs1(int u) {
		size[u] = 1; son[u] = 0;
		for (auto v : G[u]) {
			if (v == fa[u]) continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v);
			size[u] += size[v];
			if (size[son[u]] < size[v])
				son[u] = v;
		}
	}

	void dfs2(int u, int t) {
		top[u] = t;
		if (son[u]) dfs2(son[u], t);
		for (auto v : G[u]) {
			if (v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}

	void init(int n) {
		memset(fa + 1, 0, n << 2);
		dfs1(1);
		dfs2(1, 1);
	}
	
	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
			u = fa[top[u]];
		} return dep[u] < dep[v] ? u : v;
	}
	
	int dis(int u, int v) {
		return dep[u] + dep[v] - dep[lca(u, v)] * 2 + 1;
	}
	int dis(std::pair<int, int>p) {
		return dis(p.first, p.second);
	}
	
	std::pair<int, int>merge(std::pair<int, int>d1, std::pair<int, int>d2) {
		static int p[4];
		p[0] = d1.first, p[1] = d1.second;
		p[2] = d2.first, p[3] = d2.second;
		
		//for (int i = 0; i < 4; i++) std::cout << p[i] << ' '; std::cout << std::endl;
		
		int now = 0, u = 0, v = 0; 
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < i; j++) {
				int tmp; if (!p[i] || !p[j]) continue;
				if ((tmp = dis(p[i], p[j])) >= now)
					u = p[i], v = p[j], now = tmp;
			}
		return std::make_pair(u, v);
	}
}

std::pair<int, int>d1[maxn], d2[maxn];

void getD1(int u, int f) {
	d1[u] = std::make_pair(u, u);
	for (int v : G[u]) {
		if (v == f) continue;
		getD1(v, u);
		d1[u] = Tree::merge(d1[u], d1[v]);
	}
}

void getD2(int u, int f) {
	std::pair<int, int>dnow = Tree::merge(d2[u], std::make_pair(u, u));
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == f) continue;
		d2[v] = Tree::merge(d2[v], dnow);
		dnow = Tree::merge(dnow, d1[v]);
	}
	dnow = Tree::merge(d2[u], std::make_pair(u, u));
	for (int i = G[u].size() - 1; i >= 0; i--) {
		int v = G[u][i];
		if (v == f) continue;
		d2[v] = Tree::merge(d2[v], dnow);
		dnow = Tree::merge(dnow, d1[v]);
	}
	for (auto v : G[u]) if (v != f) getD2(v, u);
}

int maxlen[maxn];

void work() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	Tree::init(n);
	
	memset(d1 + 1, 0, sizeof(d1[0]) * n);
	memset(d2 + 1, 0, sizeof(d2[0]) * n);
	getD1(1, -1);
	getD2(1, -1);
	
	memset(maxlen + 1, 0, n << 2);
	
	for (int i = 2; i <= n; i++) {
		int L1 = Tree::dis(d1[i]);
		int L2 = Tree::dis(d2[i]);
		
		maxlen[L1] = std::max(maxlen[L1], L2);
		maxlen[L2] = std::max(maxlen[L2], L1);
	}
	long long ans = 0;
	for (int i = n - 1; i >= 1; i--)
		maxlen[i] = std::max(maxlen[i], maxlen[i + 1]);
	
	//for (int i = 1; i <= n; i++)
	//	printf("%d %d\n", i, maxlen[i]);
		
	//for (int i = 1; i <= n; i++) 
	//	if (maxlen[i] >= i) ans--;

	for (int i = 1; i <= n; i++)
		ans += maxlen[i];
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
/*
3
4
1 2
1 3
1 4
5
1 2
2 3
3 4
3 5
5
1 2
1 5
2 3
2 4
*/
