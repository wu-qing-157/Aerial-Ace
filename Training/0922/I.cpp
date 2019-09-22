#include <cstdio>
#include <algorithm>

#define maxn 2010
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
std::pair<int, int> q[maxn * maxn];
int vis[maxn][maxn], n, m;
inline bool check(int x, int y)
{
	return x && y && x <= n && y <= m && (!vis[x + 1][y] || !vis[x - 1][y]) && (!vis[x][y - 1] || !vis[x][y + 1]);
}
int bfs(int x, int y)
{
	if (!vis[x][y]) return 0;
	int ret = 1; vis[x][y] = 0;
	int head = 0, tail = 1; q[1] = std::make_pair(x, y);
	while (head < tail)
	{
		auto now = q[++head];
		x = now.first; y = now.second;
		for (int i = 0; i < 4; ++i)
			if (check(x + dx[i], y + dy[i]) && vis[x + dx[i]][y + dy[i]])
			{
				q[++tail] = std::make_pair(x + dx[i], y + dy[i]);
				++ret; vis[x + dx[i]][y + dy[i]] = 0;
			}
	}
	return ret;
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int q; scanf("%d%d%d", &n, &m, &q);
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= m + 1; ++j)
				vis[i][j] = 1;
		for (; q; --q)
		{
			int x, y; scanf("%d%d", &x, &y);
			int ans = bfs(x, y);
			/*for (int i = 1; i <= n; ++i, puts(""))
				for (int j = 1; j <= m; ++j)
					printf("%d", vis[i][j]);*/
			printf("%d\n", ans);
		}
	}
	return 0;
}
