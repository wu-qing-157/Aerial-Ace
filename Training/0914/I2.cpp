#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 10010;
const int M = 10010 * 20;
struct blossom {
	struct Edge {
		int x, y, next;
	} edge[M];
	
	int n, W, tot, h, l, son[N];
	int mat[N], pre[N], tp[N], q[N], vis[N], F[N];
	
	void Prepare(int n_)
	{
		n = n_;
		W = tot = 0;
		for (int i = 1; i <= n; ++i)
			son[i] = mat[i] = vis[i] = 0;
	}
	
	void add(int x, int y)
	{
		printf("add %d %d\n", x, y);
		edge[++tot].x = x; edge[tot].y = y;
		edge[tot].next = son[x]; son[x] = tot;
		edge[++tot].x = y; edge[tot].y = x;
		edge[tot].next = son[y]; son[y] = tot;
	}
	
	int find(int x)
	{
		return F[x] ? F[x] = find(F[x]) : x;
	}
	
	int lca(int u, int v)
	{
		for (++W;; u = pre[mat[u]], swap(u, v))
			if (vis[u = find(u)] == W) return u;
			else vis[u] = u ? W : 0;
	}
	
	void aug(int u, int v)
	{
		for (int w; u; v = pre[u = w])
			w = mat[v], mat[mat[u] = v] = u;
	}
	
	void blo(int u, int v, int f)
	{
		for (int w; find(u) ^ f; u = pre[v = w])
			pre[u] = v, F[u] ? 0 : F[u] = f, F[w = mat[u]] ? 0 : F[w] = f, tp[w] ^ 1 ? 0 :
				tp[q[++l] = w] = -1;
	}
	
	int bfs(int x)
	{
		for (int i = 1; i <= n; ++i)
			tp[i] = F[i] = 0;
			
		h = l = 0;
		q[++l] = x;
		tp[x]--;
		while (h < l)
		{
			x = q[++h];
			for (int i = son[x]; i; i = edge[i].next)
			{
				int y = edge[i].y, Lca;
				if (!tp[y])
				{
					if (!mat[y]) return aug(y, x), 1;
					pre[y] = x; ++tp[y]; --tp[q[++l] = mat[y]];
				}
				else if (tp[y] ^ 1 && find(x) ^ find(y))
					blo(x, y, Lca = lca(x, y)), blo(y, x, Lca);
			}
		}
		return 0;
	}
	
	int solve()
	{
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			if (!mat[i]) ans += bfs(i);
		return ans;
	}
} G;
#define maxn 20
char s[maxn][maxn];
int vis[maxn][maxn][maxn][maxn], timer, ans[N];
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
	vis[x_1][y_1][x_2][y_2] = timer;
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
bool vis2[maxn][maxn][maxn][maxn];
void dfs2(int x_1, int y_1, int x_2, int y_2, int last)
{
	if (x_1 <= 0 || x_1 > n) return ;
	if (x_2 <= 0 || x_2 > n) return ;
	if (y_1 <= 0 || y_1 > m) return ;
	if (y_2 <= 0 || y_2 > m) return ;
	if (s[x_1][y_1] == '#') return ;
	if (s[x_2][y_2] == '#') return ;
	if (x_1 == x_2 && y_1 == y_2) return ;

	if (x_1 > x_2 || (x_1 == x_2 && y_1 > y_2)) swap(x_1, x_2), swap(y_1, y_2);
	if (last != -1)
		G.add(id[x_1][y_1][x_2][y_2], last),
		G.add(last, id[x_1][y_1][x_2][y_2]);
	if (vis2[x_1][y_1][x_2][y_2]) return ;
	vis2[x_1][y_1][x_2][y_2] = 1;
	dfs2(x_1 + 1, y_1, x_2, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1 - 1, y_1, x_2, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1 + 1, x_2, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1 - 1, x_2, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1, x_2 + 1, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1, x_2 - 1, y_2, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1, x_2, y_2 + 1, id[x_1][y_1][x_2][y_2]);
	dfs2(x_1, y_1, x_2, y_2 - 1, id[x_1][y_1][x_2][y_2]);
}
int main()
{
	int k;
	while (scanf("%d%d%d", &n, &m, &k) != EOF)
	{
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		memset(vis, 0, sizeof (vis));
		memset(vis2, 0, sizeof (vis2));
		for (; k; --k)
		{
			int x_1, y_1, x_2, y_2;
			scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
			if (!vis[x_1][y_1][x_2][y_2])
			{
				counter = 0; ++timer;
				memset(id, 0, sizeof id);
				dfs(x_1, y_1, x_2, y_2);
				G.Prepare(counter);
				// dfs2(x_1, y_1, x_2, y_2, -1);
				for (int x1 = 1; x1 <= n; x1++) for (int y1 = 1; y1 <= m; y1++)
					for (int x2 = 1; x2 <= n; x2++) for (int y2 = 1; y2 <= m; y2++)
						if (id[x1][y1][x2][y2]) {
							if (id[x1 + 1][y1][x2][y2]) G.add(id[x1][y1][x2][y2], id[x1 + 1][y1][x2][y2]);
							if (id[x1][y1 + 1][x2][y2]) G.add(id[x1][y1][x2][y2], id[x1][y1 + 1][x2][y2]);
							if (id[x1][y1][x2 + 1][y2]) G.add(id[x1][y1][x2][y2], id[x1][y1][x2 + 1][y2]);
							if (id[x1][y1][x2][y2 + 1]) G.add(id[x1][y1][x2][y2], id[x1][y1][x2][y2 + 1]);
						}
				int tmp = G.solve();
				printf("tmp %d %d\n", tmp, counter);
				ans[timer] = tmp * 2 == counter;
				puts(ans[timer] ? "1" : "2");
			}
			else
			{
				puts(ans[vis[x_1][y_1][x_2][y_2]] ? "1" : "2");
			}
		}
	}
	return 0;
}
/*
1 10 1
.....#....
1 7 1 10
*/
