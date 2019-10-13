#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

#define maxn 100010
struct edge {
	int a, b, w;
	inline bool operator < (const edge &that) const {return w < that.w;}
} e[maxn << 1];
int Fa[maxn << 1], ch[maxn << 1][2], inv[maxn << 1], timer, n, dfn[maxn << 1], inw[maxn << 1], pos[maxn];
int fa[maxn << 1][20], c[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
void dfs(int x)
{
	dfn[x] = timer;
	for (int i = 1; i <= 19; ++i)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	if (x <= n) pos[timer++] = c[x];
	else
	{
		fa[ch[x][0]][0] = x;
		fa[ch[x][1]][0] = x;
		dfs(ch[x][0]); dfs(ch[x][1]);
	}
	inv[x] = timer - 1;
}
int hash[maxn], hcnt;
int Ans[333][333], Cnt[333][maxn];
int nc[maxn], sq, num;
inline int query_cnt(int col, int lid, int rid)
{
	if (rid < 0) return 0;
	return Cnt[rid][col] - Cnt[lid - 1][col];
}
inline int Query(int l, int r)
{
	int lid = l / sq, rid = r / sq;
	if (lid == rid)
	{
		int ans = 0, ans_id = 0;
		for (int i = l; i <= r; ++i)
		{
			++nc[pos[i]];
			if (nc[pos[i]] > ans || (nc[pos[i]] == ans && pos[i] < ans_id))
				ans = nc[pos[i]], ans_id = pos[i];
		}
		for (int i = l; i <= r; ++i)
			--nc[pos[i]];
		return ans_id;
	}
	int ans = 0, ans_id = 0;
	ans_id = Ans[lid + 1][rid - 1]; ans = Cnt[rid - 1][ans_id] - Cnt[lid][ans_id];
	// printf("%d %d %d %d\n", lid, rid, ans, ans_id);
	for (int i = l; i < (lid + 1) * sq; ++i)
	{
		++nc[pos[i]];
		int nn = nc[pos[i]] + query_cnt(pos[i], lid + 1, rid - 1);
		if (nn > ans || (nn == ans && pos[i] < ans_id)) ans = nn, ans_id = pos[i];
	}
	for (int i = rid * sq; i <= r; ++i)
	{
		++nc[pos[i]];
		int nn = nc[pos[i]] + query_cnt(pos[i], lid + 1, rid - 1);
		if (nn > ans || (nn == ans && pos[i] < ans_id)) ans = nn, ans_id = pos[i];
	}
	
	for (int i = l; i < (lid + 1) * sq; ++i) --nc[pos[i]];
	for (int i = rid * sq; i <= r; ++i) --nc[pos[i]];
	return ans_id;
}
int main()
{
	int T; scanf("%d", &T); inw[0] = 0x7fffffff;
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int m; scanf("%d%d", &n, &m); timer = 0; hcnt = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", c + i);
		for (int i = 1; i < 2 * n; ++i) Fa[i] = i, ch[i][0] = ch[i][1] = 0;
		for (int i = 1; i <= m; ++i) scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].w);
		std::sort(e + 1, e + m + 1);
		int cnter = n;
		for (int i = 1; i <= m; ++i)
		{
			int f1 = Find(e[i].a), f2 = Find(e[i].b);
			if (f1 != f2)
			{
				++cnter;
				ch[cnter][0] = f1;
				ch[cnter][1] = f2;
				Fa[f1] = Fa[f2] = cnter;
				inw[cnter] = e[i].w;
			}
		}
		int tcnt = 0; static int tmp[maxn];
		for (int i = 1; i <= n; ++i)
			tmp[++tcnt] = Find(i);
		std::sort(tmp + 1, tmp + tcnt + 1);
		tcnt = std::unique(tmp + 1, tmp + tcnt + 1) - tmp - 1;
		for (int i = 1; i < tcnt; ++i)
		{
			++cnter;
			int f1 = Find(tmp[i]), f2 = Find(tmp[i + 1]);
			ch[cnter][0] = f1;
			ch[cnter][1] = f2;
			Fa[f1] = Fa[f2] = cnter;
			inw[cnter] = 0x7fffffff;
		}
		fa[2 * n - 1][0] = 0;
		dfs(2 * n - 1);
		sq = (int) sqrt(n), num = (n - 1) / sq;
		
		for (int i = 0; i <= num; ++i)
		{
			int ans = 0, ans_id = 0;
			memset(nc, 0, (n + 1) << 2);
			for (int j = i * sq; j < n; ++j)
			{
				if (j % sq == 0 && j / sq > i)
					Ans[i][j / sq - 1] = ans_id;
				++nc[pos[j]];
				nc[pos[j]] > ans || (nc[pos[j]] == ans && pos[j] < ans_id)
					? ans = nc[pos[j]], ans_id = pos[j]
					: 0;
			}
		}
		/*for (int i = 0; i <= num; ++i)
			for (int j = i; j <= num; ++j)
				printf("Ans[%d][%d] = %d\n", i, j, Ans[i][j]);*/
		memset(nc, 0, (n + 1) << 2);
		for (int i = 0; i <= num; ++i)
		{
			if (i != 0) memcpy(Cnt[i], Cnt[i - 1], (n + 1) << 2);
			else memset(Cnt[0], 0, (n + 1) << 2);
			for (int j = i * sq; j < (i + 1) * sq && j < n; ++j)
				++Cnt[i][pos[j]];
		}
		
		
		// for (int i = 0; i < n; ++i) printf("%d ", pos[i]); puts("");
		int q, lastans = 0; scanf("%d", &q);
		printf("Case #%d:\n", Cas);
		for (; q; --q)
		{
			int x, w; scanf("%d%d", &x, &w);
			// x ^= lastans; w ^= lastans;
			for (int i = 19; ~i; --i)
				if (inw[fa[x][i]] <= w)
					x = fa[x][i];
			int ql = dfn[x], qr = inv[x];
			// printf("%d %d\n", ql, qr);
			printf("%d\n", lastans = Query(ql, qr));
		}
	}
	return 0;
}
