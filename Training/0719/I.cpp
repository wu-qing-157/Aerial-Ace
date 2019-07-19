#include <cstdio>
#include <vector>

#define maxn 210
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
int a[maxn][maxn];
struct Query {
	int a, b, c, d, id;
} ;
std::vector<Query> v;
int ans[10010], n, m;
int sum[maxn][maxn];
void prepare(int x)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (a[i][j] <= x);
}
int query(int a, int b, int c, int d)
{
	return sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
}
void work(int l, int r, std::vector<Query> vv)
{
	if (!vv.size()) return ;
	//printf("l %d r %d\n", l, r);
	//for (auto it : vv) printf("%d ", it.id);puts("");
	if (l == r)
	{
		for (auto it : vv)
			ans[it.id] = l;
		return ;
	}
	int mid = l + r >> 1;
	prepare(mid);
	std::vector<Query> vl, vr;
	for (auto it : vv)
	{
		//printf("%d %d\n", it.id, query(it.a, it.b, it.c, it.d));
		if (query(it.a, it.b, it.c, it.d) >= (it.c - it.a + 1) * (it.d - it.b + 1) / 2 + 1)
			vl.push_back(it);
		else vr.push_back(it);
	}
	work(l, mid, vl);
	work(mid + 1, r, vr);
}
int main()
{
//	freopen("important.in", "r", stdin);
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int q; scanf("%d%d%d", &n, &m, &q);
		v.clear();
		int maxx = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &a[i][j]), cmax(maxx, a[i][j]);
		for (int i = 1; i <= q; ++i)
		{
			int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
			v.push_back((Query) {a, b, c, d, i});
		}
		work(1, maxx, v);
		printf("Case %d:\n", Cas);
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
/*
1
3 4 2
1 2 3 1
2 1 1 4
7 8 9 3
1 1 1 1
1 2 3 4
*/
