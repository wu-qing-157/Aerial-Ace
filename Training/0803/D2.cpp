#include <bits/stdc++.h>
using namespace std;
namespace LCA {
	vector<int>G[maxn];
	int dfn[maxn], dep[maxn], pos[maxn], dfc;
	void clear(int n) {
		for (int i = 1; i <= n; i++) G[i].clear();
		dfc = 0;
	}	
	void dfs(int u, int f) {
		dfn[++dfc] = u; pos[u] = dfc;
		for (int v : G[u]) 
			if (v == f) continue;
			else {
				dep[v] = dep[u] + 1;
				dfs(v, u);
				dfn[++dfc] = u;
			}
	}
	
	int st[23][maxn], ln[maxn];
	
	void build(int n) {
		for (int i = 1; i <= dfc; i++) st[0][i] = dfn[i];
		for (int j = 1; j < 23; j++) 
			for (int i = 1; i + (1 << j) - 1 <= dfc; i++)
				st[j][i] = dep[st[j - 1][i]] < dep[st[j - 1][i + (1 << (j - 1))]] ? 
							st[j - 1][i] : st[j - 1][i + (1 << (j - 1))];
		ln[0] = -1;
		for (int i = 1; i <= dfc; i++) ln[i] = ln[i >> 1] + 1;
	}
	int ask(int u, int v) {
		u = pos[u]; v = pos[v];
		if (u > v) swap(u, v);
		int k = ln(v - u + 1);
		u = st[k][u]; v = st[k][v - (1 << k) + 1];
		return dep[v] < dep[u] ? v : u;
	}
	
	
}
