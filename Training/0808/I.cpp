#include <cstdio>
#include <cstring>
#include <vector>

#define maxn 5010
#define maxm 4000010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
const int inf = 0x7fffffff;
typedef long long ll;
struct Edge {
	Edge *next, *rev;
	int from, to, cap, cost;
} *last[maxn], *prev[maxn], e[maxm], *ecnt = e;
int s, t, q[maxm], dis[maxn], a[maxn];
ll ans;
bool inq[maxn];
inline void link(int a, int b, int w, int c)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, a, b, w, c}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, b, a, 0, -c}; last[b] = ecnt;
}
inline bool spfa()
{
	int head = 0, tail = 1;
	for (int i = 1; i <= t; ++i) dis[i] = inf;
	dis[q[1] = s] = 0;
	while (head < tail)
	{
		int now = q[++head]; inq[now] = 0;
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> cap && dis[iter -> to] > dis[now] + iter -> cost)
			{
				dis[iter -> to] = dis[now] + iter -> cost;
				prev[iter -> to] = iter;
				!inq[iter -> to] ? inq[q[++tail] = iter -> to] = 1 : 0;
			}
	}
	return dis[t] != inf;
}
inline void mcmf()
{
	int x = inf;
	for (Edge *iter = prev[t]; iter; iter = prev[iter -> from]) cmin(x, iter -> cap);
	for (Edge *iter = prev[t]; iter; iter = prev[iter -> from])
	{
		iter -> cap -= x;
		iter -> rev -> cap += x;
		ans += 1ll * x * iter -> cost;
	}
}
int st[maxn], top;
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, k; scanf("%d%d", &n, &k);
		memset(last, 0, sizeof last); ecnt = e;
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			link(i, i + n, 1, -a[i]);
			link(i, i + n, inf, 0);
		}
		for (int i = 1; i <= n; ++i)
		{
			int maxx = -1, ccnt = 0;
			for (int j = i + 1; j <= n; ++j)
				if ((maxx == -1 && a[i] <= a[j]) || (maxx != -1 && maxx > a[j] && a[j] >= a[i]))
				{
					link(i + n, j, inf, 0);
					maxx = a[j];
					if (++ccnt == k) break;
				}
		}
		for (int i = 1; i <= n; i++) 
		{
			int maxx = -1;
			std::vector<int>tmp;
			for (int j = i - 1; j > 0; j--) 
				if ((maxx == -1 && a[j] <= a[i]) || (maxx != -1 && a[j] <= a[i] && maxx < a[j])) 	
				{
					tmp.push_back(j);
					maxx = a[j];
				}
			for (int j = 1; j <= std::min(k, int(tmp.size())); j++)
				link(tmp[tmp.size() - j] + n, i, inf, 0);
		}
		s = 0; t = n << 1 | 1;
		for (int i = 1; i <= n; ++i) link(s, i, inf, 0), link(i + n, t, inf, 0);
		++t;
		link(t - 1, t, k, 0);
		ans = 0;
		while (spfa()) mcmf();
		printf("%lld\n", -ans);
	}
	return 0;
}
