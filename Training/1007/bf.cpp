#include <cstdio>
#include <cstring>

#define maxn 23333
int c[maxn];
struct Edge {
	Edge *next;
	int to, w;
} *last[maxn], e[maxn], *ecnt = e;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w}; last[b] = ecnt;
}
bool vis[maxn];
int cnt[maxn];
int ans, ans_id;
void dfs(int x, int w)
{
	++cnt[c[x]];
	if (cnt[c[x]] > ans || (cnt[c[x]] == ans && c[x] < ans_id))
		ans = cnt[c[x]], ans_id = c[x];
	vis[x] = 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> w <= w && !vis[iter -> to])
			dfs(iter -> to, w);
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m; scanf("%d%d",&n, &m);
		for (int i = 1; i <= n; ++i) scanf("%d", c + i);
		memset(last, 0, sizeof last); ecnt = e;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			link(a, b, w);
		}
		int q; scanf("%d", &q);
		printf("Case #%d:\n", Cas);
		for (; q; --q)
		{
			int x, w; scanf("%d%d", &x, &w);
			memset(vis, 0, sizeof (vis)); ans = ans_id = 0;
			memset(cnt, 0, sizeof (cnt));
			dfs(x, w);
			printf("%d\n", ans_id);
		}
	}
	return 0;
}
/*
1
5 6
2 1 1 3 2
1 2 2
1 3 4
2 3 7
3 4 5
4 5 6
5 3 3
4
1 1
2 2
4 4
5 8
*/
