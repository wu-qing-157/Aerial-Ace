#include <cstdio>
#include <map>

#define maxn 100010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int a[maxn], ans, k;
std::map<int, int> cnt[maxn];
void work(int l, int r, int id)
{
	if (l > r) return ;
	for (int ll = l, rr = r; ll <= rr; ++ll, --rr)
	{
		if (cnt[id][a[ll]] < k)
		{
			for (int i = l; i <= ll; ++i)
				--cnt[id][a[i]];
			work(ll + 1, r, id);
			cnt[id + 1].clear();
			for (int i = l; i < ll; ++i)
				++cnt[id + 1][a[i]];
			work(l, ll - 1, id + 1);
			return ;
		}
		if (cnt[id][a[rr]] < k)
		{
			for (int i = rr; i <= r; ++i)
				--cnt[id][a[i]];
			work(l, rr - 1, id);
			cnt[id + 1].clear();
			for (int i = rr + 1; i <= r; ++i)
				++cnt[id + 1][a[i]];
			work(rr + 1, r, id + 1);
			return ;
		}
	}
	cmax(ans, r - l + 1);
}
int main()
{
	int n, c;
	while (scanf("%d%d%d", &n, &c, &k) != EOF)
	{
		cnt[0].clear(); ans = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i), ++cnt[0][a[i]];
		work(1, n, 0);
		printf("%d\n", ans);
	}
	return 0;
}
