#include <cstdio>
#include <vector>
#include <cstring>
#include <bitset>

#define maxn 110
std::vector<int> e[maxn];
int n, m, s;
bool vis[maxn], vv[maxn];
int ans;
std::bitset<maxn> con[maxn], st;
void dfs(int x, int num)
{
	if (num == s)
	{
		++ans;
		return ;
	}
	for (int it : e[x])
		if (it > x)
	{
		bool flag = (con[it] & st).count() == num;
		st[it] = 1;
		if (flag) dfs(it, num + 1);
		st[it] = 0;
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d%d%d", &n, &m, &s);
		ans = 0;
		for (int i = 1; i <= n; ++i) con[i].reset(), e[i].clear();
		for (int i = 1; i <= m; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			e[a].push_back(b);
			e[b].push_back(a);
			con[a][b] = con[b][a] = 1;
		}
		for (int i = 1; i <= n; ++i)
		{
			st[i] = 1;
			dfs(i, 1);
			st[i] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
/*
2
5 9 3
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
4 5
6 15 4
1 2
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
4 5
4 6
5 6
*/
