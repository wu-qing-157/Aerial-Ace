#include <cstdio>
#include <set>
#include <cstring>

#define maxn 1010
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
struct edge {int a, b;} ee[maxn];
struct Edge {
	Edge *next;
	int to, id;
} *last[maxn], e[maxn * maxn], *ecnt = e;
inline void link(int a, int b, int id)
{
	*++ecnt = (Edge) {last[a], b, id}; last[a] = ecnt;
}
bool del[maxn];
int n, m;
std::set<int> vv;
int dfn[maxn], low[maxn], timer, st[maxn], top, id[maxn], idcnt;
void tarjan(int x, int fa)
{
	dfn[x] = low[x] = ++timer; st[++top] = x;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		{
			if (!dfn[iter -> to])
			{
				tarjan(iter -> to, x);
				cmin(low[x], low[iter -> to]);
			}
			else if (!id[iter -> to]) cmin(low[x], dfn[iter -> to]);
		}
	if (dfn[x] == low[x])
	{
		++idcnt;
		for (; ;)
		{
			int now = st[top--];
			id[now] = idcnt;
			if (now == x) break;
		}
	}
}
int con[maxn][maxn];
void dfs(int step, std::set<int> now_v)
{
	if (now_v.size() == 1)
	{
		bool find = 0;
		for (int i = 1; i <= m; ++i)
			if (!del[i] && now_v.count(ee[i].a) && now_v.count(ee[i].b))
			{
				del[i] = 1;
				for (int j = 0; j < step; ++j) printf(" ");
				printf("wheel %d\n", 1);
				dfs(step + 1, now_v);
				for (int j = 0; j < step; ++j) printf(" ");
				printf("edge %d\n", i);
				return ;
			}
		for (int i = 1; i <= step; ++i) printf(" ");
		printf("vertex %d\n", *now_v.begin());
		return ;
	}
	for (int i = 1; i <= m; ++i)
		if (!del[i] && ee[i].a != ee[i].b)
		{
			del[i] = 1;
			memset(last, 0, sizeof last); ecnt = e;
			for (int j = 1; j <= m; ++j)
				if (!del[j] && now_v.count(ee[j].a) && now_v.count(ee[j].b) && ee[j].a != ee[j].b)
					link(ee[j].a, ee[j].b, j);
			idcnt = 0; memset(id, 0, (n + 1) << 2);
			memset(dfn, 0, (n + 1) << 2); timer = 0; top = 0;
			memset(con, 0, sizeof (con));
			for (auto it : now_v)
				if (!dfn[it])
					tarjan(it, 0);
			bool flag = 1;
			for (auto it : now_v)
				for (Edge *iter = last[it]; iter; iter = iter -> next)
					if (id[it] != id[iter -> to])
					{
						if (con[id[it]][id[iter -> to]]) flag = 0;
						if (id[it] != id[iter -> to] + 1) flag = 0;
						con[id[it]][id[iter -> to]] = iter -> id;
					}
			if (!flag) {del[i] = 0; continue;}
			std::set<int> s[maxn];
			for (int j = 1; j <= idcnt; ++j) s[j].clear();
			for (auto it : now_v) s[id[it]].insert(it);
			for (int j = 0; j < step; ++j) printf(" ");
			printf("wheel %d\n", idcnt);
			int ans[maxn];
			for (int j = idcnt; j; --j) del[ans[j] = con[j][j - 1]] = 1;
			for (int j = idcnt; j; --j)
			{
				dfs(step + 1, s[j]);
				if (j > 1)
				{
				for (int ii = 0; ii <= step; ++ii) printf(" ");
				printf("edge %d\n", ans[j]); }
			}
			for (int ii = 0; ii <= step; ++ii) printf(" ");
			printf("edge %d\n", i);
			return ;
		}
}
int main()
{
//freopen("wheels.in", "r", stdin);
//freopen("wheels.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i)
	{
		int a, b, w; scanf("%d%d", &a, &b);
		ee[i] = (edge) {a, b};
	}
	for (int i = 1; i <= n; ++i) vv.insert(i);
	dfs(0, vv);
	return 0;
}
/*
3 3
1 2
2 3
3 1

4 5
1 2
2 3
3 4
4 1
1 3

7 9
1 6
6 2
2 1
5 7
2 3
3 5
4 3
5 4
7 6
*/
