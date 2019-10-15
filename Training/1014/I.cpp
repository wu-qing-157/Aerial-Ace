#include <bits/stdc++.h>

#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
const int maxk = 5;
const int maxn = 100010;
const int maxm = 1000010;
const int inf = 0x7fffffff;
typedef long long ll;

int a[30][30][maxk];
int w[30][30];
int id[30][30][maxk], id_cnt = 0;

struct Edge {
	Edge *next, *rev;
	int to, cap;
} *last[maxn], e[maxm], *ecnt = e, *cur[maxn];
inline void link(int a, int b, int w)
{	
	std::cout << a << ' ' << b << ' ' << w << std::endl;
	*++ecnt = (Edge) {last[a], ecnt + 1, b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, a, 0}; last[b] = ecnt;
}
ll ans;
int s, t, q[maxn], dep[maxn];

inline bool bfs()
{
	memset(dep, -1, (t + 1) << 2);
	int head = 0, tail = 1;
	dep[q[1] = t] = 0;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> rev -> cap && dep[iter -> to] == -1)
				dep[q[++tail] = iter -> to] = dep[now] + 1;
	}
	return dep[s] != -1;
}
ll dfs(int x, ll f)
{
	if (x == t) return f;
	ll used = 0;
	for (Edge* &iter = cur[x]; iter; iter = iter -> next)
		if (iter -> cap && dep[iter -> to] + 1 == dep[x])
		{
			ll v = dfs(iter -> to, dmin(f - used, iter -> cap));
			iter -> cap -= v;
			iter -> rev -> cap += v;
			used += v;
			if (used == f) return f;
		}
	return used;
}
void dinic()
{
	ans = 0;
	while (bfs())
	{
		memcpy(cur, last, (t + 1) * sizeof (Edge *));
		ans += dfs(s, inf);
	}
}
inline void init(int n)
{
	memset(last, 0, (n + 1) * sizeof (Edge*)); ecnt = e;
}

void work() {
	int n, m; scanf("%d%d", &n, &m);
	id_cnt = 0;
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j][0]);
			id[i][j][0] = ++id_cnt;
			for (int k = 1; k < maxk - 1; k++) 
				a[i][j][k] = a[i][j][k - 1] / 2;
			for (int k = 1; k < maxk; k++) 
				id[i][j][k] = ++id_cnt;
		}
	s = 0; t = ++id_cnt;
	init(id_cnt);	
	
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= m; j++) {
			scanf("%d", &w[i][j]);
			for (int k = 0; k < maxk - 1; k++)
				link(id[i][j][k], id[i][j][k + 1], w[i][j] * k);
		}
	int m1, m2;
	scanf("%d", &m1);
	while (m1--) {
		int x1, x2, y1, y2, d;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &d);
		for (int t1 = 0; t1 < maxk - 1; t1++) {
			bool bk = false;
			for (int t2 = maxk - 2; t2 >= 0; t2--) {
				if (a[x1][y1][t1] + a[x2][y2][t2] <= d) {
					link(id[x1][y1][t1], id[x2][y2][t2], inf);
					bk =  true;
					break;
				} 
			}
			//if (!bk) link(id[x1][y1][t1], id[x1][y1][t1 + 1], inf);
		}
		std::swap(x1, x2);
		std::swap(y1, y2);
		for (int t1 = 0; t1 < maxk - 1; t1++) {
			bool bk = false;
			for (int t2 = maxk - 2; t2 >= 0; t2--) {
				if (a[x1][y1][t1] + a[x2][y2][t2] <= d) {
					link(id[x1][y1][t1], id[x2][y2][t2], inf);
					bk =  true;
					break;
				} 
			}
			//if (!bk) link(id[x1][y1][t1], id[x1][y1][t1 + 1], inf);
		}
	}
	scanf("%d", &m2);
	while (m2--) {
		int x1, x2, y1, y2, c;
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
		for (int t1 = 0; t1 < maxk - 1; t1++) {
			bool bk = false;
			for (int t2 = 0; t2 < maxk - 1; t2++) {
				if (a[x1][y1][t1] + a[x2][y2][t2] >= c) {
					link(id[x2][y2][t2 + 1], id[x1][y1][t1 + 1], inf);
					bk = true;
					break;
				} 
			}
			//if (!bk) link(id[x1][y1][t1], id[x1][y1][t1 + 1], inf);
		}
		std::swap(x1, x2);
		std::swap(y1, y2);
		for (int t1 = 0; t1 < maxk - 1; t1++) {
			bool bk = false;
			for (int t2 = 0; t2 < maxk - 1; t2++) {
				if (a[x1][y1][t1] + a[x2][y2][t2] >= c) {
					link(id[x2][y2][t2 + 1], id[x1][y1][t1 + 1], inf);
					bk = true;
					break;
				} 
			}
			//if (!bk) link(id[x1][y1][t1], id[x1][y1][t1 + 1], inf);
		}
	}
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			link(s, id[i][j][0], inf), 
			link(id[i][j][maxk - 1], t, inf);
	
	dinic();
	
	if (ans > 2e9) puts("impossible");
	else printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
/*
1
1 2
8 3
2 1
1
1 1 1 2 5
1
1 1 1 2 4
*/

