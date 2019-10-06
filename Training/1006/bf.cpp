#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define maxn 80010
#define maxm 300010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
typedef long long ll;
int A[maxn], B[maxn], C[maxn], Q;
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
int dfn[maxn], timer, pos[maxn], inv[maxn], fa[maxn], n;
void dfs(int x)
{
	dfn[x] = ++timer; pos[timer] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (!dfn[iter -> to]) fa[iter -> to] = x, dfs(iter -> to);
	inv[x] = timer;
}
int main()
{
	int qq; scanf("%d%d", &n, &qq);
	for (int i = 1; i <= n; ++i) scanf("%d", A + i);
	for (int i = 1; i <= n; ++i) scanf("%d", B + i);
	for (int i = 1; i <= n; ++i) scanf("%d", C + i);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		link(a, b);
	}
	dfs(1);
	for (int i = 1; i <= qq; ++i)
	{
		int v, t; scanf("%d%d", &v, &t);
		ll ans = ~0ULL >> 1;
		for (int f = v; f; f = fa[f])
			if (t <= C[f]) cmin(ans, A[f] + 1ll * B[f] * t);
		printf("%lld\n", ans);
	}
	return 0;
}
