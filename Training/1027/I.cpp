#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>

#define maxn 1010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
const int inf = 0x7fffffff;
struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], *cur[maxn], e[maxn * maxn], *ecnt = e;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
int dep[maxn], q[maxn], s, t, ans;
inline bool bfs()
{
	int head = 0, tail = 1;
	memset(dep, -1, (t + 1) << 2); dep[q[1] = t] = 0;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> rev -> cap && dep[iter -> to] == -1)
				dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
int dfs(int x, int f)
{
	if (x == t) return f;
	int used = 0;
	for (Edge* &iter = cur[x]; iter; iter = iter -> next)
		if (iter -> cap && dep[iter -> to] + 1 == dep[x])
		{
			int v = dfs(iter -> to, dmin(f - used, iter -> cap));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	return used;
}
inline void dinic()
{
	while (bfs())
	{
		memcpy(cur, last, sizeof last);
		ans += dfs(s, inf);
	}
}
int main()
{
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i)
	{
		int t; scanf("%d", &t);
		for (int j = 1; j <= t; ++j)
		{
			int x; scanf("%d", &x);
			link(i, x + n, 1);
		}
		link(n + m + 1, i, 1);
		link(s, i, 1);
	}
	s = 0; t = n + m + 2; link(s, n + m + 1, k);
	for (int i = 1; i <= m; ++i) link(i + n, t, 1);
	dinic();
	printf("%d\n", ans);
	return 0;
}
