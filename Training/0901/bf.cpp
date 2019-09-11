#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;
const int inv6 = 166666668;
#define maxn 1500010
#define maxm 3000010
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
int m, rem1, rem2, h2[maxm], pre[maxm], htt[maxm];
int inv[maxm], upp[maxm];
inline int Po(int d)
{
	if (d == 1) return (rem1 - 1 + mod) % mod;
	int up = d < maxm ? upp[d] : qpow(d, rem2);
	int iv = d < maxm ? inv[d - 1] : qpow(d - 1, mod - 2);
	--up; up += mod; up %= mod;
	up = 1ll * up * iv % mod * d % mod;
	return (up - d + mod) % mod;
}
inline int Poi(int d)
{
	if (d < maxm) return pre[d];
	if (htt[N / d] == timer) return h2[N / d];
	htt[N / d] = timer;
	return h2[N / d] = Po(d);
}
inline int Sum2(int x)
{
	return 1ll * x * (x + 1) % mod * (2 * x + 1) % mod * inv6 % mod;
}
inline int Mi(int n)
{
	int ans = 0, last = 0;
	for (int i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		int ps = Miu(j);
		int fs = Poi(n / i);
		ans = (ans + 1ll * (ps - last + mod) * fs) % mod;
		last = ps;
	}
	return ans;
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
	inv[1] = 1; for (int i = 2; i < maxn; ++i)
		inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	for (timer = 1; timer <= T; ++timer)
	{
		scanf("%d%s", &N, K);
		m = strlen(K);
		rem1 = rem2 = 0;
		for (int i = 0; i < m; ++i)
			rem1 = rem1 * 10ll + (K[i] - '0') % mod,
			rem2 = rem2 * 10ll + (K[i] - '0') % (mod - 1);
		int ans = 0, last = 0;
	upp[1] = 1;
	for (int i = 2; i < maxm; ++i)
	{
		if (!vis[i]) upp[i] = qpow(i, rem2);
		for (int j = 1; j <= prcnt && 1ll * i * pr[j] < maxm; ++j)
		{
			vis[i * pr[j]] = 1;
			upp[i * pr[j]] = 1ll * upp[i] * upp[pr[j]] % mod;
			if (i % pr[j] == 0) break;
		}
	}
		for (int i = 1; i < maxm; ++i) pre[i] = Po(i);
		for (int id = 1, jd; id <= N; id = jd + 1)
		{
			jd = N / (N / id);
			int Ph = Sum2(jd);
			int fs = Mi(N / id);
			ans = (ans + 1ll * (Ph - last + mod) * fs) % mod;
			last = Ph;
		}
		printf("%d\n", ans);
	}
	return 0;
}
