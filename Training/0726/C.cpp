#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>

#define maxn 20
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m;
int a[maxn][maxn];
int ans, score, num;
bool vis[maxn][maxn];
int tot[10];
struct Con {
	int x, y, num, col;
	inline bool operator < (const Con &that) const {return num > that.num;}
} ;
std::pair<int, int> q[maxn * maxn];
void floodfill(int x, int y)
{
	int head = 0, tail = 1; q[1] = std::make_pair(x, y); vis[x][y] = 1;
	while (head < tail)
	{
		auto now = q[++head]; ++num;
		for (int i = 0; i < 4; ++i)
		{
			int nx = now.first + dx[i], ny = now.second + dy[i];
			if (nx && ny && nx <= n && ny <= m && a[nx][ny] == a[x][y] && !vis[nx][ny])
			{
				q[++tail] = std::make_pair(nx, ny);
				vis[nx][ny] = 1;
			}
		}
	}
}
void erase(int x, int y, int c)
{
	int head = 0, tail = 1; q[1] = std::make_pair(x, y);
	while (head < tail)
	{
		auto now = q[++head]; ++num; a[now.first][now.second] = -1;
		for (int i = 0; i < 4; ++i)
		{
			int nx = now.first + dx[i], ny = now.second + dy[i];
			if (nx && ny && nx <= n && ny <= m && a[nx][ny] == c)
			{
				q[++tail] = std::make_pair(nx, ny);
				a[nx][ny] = -1;
			}
		}
	}
	for (int j = 1; j <= m; ++j)
	{
		for (int i = 2; i <= n; ++i)
			if (a[i][j] == -1)
			{
				for (int k = i; k > 1; --k)
					a[k][j] = a[k - 1][j];
				a[1][j] = -1;
			}
	}
	for (int j = 2; j <= m; ++j)
		if (a[n][j] == -1)
		{
			for (int jj = j; jj > 1; --jj)
				for (int i = 1; i <= n; ++i)
					a[i][jj] = a[i][jj - 1];
			for (int i = 1; i <= n; ++i) a[i][1] = -1;
		}
}
struct Map {
	int a[maxn][maxn];
} ;
std::unordered_map<Map> mp;
void dfs()
{
	cmax(ans, score);
	int tmp = score;
	for (int i = 0; i < 5; ++i) tmp += tot[i] * (tot[i] - 1);
	if (tmp <= ans) return ;
	Map p; memcpy(p.a, a, sizeof (a));
	memset(vis, 0, sizeof (vis));
	int ccnt = 0, col = 5;
	Con c[maxn * maxn];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		if (a[i][j] != -1 && !vis[i][j])
		{
			num = 0;
			floodfill(i, j);
			c[++ccnt] = (Con) {i, j, num, a[i][j]};
			if (num > 1) cmin(col, a[i][j]);
		}
	std::sort(c + 1, c + ccnt + 1);
	int mp[maxn][maxn];
	for (int i = 1; i <= ccnt; ++i)
		if (c[i].col == col && c[i].num > 1)
		{
			memcpy(mp, a, sizeof (a));
			score += c[i].num * (c[i].num - 1);
			tot[c[i].col] -= c[i].num;
			erase(c[i].x, c[i].y, c[i].col);
			dfs();
			score -= c[i].num * (c[i].num - 1);
			tot[c[i].col] += c[i].num;
			memcpy(a, mp, sizeof (a));
		}
}
int main()
{
	int Cas = 0;
	while (1)
	{
		scanf("%d%d", &n, &m); ans = 0; score = 0;
		memset(tot, 0, sizeof (tot));
		if (!n && !m) return 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]), tot[a[i][j]]++;
		dfs();
		printf("Case #%d: %d\n", ++Cas, ans);
	}
	return 0;
}
/*
4 3
0 1 2
1 2 3
3 4 0
1 0 0
4 4
0 1 2 3
1 2 3 0
2 3 0 1
3 0 1 2
0 0
*/
