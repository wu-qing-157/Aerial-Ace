#include <cstdio>
#include <queue>
#include <map>
#include <cstring>

#define maxn 4010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
std::map<std::pair<int, int>, int> id;
struct Edge {
	Edge *next;
	int to, w, id;
} *last[maxn * 2], e[maxn * 2], *ecnt = e;
struct edge {int a, b, w;} ee[maxn * 2];
inline void link(int a, int b, int w, int id)
{
	*++ecnt = (Edge) {last[a], b, w, id}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w, id}; last[b] = ecnt;
}
int dis[maxn << 2];
struct Queue {
	int d, x;
	inline bool operator < (const Queue &that) const {return d > that.d;}
} ;
std::priority_queue<Queue> q;
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		printf("Case #%d: ", Cas);
		int m, cnt = 0; scanf("%d", &m);
		id.clear();
		for (int i = 1; i <= m; ++i)
		{
			int x, y, xx, yy, w; scanf("%d%d%d%d%d", &x, &y, &xx, &yy, &w);
			if (!id[std::make_pair(x, y)]) id[std::make_pair(x, y)] = ++cnt;
			if (!id[std::make_pair(xx, yy)]) id[std::make_pair(xx, yy)] = ++cnt;
			link(id[std::make_pair(x, y)], id[std::make_pair(xx, yy)], w, i);
			ee[i] = (edge) {id[std::make_pair(x, y)], id[std::make_pair(xx, yy)], w};
		}
		int ans = 0x7fffffff;
		for (int i = 1; i <= m; ++i)
		{
			memset(dis, 63, (cnt + 1) << 2);
			int s = ee[i].a, t = ee[i].b;
			q.push((Queue) {dis[s] = 0, s});
			while (!q.empty())
			{
				Queue now = q.top(); q.pop();
				if (now.d != dis[now.x]) continue;
				for (Edge *iter = last[now.x]; iter; iter = iter -> next)
					if (iter -> id > i && dis[iter -> to] > dis[now.x] + iter -> w)
						q.push((Queue) {dis[iter -> to] = dis[now.x] + iter -> w, iter -> to});
			}
			cmin(ans, dis[t] + ee[i].w);
		}
		memset(last, 0, (cnt + 1) * sizeof (Edge *)); ecnt = e;
		if (ans > 1e9) puts("0");
		else printf("%d\n", ans);
	}
	return 0;
}
/*
2
5
0 0 0 1 2
0 0 1 0 2
0 1 1 1 2
1 0 1 1 2
1 0 0 1 5
9
1 1 3 1 1
1 1 1 3 2
3 1 3 3 2
1 3 3 3 1
1 1 2 2 2
2 2 3 3 3
3 1 2 2 1
2 2 1 3 2
4 1 5 1 4
*/
