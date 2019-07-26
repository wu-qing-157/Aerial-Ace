#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 10;

int cnt[maxn], siz[maxn], allcnt, M;
long long ds[maxn], df[maxn], dp[maxn][500 + 10];

vector<pair<int, int> >G[maxn];
pair<int, int>fa[maxn];

void dfs1(int u) {
	ds[u] = 0;
	for (auto e : G[u])	{
		if (e == fa[u]) continue;
		int v = e.first;
		fa[v] = make_pair(u, e.second);
		dfs1(v);
		cnt[u] += cnt[v];
		ds[u] += ds[v] + 1ll * e.second * cnt[v];
	}
}

void dfs2(int u) {
	for (auto e : G[u]) {
		if (e == fa[u]) continue;
		int v = e.first;
		df[v] = df[u] + ds[u] - ds[v] + 1ll * (allcnt - cnt[v] * 2) * e.second;
		dfs2(v);
	}
}

void dfs3(int u) {
	for (int i = 1; i <= M; i++) dp[u][i] = ds[u];
	siz[u] = 1;
	for (auto e : G[u]) {
		if (e == fa[u]) continue;
		int v = e.first;
		dfs3(v);
		for (int s1 = siz[u]; s1 >= 1; s1--)
			for (int s2 = siz[v]; s2 >= 1; s2--) {
				if (s1 + s2 > M) continue;
				dp[u][s1 + s2] = min(dp[u][s1 + s2], dp[u][s1] + dp[v][s2] - ds[v] - 1ll * e.second * cnt[v]);
			}
		siz[u] = min(siz[u] + siz[v], M);
	}
}

void work(int n, int m) {
	M = m;
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i <= n; i++) fa[i] = make_pair(0, 0);
	for (int i = 1; i <= n; i++) scanf("%d", &cnt[i]);
	for (int i = 1; i <= n - 1; i++) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	dfs1(1);
	allcnt = cnt[1];
	df[1] = 0;
	dfs2(1);
	dfs3(1);
	long long ans = dp[1][m] + df[1];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			dp[i][m] = min(dp[i][j], dp[i][m]);
	
	for (int i = 1; i <= n; i++) 
		ans = min(ans, dp[i][m] + df[i]);

	printf("%lld\n", ans);
	/*
	printf("allcnt = %d\n", allcnt);
	
	for (int i = 1; i <= n; i++) {
		printf("(df[%d] = %lld, ds[%d] = %lld, cnt[%d] = %lld)\n", i, df[i], i, ds[i], i, cnt[i]);
		for (int j = 1; j <= m; j++)
			printf("dp[%d][%d] = %lld ", i, j, dp[i][j]);
		printf("\n");
	}
	*/
	
}

int main() {
	int n, m, t = 0;  
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0)
			break;
		printf("Case %d: ", ++t);
		work(n, m);
	}
	return 0;
}
/*
3 1
1 2 3
1 2 2
1 3 3
3 2
100 10 100
1 2 1
2 3 1
5 1
1 1 1 1 1
1 2 1
2 3 1
3 4 1
4 5 1
3 1
1 2 3
1 2 2
1 3 3
3 2
100 10 100
1 2 1
2 3 1
0 0
*/
