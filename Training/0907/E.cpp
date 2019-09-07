#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 500010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
int tr[maxn];
int a[maxn], hash[maxn], hcnt, ans[maxn];
void modify(int x, int v)
{
	for (; x; x -= x & -x) cmax(tr[x], v);
}
int query(int x)
{
	int ret = 0;
	for (; x <= hcnt; x += x & -x) cmax(ret, tr[x]);
	return ret;
}
int main()
{
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i), hash[++hcnt] = a[i];
	std::sort(hash + 1, hash + hcnt + 1);
	hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
	for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(hash + 1, hash + hcnt + 1, a[i]) - hash;
	for (int i = n; i; --i)
	{
		int pos = std::lower_bound(hash + 1, hash + hcnt + 1, hash[a[i]] + m) - hash;
		ans[i] = query(pos) - i - 1;
		ans[i] < 0 ? ans[i] = -1 : 0;
		modify(a[i], i);
	}
	for (int i = 1; i <= n; ++i) printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
