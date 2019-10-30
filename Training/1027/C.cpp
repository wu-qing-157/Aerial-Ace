#include <bits/stdc++.h>
using namespace std;

vector<int>G[maxn];

namespace HLD {
	int size[maxn], dep[maxn], fa[maxn][20], top[maxn], son[maxn];	
	void dfs1(int u) {
		size[u] = 1;
		for (int t = 1; t < 20; t++)
			fa[u][t] = u[fa][t - 1][fa][t - 1];
		for (auto v : G[u]) {
			if (v == fa[u][0]) continue;
			fa[v][0] = u;
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
			if (v == fa[u][0] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	
	int lca(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v);
			u = fa[top[u]][0];
		} return dep[u] < dep[v] ? u : v;
	}
	
	void init() {	
		dfs1(1);
		dfs2(1, 1);
	}
	
	int go(int u, int v) {
		if (u == v) return v;
		else {
			int w = lca(u, v);
			if (w != u) return fa[u];
			else {
				int d = dep[v] - dep[w] - 1;
				for (int i = 0; i < 20; i++)
					if (d >> i & 1) v = fa[v][i];
				return v;
			}
		}
	}
	int g[maxn], rg[maxn];	
	
	int maxs(int u, int all) {
		return max(size[son[u]], all - size[u]);
	}
	
	int merge(int u, int v, int all) {
		int w = lca(u, v);
		if (u != w) {
			for (int i = 19; i >= 0; i--) {
				if (1 << i >= dep[u] - dep[w]) continue;
				int u1 = fa[u][i], u2 = fa[u1][0];
				if (maxs(u1, all) > mas(u2, all))
					u = u1;
			}
			if (maxs(u, all) > maxs(fa[u][0], all)) 
				u = fa[u][0];
		}
		if (v != w) {
			for (int i = 19; i >= 0; i--) {
				if (1 << i >= dep[v] - dep[w]) continue;
				int v1 = fa[v][i], v2 = fa[v1][0];
				if (maxs(v1, all) > mas(v2, all))
					v = v1;
			}
			if (maxs(v, all) > maxs(fa[v][0], all)) 
				v = fa[v][0];
		}
		if (v == w) return u;
		if (u == w) return v;
		assert(0);
	}
	
	int merge2(int u, int v, int all) {
		
	}
	
	void getg(int u) {
		int nows = 1;
		g[u] = u;
		for (auto v : G[u]) {
			if (v == fa[u][0]) continue;
			getg(v);
			nows += size[v];
			g[u] = merge(g[u], g[v], nows);
		}
	}
	
	
	
	void getrg(int u) {
		int nowg = u;
		
		for (auto v : G[u]) {
			
		}
	}
	
	void solve(int n) {
		init();	
		getg(1);
		getrg(1);
	}
}



int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	HLD::solve(n);
}

