#include <cstdio>
#include <cstring>

#define maxn 100010
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn << 2], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
struct edge {int a, b, w; } ee[maxn];
int n, m, u, L, K;
int dis[maxn], q[maxn];
inline bool check(int x)
{
	memset(last, 0, (n + 2) * sizeof (Edge *)); ecnt = e;

	for (int i = 1; i <= m; ++i)
		if (ee[i].w < x) link(ee[i].a, ee[i].b);
		else link(ee[i].a, n + 1), link(ee[i].b, n + 1);

	int head = 0, tail = 1;
	memset(dis, 63, (n + 2) << 2);
	dis[q[1] = u] = 0;
	while (head < tail)
	{
		int now = q[++head];
		//printf("%d\n", now);
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (dis[iter -> to] > dis[now] + 1)
				dis[q[++tail] = iter -> to] = dis[now] + 1;
	}
	return dis[n + 1] <= K - 1;
}
int main()
{
freopen("path.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d%d%d%d%d", &n, &m, &u, &L, &K);
		
		int eecnt = 0;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			ee[++eecnt] = (edge) {a, b, w};
		}
		int left = 0, right = 1000000001;
		while (left < right)
		{
			int mid = left + right >> 1;
			//printf("%d %d\n", left, right);
			if (check(mid)) left = mid + 1;
			else right = mid;
		}
		printf("%d\n", left - 1);
	}
	return 0;
}
/*
2
5 5 2 7 2
2 1 71
2 3 88
2 4 50
1 5 95
4 3 104
2 1 2 100 70
2 1 7
*/
