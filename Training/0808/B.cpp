#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 100010
#define maxm 200010
struct Edge {
	Edge *next;
	int to;
} ;
Edge *last[maxn], e[maxm], *ecnt = e;
Edge *rlast[maxn], re[maxm], *recnt = re;
int deg[maxn], q[maxn], fa[maxn][20], all_fa[maxn], fa_cnt, dep[maxn];
inline void link(int a, int b) 
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt; ++deg[b];
}
inline void link_rev(int a, int b)
{
	*++recnt = (Edge) {rlast[a], b}; rlast[a] = recnt;
}
inline int getlca(int a, int b)
{
	if (dep[a] < dep[b]) std::swap(a, b);
	int temp = dep[a] - dep[b];
	for (int i; temp; temp -= 1 << i)
		a = fa[a][i = __builtin_ctz(temp)];
	for (int i = 16; ~i; --i)
		if (fa[a][i] != fa[b][i])
			a = fa[a][i], b = fa[b][i];
	if (a == b) return a;
	return fa[a][0];
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		memset(last, 0, sizeof last); ecnt = e;
		memset(rlast, 0, sizeof rlast); recnt = re;
		memset(fa, 0, sizeof (fa));
		for (int i = 1; i <= m; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(b, a); link_rev(a, b);
		}
		for (int i = 1; i <= n; ++i) if (!deg[i]) link(0, i), link_rev(i, 0);
		q[1] = 0; dep[0] = 0;
		int head = 0, tail = 1;
		while (head < tail)
		{
			int now = q[++head];
			fa_cnt = 0;
			for (Edge *iter = rlast[now]; iter; iter = iter -> next)
				all_fa[++fa_cnt] = iter -> to;
			for (; fa_cnt > 1; --fa_cnt)
				all_fa[fa_cnt - 1] = getlca(all_fa[fa_cnt], all_fa[fa_cnt - 1]);
			fa[now][0] = all_fa[fa_cnt];
			//printf("link %d %d\n", fa[now][0], now);
			dep[now] = dep[all_fa[fa_cnt]] + 1;
			
			for (int i = 1; i <= 16; ++i)
				fa[now][i] = fa[fa[now][i - 1]][i - 1];
			for (Edge *iter = last[now]; iter; iter = iter -> next)
				if (--deg[iter -> to] == 0) q[++tail] = iter -> to;
		}
		//for (int i = 0; i <= n; ++i) printf("%d ", dep[i]); puts("");
		int q; scanf("%d", &q);
		for (; q; --q)
		{
			int u, v; scanf("%d%d", &u, &v);
			printf("%d\n", dep[u] + dep[v] - dep[getlca(u, v)] - 1);
		}
	}
	return 0;
}
