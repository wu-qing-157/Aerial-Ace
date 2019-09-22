#include <cstdio>

#define maxn 300010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
long long ans;
int a[maxn], k;
int cnt[maxn];
void solve(int l, int r)
{
	if (l == r) return (void) (ans += a[l] - 1 <= k);
	int mid = l + r >> 1;
	//printf("%d %d %d\n", l, mid, r);
	for (int i = mid + 1, j1 = mid, j2 = mid, maxx = 0; i <= r; ++i)
	{
		cmax(maxx, a[i]);
		bool flag = ++cnt[a[i]] == 2;
		while (j1 >= l && !cnt[a[j1]]) ++cnt[a[j1--]];
		while (j1 < mid && flag) --cnt[a[++j1]], flag = a[j1] != a[i];
		while (j2 >= l && a[j2] < maxx) --j2;
		if (flag) break;
		
		int ll = dmax(j1, j2), rr = dmin(i - maxx + k + 1, mid);
		
		ans += dmax(rr - ll, 0);
		
		//printf("left %d %d %d %d\n", i, j1, j2, rr);
	}
	for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
	for (int i = mid, j1 = mid + 1, j2 = mid + 1, maxx = 0; i >= l; --i)
	{
		cmax(maxx, a[i]);
		bool flag = ++cnt[a[i]] == 2;
		while (j1 <= r && !cnt[a[j1]]) ++cnt[a[j1++]];
		while (j1 > mid + 1 && flag) --cnt[a[--j1]], flag = a[j1] != a[i];
		while (j2 <= r && a[j2] < maxx) ++j2;
		
		if (flag) break;
		int ll = dmin(j1, j2), rr = dmax(mid + 1, i + maxx - k - 1);
		
		ans += dmax(ll - rr, 0);
		
		//printf("right %d %d %d\n", i, ll, rr);
	}
	for (int i = l; i <= r; ++i) cnt[a[i]] = 0;
	solve(l, mid);
	solve(mid + 1, r);
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d%d", &n, &k);
		ans = 0;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		solve(1, n);
		printf("%lld\n", ans);
	}
	return 0;
}
