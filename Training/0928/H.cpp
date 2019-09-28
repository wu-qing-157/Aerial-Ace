#include <cstdio>
#include <set>
#include <algorithm>
#include <queue>

#define maxn 100010
typedef long long ll;
struct Ship {
	ll d;
	int c, s, id;
	inline bool operator < (const Ship &that) const {return d < that.d || (d == that.d && id < that.id);}
} s[maxn];
struct Crane {
	ll d; int id;
	inline bool operator < (const Crane &that) const {return d < that.d || (d == that.d && id < that.id);}
} ;
bool pp[maxn][12];
int ans[maxn], v[maxn];
std::multiset<Crane> idle[12];
std::multiset<Ship> dock[12];
struct pipeline {
	ll d;
	int ty, id;
	inline bool operator < (const pipeline &that) const {return d > that.d || (d == that.d && (ty < that.ty || (ty == that.ty && id > that.id)));}
} ;
std::priority_queue<pipeline> q;
int main()
{
//	freopen("seaport.in", "r", stdin);
//	freopen("seaport.out", "w", stdout);
	int n, m, c; scanf("%d%d%d", &n, &m, &c);
	for (int i = 1; i <= n; ++i) scanf("%lld%d%d", &s[i].d, &s[i].c, &s[i].s), s[i].id = i;
	for (int i = 1; i <= m; ++i)
	{
		int t; scanf("%d%d", v + i, &t);
		for (int j = 1; j <= t; ++j)
		{
			int x; scanf("%d", &x); pp[i][x] = 1;
			idle[x].insert((Crane) {0, i});
		}
	}
	for (int i = 1; i <= n; ++i) q.push((pipeline) {s[i].d, 1, i});
	while (!q.empty())
	{
		pipeline now = q.top(); q.pop();
		//printf("%lld %d %d\n", now.d, now.ty, now.id);
		if (now.ty == 1)
		{
			if (idle[s[now.id].c].size())
			{
				Crane top = *idle[s[now.id].c].begin();

					

				
				for (int cc = 1; cc <= c; ++cc)
					if (pp[top.id][cc])
						idle[cc].erase(top);
				ans[now.id] = top.id;
				q.push((pipeline) {now.d + (s[now.id].s + v[top.id] - 1) / v[top.id], 2, top.id});
			}
			else dock[s[now.id].c].insert(s[now.id]);
		}
		else
		{
			Ship maxx = (Ship) {~0ULL >> 1, -1, -1, -1};
			for (int cc = 1; cc <= c; ++cc)
				if (pp[now.id][cc] && dock[cc].size())
					maxx = std::min(maxx, *dock[cc].begin());
			Crane top = (Crane) {now.d, now.id};
			if (maxx.id > 0)
			{
				dock[maxx.c].erase(maxx);
				ans[maxx.id] = top.id;
				q.push((pipeline) {now.d + (s[maxx.id].s + v[top.id] - 1) / v[top.id], 2, top.id});
			}
			else
			{
				for (int cc = 1; cc <= c; ++cc)
					if (pp[top.id][cc])
						idle[cc].insert(top);
			}
		}
	}
	
	for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}
/*
4 2 2
0 1 10
0 1 11
5 2 10
5 1 10
1 2 1 2
1 2 1 2
*/
