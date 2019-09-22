#include <cstdio>

const int mod = 1e9 + 7;
#define maxn 3010
const int N = 3010;
int n, ans;
int conp[maxn], cnt[maxn], tot, pw[N], inp[N];
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
void dfs(int step, int sum, int prod, int lim)
{
	if (prod > sum + n - step + 1) return ;
	if (prod == sum + n - step + 1)
	{
		int pww = 1ll * pw[n] * inp[n - step + 1] % mod;
		for (int i = 1; i <= tot; ++i)
			pww = 1ll * pww * inp[cnt[i]] % mod;
		(ans += pww) %= mod;
		return ;
	}
	for (int i = lim; i > 1; --i)
	{
		if (i == conp[tot]) ++cnt[tot];
		else conp[++tot] = i, cnt[tot] = 1;
		dfs(step + 1, sum + i, prod * i, i);
		if (--cnt[tot] == 0) --tot;
	}
}
int main()
{
	int T; scanf("%d", &T);
	pw[0] = 1;
	for (int i = 1; i < maxn; ++i) pw[i] = 1ll * pw[i - 1] * i % mod;
	inp[maxn - 1] = qpow(pw[maxn - 1], mod - 2);
	for (int i = maxn - 1; i; --i) inp[i - 1] = 1ll * inp[i] * i % mod;
	for (; T; --T)
	{
		scanf("%d", &n); ans = tot = 0;
		dfs(1, 0, 1, n);
		printf("%d,", ans);
	}
	return 0;
}
