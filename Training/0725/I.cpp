#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define maxn 2010
#define maxm 10010
typedef unsigned uint;
struct Edge {
	Edge *next;
	int to, w;
} *last[maxn], e[maxm], *ecnt = e;
inline void link(int a, int b, int w)
{
	*++ecnt = (Edge) {last[a], b, w}; last[a] = ecnt;
	*++ecnt = (Edge) {last[b], a, w}; last[b] = ecnt;
}
int tow[maxn], concnt, sum, fa[maxn], ans[100010], dep[maxn];
bool vis[maxn];
std::vector<int> v[maxn];
void dfs(int x)
{
	vis[x] = 1; dep[x] = dep[fa[x]] + 1;
	for (Edge *iter = last[x]; iter; iter = iter -> next)
		if (iter -> to != fa[x])
		{
			if (vis[iter -> to])
			{
				if (dep[iter -> to] > dep[x]) continue;
				int p = x; ++concnt; v[concnt].push_back(-iter -> w);
				while (p != iter -> to)
				{
					v[concnt].push_back(-tow[p]);
					p = fa[p];
				}
			}
			else
			{
				tow[iter -> to] = iter -> w;
				fa[iter -> to] = x;
				dfs(iter -> to);
			}
		}
}
struct Queue {
	int ssum, step, num;
	inline bool operator < (const Queue &that) const {return ssum > that.ssum;}
} ;
std::priority_queue<Queue> q;
int main()	
{
	int n, m, Cas = 0;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		memset(last, 0, sizeof last); ecnt = e;
		concnt = sum = 0; int tot = 0;
		memset(vis, 0, n + 1);
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			link(a, b, w); sum += w;
		}
		int k; scanf("%d", &k);
		while (!q.empty()) q.pop();
		memset(ans, 0, (k + 1) << 2);
		for (int i = 1; i <= n; ++i) v[i].clear();
		dfs(1);
		//printf("%d\n", sum);
		for (int i = 1; i <= concnt; ++i)
		{
			std::sort(v[i].begin(), v[i].end());
			//for (int it : v[i]) printf("%d ", it); puts("");
			sum += v[i][0];
		}
		q.push((Queue) {sum, 1, 0});
		while (!q.empty())
		{
			Queue now = q.top(); q.pop();
			if (now.step > concnt) {ans[++tot] = now.ssum; if (tot == k) break; else continue;}
			if (now.num + 1 < v[now.step].size()) q.push((Queue) {now.ssum + v[now.step][now.num + 1] - v[now.step][now.num], now.step, now.num + 1});
			q.push((Queue) {now.ssum, now.step + 1, 0});
		}
		uint ret = 0;
//		std::sort(ans + 1, ans + k + 1);
		for (int i = 1; i <= k; ++i)
		{
			ret += 1u * i * ans[i];
			//printf("%d ", ans[i]);
		} //puts("");
		printf("Case #%d: %u\n", ++Cas, ret);
	}
	return 0;
}
