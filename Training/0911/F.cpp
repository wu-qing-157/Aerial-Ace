#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

#define maxn 100010
typedef long long ll;
int a[maxn], b[maxn], v[maxn];
std::vector<int> e[maxn];
ll f[maxn][2], g[maxn][2], dp[maxn];
const ll oo = 1e18;
void dfs1(int x, int fa = 0)
{
	f[x][0] = oo;
	f[x][1] = -oo;
	if (e[x].size() == 1 && x != 1) f[x][0] = f[x][1] = v[x];
	if (e[x].size() == 0) f[x][0] = f[x][1] = v[x];
	for (int to : e[x])
		if (to != fa)
		{
			dfs1(to, x);
			f[x][0] = std::min(f[x][0], f[to][1]) + v[x];
			f[x][1] = std::max(f[x][1], f[to][0]) + v[x];
		}
}
ll pre[maxn][2], suf[maxn][2], tp[maxn][2];
void dfs2(int x, int fa = 0)
{
	int num = 0;
	for (int to : e[x])
		if (to != fa)
		{
			++num;
			tp[num][0] = f[to][0];
			tp[num][1] = f[to][1];
		}
	pre[0][0] = -oo;
	pre[0][1] = oo;
	suf[num + 1][0] = -oo;
	suf[num + 1][1] = oo;
	for (int i = 1; i <= num; ++i)
		pre[i][0] = std::max(pre[i - 1][0], tp[i][0]),
		pre[i][1] = std::min(pre[i - 1][1], tp[i][1]);
	for (int i = num; i; --i)
		suf[i][0] = std::max(suf[i + 1][0], tp[i][0]),
		suf[i][1] = std::min(suf[i + 1][1], tp[i][1]);
	
	int id = 0;
	for (int to : e[x])
		if (to != fa)
		{
			++id;
			g[to][0] = std::max(g[x][1], std::max(pre[id - 1][0], suf[id + 1][0]) + v[x]) + v[to];
			g[to][1] = std::min(g[x][0], std::min(pre[id - 1][1], suf[id + 1][1]) + v[x]) + v[to];
		}
	
	for (int to : e[x])
		if (to != fa)
			dfs2(to, x);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), e[i].clear();
		for (int i = 1; i <= n; ++i) scanf("%d", b + i), v[i] = a[i] - b[i];
		
		for (int i = 1; i < n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
		}
		g[1][0] = oo;
		g[1][1] = -oo;
		if (e[1].size() == 1 || e[1].size() == 0)
			g[1][0] = g[1][1] = v[1];
		dfs1(1); dfs2(1);
		
		/*for (int i = 1; i <= n; ++i)
			for (int j = 0; j < 2; ++j)
				printf("f[%d][%d] = %d\n", i, j, f[i][j]),
				printf("g[%d][%d] = %d\n", i, j, g[i][j]);*/
		
		ll maxx = f[1][0];
		for (int i = 2; i <= n; ++i) {
			if (e[i].size() == 1)
				maxx = std::max(maxx, g[i][0]);
			else
				maxx = std::max(maxx, std::min(g[i][0], f[i][0]));
		}
		printf("%lld\n", maxx);
	}
	return 0;
}
