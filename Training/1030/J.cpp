#include <cstdio>
#include <vector>

#define maxn 100010
std::vector<int> e[maxn];
inline void link(int a, int b)
{
	e[a].push_back(b);
	e[b].push_back(a);
}
int p1, p2, f[maxn][3];
void dfs(int x, int fa)
{
	
	for (int to : e[x])
		if (fa != to)
		{
			dfs(to);
			
		}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			link(a, b);
		}
		dfs(1);
	}
	return 0;
}
