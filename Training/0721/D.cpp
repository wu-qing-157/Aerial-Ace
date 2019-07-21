#include <cstdio>
#include <algorithm>

#define maxn 110
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
struct edge {
	int a, b, w;
	inline bool operator < (const edge &that) const {return w > that.w;}
} e[maxn * maxn], ans[maxn * maxn];
int a[maxn][maxn];
int fa[maxn], mn[maxn], size[maxn], f1[maxn], f2[maxn];
int main()
{
//freopen("matrix.in", "r", stdin);
//freopen("matrix.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	for (int j = 1; j <= n; ++j)
		scanf("%d", &a[i][j]);
	int ecnt = 0, anscnt = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i][i] != 0) {puts("NO"); return 0;}
		mn[i] = 0x7fffffff; size[i] = 1;
		for (int j = i + 1; j <= n; ++j)
			if (a[i][j] != a[j][i])
			{
				puts("NO"); return 0;
			}
			else e[++ecnt] = (edge) {i, j, a[i][j]};
	}
	std::sort(e + 1, e + ecnt + 1);
	for (int i = 1; i <= ecnt; ++i)
	{
		int a = e[i].a, b = e[i].b, minn = 0x7fffffff, f1cnt = 0, f2cnt = 0;
		for (; fa[a]; a = fa[a]) f1[++f1cnt] = a;
		for (; fa[b]; b = fa[b]) f2[++f2cnt] = b;
		while (f1cnt && f2cnt && f1[f1cnt] == f2[f2cnt]) --f1cnt, --f2cnt;
		for (; f1cnt; --f1cnt) cmin(minn, mn[f1[f1cnt]]);
		for (; f2cnt; --f2cnt) cmin(minn, mn[f2[f2cnt]]);

		if (size[a] > size[b]) std::swap(a, b);
		if (a != b)
		{
			size[b] += size[a]; fa[a] = b; mn[a] = e[i].w;
			ans[++anscnt] = (edge) {e[i].a, e[i].b, e[i].w};
		}
		else if (minn != e[i].w) {puts("NO"); return 0;}
	}
	puts("YES");
	printf("%d\n", anscnt);
	for (int i = 1; i <= anscnt; ++i) printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].w);
	return 0;
}
