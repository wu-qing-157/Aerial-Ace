#include <cstdio>

#define maxn 100010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
struct Edge {
	Edge *next;
	int to, id;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b, int id)
{
	*++ecnt = (Edge) {last[a], b, id}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, id}; last[b] = ecnt;
}
int w[maxn];
ll dis[maxn], ans;
void dfs(int x, int fa = 0)
{
	cmax(ans, dis[x]);
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa)
		{
			dis[iter -> to] = dis[x] + w[iter -> id];
			dfs(iter -> to, x);
		}
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d%d", &a, &b, w + i);
		link(a, b, i);
	}
	int q; scanf("%d", &q);
	for (; q; --q)
	{
		char opt[2]; scanf("%s", opt);
		if (opt[0] == 'Q')
		{
			int x; scanf("%d", &x); dis[x] = ans = 0;
			dfs(x);
			printf("%lld\n", ans);
		}
		else
		{
			int e, _w; scanf("%d%d", &e, &_w);
			w[e] = _w;
		}
	}
	return 0;
}
