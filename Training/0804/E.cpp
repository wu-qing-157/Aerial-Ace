#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

#define maxn 10010
#define maxm 100010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
typedef long long ll;
struct Edge1 {
	int to, w;
} ; std::vector<Edge1> e1[maxn];
struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], e[maxm << 2], *ecnt = e, *cur[maxn];
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
inline void link1(int a, int b, int c)
{
	e1[a].push_back((Edge1){b, c});
}
ll d[maxn];
struct Queue {
	int x; ll d;
	inline bool operator < (const Queue &that) const {return d > that.d;}
} ; std::priority_queue<Queue> qq;
ll ans;
int s, t, q[maxn], dep[maxn];
inline bool bfs()
{
	memset(dep, -1, (t + 1) << 2);
	dep[q[1] = t] = 0; int head = 0, tail = 1;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (dep[iter -> to] == -1 && iter -> rev -> cap)
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
void dinic()
{
	ans = 0;
	while (bfs())
	{
		memcpy(cur, last, (t + 1) * sizeof (Edge *));
		ans += dfs(s, 0x7fffffff);
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) e1[i].clear(), last[i] = 0;
		ecnt = e;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, c; scanf("%d%d%d", &a, &b, &c);
			link1(a, b, c);
		}
		memset(d, 63, (n + 1) << 3);
		qq.push((Queue) {1, d[1] = 0});
		while (!qq.empty())
		{
			Queue now = qq.top(); qq.pop();
			if (d[now.x] != now.d) continue;
			for (auto it : e1[now.x])
				if (d[it.to] > d[now.x] + it.w)
					d[it.to] = d[now.x] + it.w,
					qq.push((Queue) {it.to, d[it.to]});
		}
		s = 1; t = n;
		for (int i = 1; i <= n; ++i)
			for (auto it : e1[i])
				if (d[it.to] == d[i] + it.w)
					link(i, it.to, it.w);
		dinic();
		printf("%lld\n", ans);
	}
	return 0;
}
/*
2
3 4
1 2 1
2 3 1
1 3 2
1 3 3
3 4
1 2 1
2 3 1
1 3 2
1 3 3
*/
