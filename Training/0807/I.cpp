#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

vector<pair<int, int> >T[maxn];

map<pair<int, int>, int>W;

vector<pair<int, pair<int, int> > >E;

struct MFS {
	int f[maxn];
	void init(int n) {
		for (int i = 1; i <= n; i++) f[i] = i;
	}
	int find(int x) {
		return x == f[x] ? x : f[x] = find(f[x]);
	}
	void merge(int x, int y) {
		f[find(x)] = find(y);
	}
} mfs;

int fa[20][maxn], mx[20][maxn], dep[maxn];

void dfs(int u) {
	for (int i = 1; i < 20; i++) {
		fa[i][u] = fa[i - 1][fa[i - 1][u]];
		mx[i][u] = max(mx[i - 1][u], mx[i - 1][fa[i - 1][u]]);
	}
	for (auto e : T[u]) {
		int v = e.first;
		int w = e.second;
		if (v == fa[0][u]) continue;
		fa[0][v] = u;
		mx[0][v] = w;
		dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int ask(int u, int v) {
	int ans = 0;
	if (dep[v] > dep[u]) swap(u, v);
	for (int i = 19; i >= 0; i--) 
		if (dep[u] - dep[v] >= (1 << i)) 
			ans = max(ans, mx[i][u]), u = fa[i][u];	
	assert(dep[v] == dep[v]);
	for (int i = 19; i >= 0; i--)
		if (fa[i][u] != fa[i][v]) {
			ans = max(ans, mx[i][v]);
			ans = max(ans, mx[i][u]);
			u = fa[i][u];
			v = fa[i][v];
		}
	if (u == v)	return ans;
	else {
		ans = max(ans, mx[0][u]);
		ans = max(ans, mx[0][v]);
		return ans;
	}
}

int main() {
	int n, m; scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (u > v) swap(u, v);
		W[make_pair(u, v)] = w;
		E.push_back(make_pair(w, make_pair(u, v)));
	}
	
	sort(E.begin(), E.end());
	
	mfs.init(n);
	
	long long ans = 0;
	
	for (auto e : E) {
		int w = e.first;
		int u = e.second.first, v = e.second.second;
		if (mfs.find(u) != mfs.find(v)) {
			T[u].push_back(make_pair(v, w));
			T[v].push_back(make_pair(u, w));
			mfs.merge(u, v), ans += w;
		}
	}
	
	dfs(1);
	
	int q; scanf("%d", &q);
	while (q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		int tmp = ask(u, v);
		printf("%lld\n", ans - tmp + W[make_pair(u, v)]);
	}
	return 0;
}
