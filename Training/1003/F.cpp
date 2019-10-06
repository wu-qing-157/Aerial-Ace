#include <cstdio>
#include <cstring>

#define maxn 1010
char mp[maxn * 4][maxn * 6];
int id[maxn][maxn];
struct Edge {
	Edge *next;
	int to;
} *last[1000010], e[10000010], *ecnt = e;
inline void link(int a, int b)
{
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int q[maxn * maxn], dis[maxn * maxn], s, t;
const int dx[6] = {1, 2, 1, -1, -2, -1}, dy[6] = {-3, 0, 3, 3, 0, -3};
const int ddx[6] = {0, 1, 0, -1, -1, -1}, ddy[6] = {-1, 0, 1, 1, 0, -1};
const int dd[6] = {1, 1, 1, 0, -1, 0};
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m); getchar();
		for (int i = 1; i <= 4 * n + 3; ++i)
			fgets(mp[i] + 1, maxn * 6, stdin);
		int cnt = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				id[i][j] = ++cnt;
		memset(last + 1, 0, cnt * sizeof (Edge*)); ecnt = e;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
			{
				int cx = 4 * i - 1 + (j & 1 ? 0 : 2), cy = 6 * j - 1;
				// printf("[%d][%d] = (%d, %d)\n", i, j, cx, cy);
				if (mp[cx][cy] == 'S') s = id[i][j];
				if (mp[cx][cy] == 'T') t = id[i][j];
				for (int k = 0; k < 6; ++k)
				{
					int tx = cx + dx[k], ty = cy + dy[k];
					if (mp[tx][ty] == ' ')
					{
						if (j & 1)
							link(id[i][j], id[i + ddx[k]][j + ddy[k]]);
						else
							link(id[i][j], id[i + dd[k]][j + ddy[k]]);
					}
				}
			}
		int head = 0, tail = 1;
		memset(dis, 63, (cnt + 1) << 2);
		dis[q[1] = s] = 0;
		while (head < tail)
		{
			int now = q[++head];
			for (Edge *iter = last[now]; iter; iter = iter -> next)
				if (dis[iter -> to] > dis[now] + 1)
					dis[q[++tail] = iter -> to] = dis[now] + 1;
		}
		printf("%d\n", dis[t] + 1);
	}
	return 0;
}
/*
1
3 4
  +---+       +---+
 /     \     /     \
+       +---+       +---+
 \           \     /     \
  +   +   S   +---+   T   +
 /     \     /           /
+       +---+       +   +
 \           \     /     \
  +---+       +---+       +
 /                       /
+       +---+       +   +
 \                 /     \
  +---+       +---+       +
       \     /     \     /
        +---+       +---+
*/
