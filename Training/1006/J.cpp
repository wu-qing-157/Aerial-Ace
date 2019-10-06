#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 250010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
typedef long long ll;
struct Edge {
	Edge *next, *rev;
	int to, cap, id;
} *last[maxn], e[maxn << 2], *ecnt = e, *cur[maxn];
inline void link(int a, int b, int w, int id)
{
	// printf("%d %d %d %d\n", a, b, w, id);
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w, id}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0, id}; last[b] = ecnt;
}
const int inf = 0x7fffffff;
int s, t, q[maxn], dep[maxn];
inline bool bfs()
{
	int head = 0, tail = 1;
	memset(dep, -1, (t + 1) << 2);
	dep[q[1] = t] = 0;
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
			int v = dfs(iter -> to, dmin(iter -> cap, f - used));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	return used;
}
ll ans;
inline void dinic()
{
	while (bfs())
	{
		memcpy(cur, last, sizeof cur);
		ans += dfs(s, inf);
	}
}
int fff[maxn];
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	s = 0; t = n << 1 | 1;
	for (int i = 1; i <= n; ++i)
		link(s, i, n, 0), link(i + n, t, n - 1, 0);
	for (int i = 1; i <= m; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b + n, inf, i);
	}
	dinic();
	if (ans != 1ll * n * (n - 1)) puts("-1");
	else
	{
		for (int i = 1; i <= n; ++i)
			for (Edge *iter = last[i + n]; iter; iter = iter -> next)
				if (iter -> id)
					fff[iter -> id] = iter -> cap;
		for (int i = 1; i <= m; ++i)
			printf("%d\n", fff[i]);
	}
	return 0;
}
