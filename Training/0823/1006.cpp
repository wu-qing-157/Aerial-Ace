#include <cstdio>
#include <cstring>

#define maxn 100010
int a[maxn], ans[maxn], b[maxn];
bool vis[maxn];
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		memset(vis, 0, n + 1);
		for (int i = 1; i <= n; ++i) scanf("%d", b + i);
		for (int i = 1; i <= m; ++i) scanf("%d", a + i);
		int p = 0;
		for (int i = m; i; --i) !vis[a[i]] ? vis[ans[++p] = a[i]] = 1 : 0;
		for (int i = 1; i <= n; ++i) !vis[b[i]] ? ans[++p] = b[i] : 0;
		for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	}
	return 0;
}
