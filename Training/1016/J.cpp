#include <cstdio>
#include <algorithm>
#include <cstring>

#define maxn 2010
typedef long long ll;
struct Edge {
	Edge *next;
	int to, w;
} *last[maxn], e[maxn * maxn], *ecnt = e;
inline void link(int a, int b, int w)
{
	// printf("%d %d %d\n", a, b, w);
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
}
bool ins[maxn];
ll dis[maxn];
bool flag;
void dfs(int x)
{
	ins[x] = 1;
	for (Edge *iter = last[x]; iter && !flag; iter = iter -> next)
		if (dis[iter -> to] > dis[x] + iter -> w)
		{
			if (!ins[iter -> to])
			{
				dis[iter -> to] = dis[x] + iter -> w;
				dfs(iter -> to);
			}
			else flag = 1;
		}
	ins[x] = 0;
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n, m, X; scanf("%d%d%d", &n, &m, &X);
		memset(last, 0, sizeof last); ecnt = e;
		memset(ins, 0, sizeof (ins));
		for (int i = 1; i <= m; ++i)
		{
			int A, B, C, D; scanf("%d%d%d%d", &A, &B, &C, &D);
			if (A == B && C == D)
			{
				link(C, A, -X);
				link(A, C, X);
			}
			else
			{
				link(B, C, X - 1);
				link(D, A, -1 - X);
			}
		}
		for (int i = 1; i <= n; ++i) link(i + 1, i, -1);
		for (int i = 1; i <= n; ++i) link(0, i, 0);
		memset(dis, 63, (n + 1) << 3);
		dis[0] = 0; flag = 0; dfs(0);
		printf("Case #%d: ", Cas);
		if (flag)
		{
			puts("IMPOSSIBLE");
			continue;
		}
		for (int i = n; i > 1; --i) dis[i] -= dis[i - 1];
		for (int i = 2; i <= n; ++i) printf("%lld%c", dis[i], " \n"[i == n]);
	}
	return 0;
}
