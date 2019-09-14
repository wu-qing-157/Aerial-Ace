#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 10010;
const int M = 10010 * 20;

#define maxn 20
char s[maxn][maxn];
int vis[maxn][maxn][maxn][maxn], ans[N];
int id[maxn][maxn][maxn][maxn], counter[2], n, m;
void dfs(int x_1, int y_1, int x_2, int y_2) {
	if (x_1 <= 0 || x_1 > n) return ;
	if (x_2 <= 0 || x_2 > n) return ;
	if (y_1 <= 0 || y_1 > m) return ;
	if (y_2 <= 0 || y_2 > m) return ;
	if (s[x_1][y_1] == '#') return ;
	if (s[x_2][y_2] == '#') return ;
	if (x_1 == x_2 && y_1 == y_2) return ;
	if (x_1 > x_2 || (x_1 == x_2 && y_1 > y_2)) swap(x_1, x_2), swap(y_1, y_2);
	if (vis[x_1][y_1][x_2][y_2]) return ;
	vis[x_1][y_1][x_2][y_2] = 1;
	if ((x_1 ^ y_1 ^ x_2 ^ y_2) & 1)
		id[x_1][y_1][x_2][y_2] = ++counter[1];
	else
		id[x_1][y_1][x_2][y_2] = ++counter[0];
	dfs(x_1 + 1, y_1, x_2, y_2);
	dfs(x_1 - 1, y_1, x_2, y_2);
	dfs(x_1, y_1 + 1, x_2, y_2);
	dfs(x_1, y_1 - 1, x_2, y_2);
	dfs(x_1, y_1, x_2 + 1, y_2);
	dfs(x_1, y_1, x_2 - 1, y_2);
	dfs(x_1, y_1, x_2, y_2 + 1);
	dfs(x_1, y_1, x_2, y_2 - 1);
}

int nn, mm, dx[N], dy[N], matx[N], maty[N], q[N * 20];
std::vector<int> to[N];

int bfs() {
	int flag = 0, h = 0, l = 0;
	for (int i = 1; i <= mm; i++) dy[i] = 0;
	for (int i = 1; i <= nn; i++) {
		dx[i] = 0;
		if (!matx[i]) q[++l] = i;
	}
	while (h < l) {
		int x = q[++h];
		for (int y : to[x]) {
			if (!dy[y]) {
				dy[y] = dx[x] + 1;
				if (!maty[y]) flag = 1;
				else {
					dx[maty[y]] = dx[x] + 2;
					q[++l] = maty[y];
				}
			}
		}
	}
	return flag;
}

int dfs(int x) {
	for (int y : to[x]) {
		if (dy[y] == dx[x] + 1) {
			dy[y] = 0;
			if (!maty[y] || dfs(maty[y])) {
				matx[x] = y, maty[y] = x;
				return 1;
			}
		}
	}
	return 0;
}

void add(int i, int j) {
	to[i].push_back(j);
}

int main()
{
	int k;
	while (scanf("%d%d%d", &n, &m, &k) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		for (; k; --k)
		{
			int x_1, y_1, x_2, y_2;
			scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
			counter[0] = counter[1] = 0;
			memset(vis, 0, sizeof (vis));
			memset(id, 0, sizeof id);
			dfs(x_1, y_1, x_2, y_2);
			// dfs2(x_1, y_1, x_2, y_2, -1);
			for (int x1 = 1; x1 <= n; x1++) for (int y1 = 1; y1 <= m; y1++)
				for (int x2 = 1; x2 <= n; x2++) for (int y2 = 1; y2 <= m; y2++) {
					if (id[x1][y1][x2][y2]) {
						if ((x1 ^ y1 ^ x2 ^ y2) & 1) {
							if (id[x1 + 1][y1][x2][y2]) add(id[x1 + 1][y1][x2][y2], id[x1][y1][x2][y2]);
							if (id[x1][y1 + 1][x2][y2]) add(id[x1][y1 + 1][x2][y2], id[x1][y1][x2][y2]);
							if (id[x1][y1][x2 + 1][y2]) add(id[x1][y1][x2 + 1][y2], id[x1][y1][x2][y2]);
							if (id[x1][y1][x2][y2 + 1]) add(id[x1][y1][x2][y2 + 1], id[x1][y1][x2][y2]);
						} else {
							if (id[x1 + 1][y1][x2][y2]) add(id[x1][y1][x2][y2], id[x1 + 1][y1][x2][y2]);
							if (id[x1][y1 + 1][x2][y2]) add(id[x1][y1][x2][y2], id[x1][y1 + 1][x2][y2]);
							if (id[x1][y1][x2 + 1][y2]) add(id[x1][y1][x2][y2], id[x1][y1][x2 + 1][y2]);
							if (id[x1][y1][x2][y2 + 1]) add(id[x1][y1][x2][y2], id[x1][y1][x2][y2 + 1]);
						}
					}
			nn = counter[0], mm = counter[1];
			for (int i = 1; i <= nn; i++) matx[i] = 0;
			for (int i = 1; i <= mm; i++) maty[i] = 0;
			while (bfs()) for (int i = 1; i <= n; i++) if (!matx[i]) dfs(i);
			memset(v, 0, sizeof v);
			memset(ans, 0, sizeof ans);
			for (int i = 1; i <= n; i++) dfss1(i);
			for 
		}
	}
	return 0;
}
/*
1 10 1
.....#....
1 7 1 10
*/
