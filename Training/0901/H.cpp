#include <cstdio>
#include <cstring>

typedef long long ll;
#define maxn 310
#define maxm 2333
struct Edge {
	Edge *next;
	int to; ll w;
} *last[maxn], e[maxm], *ecnt = e;
inline void link(int a, int b, ll w)
{
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
}
ll dis[maxn];
int q[maxn * maxn];
void spfa(int s)
{
	memset(dis, 63, sizeof (dis));
	dis[s] = 0; int head = 0, tail = 1; q[1] = s;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (dis[iter -> to] > dis[now] + iter -> w)
				dis[q[++tail] = iter -> to] = dis[now] + iter -> w;
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		memset(last, 0, sizeof last); ecnt = e;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			link(a, b, w);
		}
		for (int i = 1; i <= 6; ++i)
		{
			int s, t; scanf("%d%d", &s, &t);
			spfa(t);
			link(s, t, -dis[s]);
			printf("%lld\n", -dis[s]);
		}
	}
	return 0;
}
