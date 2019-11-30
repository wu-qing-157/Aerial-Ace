#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

#define maxn 210
#define maxm 200010
typedef double db;
struct Edge {
	Edge *next, *rev;
	int from, to, cap;
	db cost;
} *last[maxn], *prev[maxn], e[maxm], *ecnt = e;
inline void link(int a, int b, int c, db p)
{
	*++ecnt = (Edge) {last[a], ecnt + 1, a, b, c, p}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], ecnt - 1, b, a, 0, -p}; last[b] = ecnt;
}
int s, t, q[maxn * maxn]; db ans, dis[maxn], pil;
bool inq[maxn], v[maxn];

const db inf = 1.0 / 0.0;
const db eps = 1e-9;
int aug(int no, int res)
{
	if (no == t) return ans += pil*res,res;
	v[no] = 1; int flow = 0;
	for (Edge *iter = last[no]; iter; iter = iter -> next)
		if (iter -> cap && !v[iter -> to] && fabs(iter -> cost) < eps) {
			int d = aug(iter -> to, std::min(res, iter -> cap));
			iter -> cap -= d; iter -> rev -> cap += d; flow += d;
			res -= d; if (!res) return flow;
		}
	return flow;
}
bool modlabel() {
	db d = inf;
	for (int i = 0; i <= t; ++i) if (v[i]) {
		for (Edge *iter = last[i]; iter; iter = iter -> next)
			if (iter -> cap && !v[iter -> to] && iter -> cost < d)
				d = iter -> cost;
	}
	if (d == inf) return 0;
	for (int i = 0; i <= t; ++i) if (v[i]) {
		for (Edge *iter = last[i]; iter; iter = iter -> next)
			iter -> cost -= d, iter -> rev -> cost += d;
	}
	pil += d; return 1;
}
void mininum_cost_flow_zkw() {
	int nowans = 0; pil = 0;
	do {
		do{
			for (int i = 0; i <= t; ++i) v[i] = 0;
			nowans = aug(s, 0x7fffffff); 
		} while (nowans);
	}while (modlabel());
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		s = 0; t = n + 1;
		for (int i = 0; i <= t; ++i) last[i] = 0; ecnt = e;
		for (int i = 1; i <= n; ++i)
		{
			int si, bi; scanf("%d%d", &si, &bi);
			link(s, i, si, 0);
			link(i, t, bi, 0);
		}
		for (int i = 1; i <= m; ++i)
		{
			int a, b, c; db p; scanf("%d%d%d%lf", &a, &b, &c, &p);
			link(a, b, 1, 0);
			link(a, b, c - 1, -log(1 - p));
		}
		ans = 0;
		mininum_cost_flow_zkw();
		printf("%.2lf\n", 1 - exp(-ans));
	}
	return 0;
}
