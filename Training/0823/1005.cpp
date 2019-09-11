#include <cstdio>
#include <cmath>

const int mod = 1e9 + 7;
const int inv6 = 166666668;
#define maxn 1500010
int miu[maxn], smiu[maxn], pr[maxn / 10], prcnt, lim, N;
bool vis[maxn];
int hash[maxn];
int vihash[maxn], timer;
inline int Sum(int x)
{
	return 1ll * x * (x + 1) / 2 % mod;
}
int Miu(int n)
{
	if (n < maxn) return smiu[n];
	if (vihash[N / n] == timer) return hash[N / n];

	vihash[N / n] = timer;
	int ret = 1;
	for (int i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		int ps = (Sum(j) - Sum(i - 1) + mod) % mod;
		(ret += mod - 1ll * ps * Miu(n / i) % mod) %= mod;
	}
	return hash[N / n] = ret;
}
inline int P(int x)
{
	return 1ll * x * (x + 1) % mod * (x - 1) % mod * inv6 % mod;
}
int main()
{
	int T; scanf("%d", &T);
	miu[1] = 1; smiu[1] = 1;
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, miu[i] = -1;
		smiu[i] = (smiu[i - 1] + miu[i] * i + mod) % mod;
		for (int j = 1; j <= prcnt && 1ll * i * pr[j] < maxn; ++j)
		{
			vis[i * pr[j]] = 1;
			if (i % pr[j]) miu[i * pr[j]] = -miu[i];
			else
			{
				miu[i * pr[j]] = 0;
				break;
			}
		}
	}
	for (timer = 1; timer <= T; ++timer)
	{
		scanf("%d%*d%*d", &N);
		int ans = 0, last = 0;
		for (int i = 1, j; i <= N; i = j + 1)
		{
			j = N / (N / i);
			int Ph = Miu(j);
			int fs = P(N / i);
			ans = (ans + 1ll * (Ph - last + mod) * fs) % mod;
			last = Ph;
		}
		printf("%d\n", ans);
	}
	return 0;
}
