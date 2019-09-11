#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;
#define maxn 1500010
int miu[maxn], smiu[maxn], pr[maxn / 10], prcnt, N;
bool vis[maxn];
int hash[maxn];
int vihash[maxn], timer;
int Miu(int n)
{
	if (n < maxn) return smiu[n];
	if (vihash[N / n] == timer) return hash[N / n];
	
	vihash[N / n] = timer;
	int ret = 1;
	for (int i = 2, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		ret -= (j - i + 1) * Miu(n / i);
	}
	return hash[N / n] = ret;
}
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
char K[maxn];
int m, pw[12];
inline int Po(int d)
{
	if (d == 1)
	{
		int ret = 0;
		for (int i = 0; i < m; ++i)
			(ret = 10ll * ret + K[i] - '0') % mod;
		--ret; ret += mod; ret %= mod;
		return ret;
	}
	int inv = qpow(d - 1, mod - 2), up = 1;
	pw[0] = 1;
	for (int i = 1; i < 10; ++i)
		pw[i] = 1ll * pw[i - 1] * d % mod;
	for (int i = 0; i < m; ++i)
		up = 1ll * qpow(up, 10) * pw[K[i] - '0'] % mod;
	--up; up += mod; up %= mod;
	up = 1ll * up * inv % mod * d % mod;
	return (up - d + mod) % mod;
}
int main()
{
	int T; scanf("%d", &T);
	miu[1] = 1; smiu[1] = 1;
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, miu[i] = -1;
		smiu[i] = (smiu[i - 1] + miu[i] + mod) % mod;
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
		scanf("%d%s", &N, K);
		m = strlen(K);
		int ans = 0, last = 0;
		for (int i = 1, j; i <= N; i = j + 1)
		{
			j = N / (N / i);
			int Ph = Miu(j);
			int fs = Po(N / i);
			ans = (ans + 1ll * (Ph - last + mod) * fs) % mod;
			last = Ph;
		}
		printf("%d\n", ans);
	}
	return 0;
}
