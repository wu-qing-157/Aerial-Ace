#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>

#define maxn 10010
struct edge {int a, b;} v[2][maxn];
std::vector<int> e[2][maxn];
int dfn[2][maxn], pos[2][maxn], timer;
int fa[2][maxn][20], dep[2][maxn];
int mark[maxn], size[maxn], near[maxn];
void dfs(int x, int t)
{
	dfn[t][x] = ++timer; pos[t][timer] = x;
	if (!t) size[x] = 1;
	for (int i = 1; i <= 14; ++i)
		fa[t][x][i] = fa[t][fa[t][x][i - 1]][i - 1];
	for (int to : e[t][x])
	{
		fa[t][to][0] = x;
		dep[t][to] = dep[t][x] + 1;
		dfs(to, t);
		if (!t) size[x] += size[to];
	}
}
int ans[maxn], con_cnt;
int ff[maxn], ss[maxn], st[maxn], top;
void link(int u, int v)
{
	while (ff[u]) u = ff[u];
	while (ff[v]) v = ff[v];
	if (u == v) return ;
	if (size[u] > size[v]) std::swap(u, v);
	st[++top] = u;
	ff[u] = v;
	ss[v] += ss[u];
	--con_cnt;
}
void redo(int last_top)
{
	while (top > last_top)
	{
		int now = st[top--];
		ss[ff[now]] -= ss[now];
		ff[now] = 0;
		++con_cnt;
	}
}
void dfs_calc(int x, int col)
{
	int org = top;
	link(v[1][x].a, v[1][x].b);
	if (near[x] == col)
	{
		int ntop = top;
		for (int poi = x; poi != col; poi = fa[0][poi][0])
			link(v[0][poi].a, v[0][poi].b);
		ans[x] = con_cnt;
		redo(ntop);
	}
	for (int to : e[1][x])
		dfs_calc(to, col);
	redo(org);
}
void dfs(int x)
{
	int org = top;
	link(v[0][x].a, v[0][x].b);
	if (near[x] == x)
		dfs_calc(1, x);
	for (int to : e[0][x])
		dfs(to);
	redo(org);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		memset(mark, 0, (n + 1) << 2);
		memset(ff, 0, (m + 1) << 2);
		for (int i = 1; i <= m; ++i) ss[i] = 1;
		for (int j = 0; j < 2; ++j)
		{
			for (int i = 1; i <= n; ++i) scanf("%d%d", &v[j][i].a, &v[j][i].b), e[j][i].clear();
			for (int i = 1; i < n; ++i)
			{
				int a, b; scanf("%d%d", &a, &b);
				e[j][a].push_back(b);
			}
		}
		timer = 0; dfs(1, 0); timer = 0; dfs(1, 1);
		int D = std::sqrt(n), mcnt = 0;
		for (int i = 1; i <= n; ++i)
			if (dep[0][i] % D == 0 && size[i] >= D)
				mark[i] = ++mcnt;
		for (int i = 1, x; i <= n; ++i)
		{
			x = pos[0][i];
			near[x] = mark[x] ? x : near[fa[0][x][0]];
		}
		con_cnt = m;
		dfs(1);
		for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
/*
2
3 4
1 2
2 3
3 4
1 2
1 3
1 3
2 4
3 4
1 2
2 3
2 100
100 99
99 98
1 2
97 96
95 94
1 2
*/
