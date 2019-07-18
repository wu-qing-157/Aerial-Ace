#include <cstdio>
#include <algorithm>

#define maxn 20010
#define maxm 100010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
struct edge {int a, b;} ee[maxm];
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dep[maxn], fa[maxn], dfn[maxn], low[maxn], timer;
bool vis[maxn];
void dfs1(int x)
{
	vis[x] = 1; dep[x] = dep[fa[x]] + 1; dfn[x] = ++timer;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!vis[iter -> to]) {fa[iter -> to] = x; dfs1(iter -> to);}
}
struct Heap {
	Heap *ch[2];
	int val, size;
	inline void update() {size = ch[0] -> size + ch[1] -> size + 1;}
} mem[maxn], *tot = mem, *rt[maxn];
Heap *merge(Heap *a, Heap *b)
{
	if (a == mem) return b;
	if (b == mem) return a;
	if (a -> val > b -> val) std::swap(a, b);
	std::swap(a -> ch[0], a -> ch[1]);
	a -> ch[1] = merge(a -> ch[1], b);
	a -> update();
	return a;
}
int ans;
void dfs2(int x)
{
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa[x])
		{
			dfs2(iter -> to);
			rt[x] = merge(rt[x], rt[iter -> to]);
		}
	//printf("%d %d\n", x, rt[x] -> size);
	if (rt[x] -> size > 1 && rt[x] -> val < dfn[x])
	{
//		puts("K");
		Heap *tmp = rt[x];
		rt[x] = merge(rt[x] -> ch[0], rt[x] -> ch[1]);
		tmp -> ch[0] = tmp -> ch[1] = mem; tmp -> size = 1;

		rt[x] -> val >= dfn[x] ? ++ans : 0;
		//printf("v %d v %d\n", rt[x] -> val, tmp -> val);
		rt[x] = merge(rt[x], tmp);
	}
	else if (x != 1) ++ans;
}
int main()
{
	freopen("diversion.in", "r", stdin);
	freopen("diversion.out", "w", stdout);
	int n, m; scanf("%d%d", &n, &m);
	int eecnt = 0;
	mem -> ch[0] = mem -> ch[1] = mem;
	for (int i = 1; i <= n; ++i) rt[i] = mem;
	for (int i = 1; i <= m; ++i)
	{
		int a, b, w; scanf("%d%d%d", &a, &b, &w);
		if (w) link(a, b);
		else ee[++eecnt] = (edge) {a, b};
	}
	dfs1(1);
	for (int i = 1; i <= eecnt; ++i)
	{
		if (dfn[ee[i].a] < dfn[ee[i].b]) std::swap(ee[i].a, ee[i].b);
		//printf("a %d b %d\n", ee[i].a, ee[i].b);
		*++tot = (Heap) {mem, mem, dfn[ee[i].b], 1};
		rt[ee[i].a] = merge(rt[ee[i].a], tot);
	}
	dfs2(1);
	printf("%d\n", ans);
	return 0;
}
/*
6 7
1 2 1
2 3 1
1 4 0
3 4 1
4 5 1
3 6 0
5 6 1

*/
