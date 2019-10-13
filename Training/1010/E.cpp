#include <cstdio>
#include <cstring>

#define maxn 110
#define maxp 60010
#define maxm 1000010
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
const int inf = 0x7fffffff;
struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxp], e[maxm], *ecnt = e, *cur[maxp];
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
int s, t, ans, dep[maxp], q[maxp];
inline bool bfs()
{
	memset(dep, -1, (t + 1) << 2);
	int head = 0, tail = 1; dep[q[1] = t] = 0;
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
	ans = 0;
	while (bfs())
	{
		memcpy(cur, last, sizeof cur);
		ans += dfs(s, inf);
	}
}
char mp[maxn][maxn];
int id[maxn][maxn][2][2];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, a, b; scanf("%d%d%d%d", &n, &m, &a, &b);
		for (int i = 1; i <= n; ++i) scanf("%s", mp[i] + 1);
		s = t = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				for (int ii = 0; ii < 2; ++ii)
					for (int jj = 0; jj < 2; ++jj)
						id[i][j][ii][jj] = ++t;
		++t;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				link(id[i][j][0][0], id[i][j][0][1], 1);
				link(id[i][j][1][0], id[i][j][1][1], 1);
				link(id[i][j][0][1], id[i][j][1][0], 1);
				link(id[i][j][1][1], id[i][j][0][0], 1);
				
				for (int ii = -1; ii <= 1; ii += 2)
				{
					int x = i + ii, y = j;
					if (x && x <= n && y && y <= m && mp[x][y] != '1')
						link(id[i][j][0][1], id[x][y][0][0], 1);
				}
				for (int ii = -1; ii <= 1; ii += 2)
				{
					int x = i, y = j + ii;
					if (x && x <= n && y && y <= m && mp[x][y] != '1')
						link(id[i][j][1][1], id[x][y][1][0], 1);
				}
			}
		for (int i = 1; i <= a; ++i)
		{
			int p; scanf("%d", &p);
			link(s, id[1][p][0][0], 1);
		}
		for (int i = 1; i <= b; ++i)
		{
			int p; scanf("%d", &p);
			link(id[n][p][0][1], t, 1);
		}
		dinic();
		puts(ans == a ? "Yes" : "No");
		
		memset(last, 0, (t + 1) * sizeof (Edge *)); ecnt = e;
	}
	return 0;
}
