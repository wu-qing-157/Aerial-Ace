#include <cstdio>
#include <vector>

#define maxn 25010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], ee[maxn << 1], *ecnt = ee;
struct edge {
	int a, b;
} e[maxn];
struct e2 {int to, id;}
std::vector<e2> v[maxn];
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dfn[maxn], low[maxn], timer, st[maxn], top, col[maxn], colcnt, r[maxn];
inline bool cmp(int a, int b) {return col[a] < col[b];}
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer; st[++top] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
			}
			else if (!id[iter -> to]) cmin(low[x], dfn[iter -> to]);
		}
	if (dfn[x] == low[x])
	{
		++colcnt; bool flag = 1;
		for (; ;)
		{
			int now = st[top--];
			col[now] = colcnt;
			if (now == x) break;
		}
	}
}
int main()
{
	int n, m, k; scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b); link(a, b);
		e[i] = (edge) {a, b};
	}
	tarjan(1, 0);

	for (int i = 1; i <= n; ++i) r[i] = i;
	std::sort(r + 1, r + n + 1, cmp);
	for (int i = 1; i < n; ++i)
		if (col[e[i].a] != col[e[i].b])
			v[col[e[i].a]].push_back((e2) {col[e[i].b], i}),
			v[col[e[i].b]].push_back((e2) {col[e[i].a], i});
	for (int i = 1, j = 1; i <= colcnt; ++i)
	{
		while (j <= n && col[r[j]] == i) ;
		for (e2 it : v[i])
			if (it.to > i)
			{
			}
	}
	return 0;
}
