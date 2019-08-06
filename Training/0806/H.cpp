#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 1010
#define maxm 100010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
const int inf = 0x7fffffff;
typedef long long ll;
struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], e[maxm << 1], *ecnt = e, *cur[maxn];
inline void link(int a, int b, int w)
{
	//printf("%d %d %d\n", a, b, w);
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
int s, t, dep[maxn];
ll ans;
int q[maxn];
inline bool bfs()
{
	memset(dep, -1, (t + 1) << 2);
	int head = 0, tail = 1; dep[q[1] = t] = 0;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> rev -> cap && dep[iter -> to] == -1)
				dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
ll dfs(int x, ll f)
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
	int n, m;
	const int d = 4e6;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		memset(last, 0, sizeof last); ecnt = e;
		for (int i = 1; i <= n; ++i) link(i, i + n, inf);
		s = 0; t = n << 1 | 1;
		ans = - 2ll * d * m;
		for (int i = 1; i <= m; ++i)
		{
			int u, v, a, b, c; scanf("%d%d%d%d%d", &u, &v, &a, &b, &c);
			link(s, u, d - a / 2);
			link(s, v, d - a / 2);
			link(u + n, t, d - (c - c / 2));
			link(v + n, t, d - (c / 2));
			link(v, u + n, a / 4 + c / 2 - c / 3);
			link(u, v + n, a / 4 + 2 * c / 3 - c / 2);
		}
		dinic();
		printf("%lld\n", -ans);
	}
	return 0;
}
