#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

#define maxn 300010
std::vector<int> e[maxn], kfa[maxn];
int val[maxn], mp[maxn], fa[maxn][20], top[maxn], son[maxn], pos[maxn], timer, dfn[maxn];
int dep[maxn], lim, Fa[maxn];
void dfs1(int x)
{
	for (int to : e[x])
	{
		dep[to] = dep[x] + 1;
		dfs1(to);
		mp[to] > mp[son[x]] ? son[x] = to : 0;
	}
	mp[x] = mp[son[x]] + 1;
}
void dfs2(int x)
{
	top[x] = son[Fa[x]] == x ? top[Fa[x]] : x;
	pos[++timer] = x; dfn[x] = timer;
	if (top[x] == x)
	{
		for (int p = x, i = 0; p && i <= mp[x]; ++i, p = Fa[p])
			kfa[x].push_back(p);
	}
	fa[x][0] = Fa[x];
	for (int i = 1; i <= 19; ++i)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	if (son[x]) dfs2(son[x]);
	for (int to : e[x])
		if (son[x] != to)
			dfs2(to);
}
inline int kth_father(int x, int k)
{
	if (!k) return x;
	if (k > dep[x]) return 0;
	int p = 31 - __builtin_clz(k);
	x = fa[x][p]; k -= 1 << p;
	if (dep[x] - dep[top[x]] >= k)
		return pos[dfn[x] - k];
	else return kfa[top[x]][k];
}
int inv_m[200][maxn], dfn_m[200][maxn], pos_m[200][maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 2; i <= n; ++i) scanf("%d", Fa + i), e[Fa[i]].push_back(i);
		dfs1(1); dfs2(1);
		lim = (int) ceil(sqrt(mp[1]));
		lim = 0;
		for (; m; --m)
		{
			int opt; scanf("%d", &opt);
			if (opt == 1)
			{
				int a, x, y, z; scanf("%d%d%d%d", &a, &x, &y, &z);
				if (x <= lim)
				{
				}
				else
					val[a] += z;
			}
			else
			{
				int x; scanf("%d", &x);
				int sum = 0;
				for (int p = kth_father(x, y); p; p = kth_father(p, x))
					{
						printf("%d %d\n", p, z);
						val[p];
					}
				printf("%d\n", sum);
			}
		}
	}
	return 0;
}
