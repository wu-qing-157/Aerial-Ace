#include <cstdio>

const int mod = 998244353;
const int inv2 = 499122177;
void fwt(int n, int *x, bool inv = false)
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < (1 << n); ++j)
			if ((j >> i) & 1)
			{
				int p = x[j ^ (1 << i)], q = x[j];
				if (!inv)
				{
					x[j ^ (1 << i)] = (p - q + mod) % mod;
					x[j] = (p + q) % mod;
				}
				else
				{
					x[j ^ (1 << i)] = 1ll * (p + q) * inv2 % mod;
					x[j] = 1ll * (q - p + mod) * inv2 % mod;
				}
			}
}
void solve(int n, int *a)
{
	fwt(n, a);
	for (int i = 0; i < (1 << n); ++i)
		a[i] = 1ll * a[i] * a[i] % mod * a[i] % 998244353;
	fwt(n, a, 1);
}
#define maxn 1048576
int a[maxn];
int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; ++i) a[i] = 1;
		int len = 0, ll = 1;
		for (int nn = n; nn; nn >>= 1, ++len, ll <<= 1);
		for (int i = n; i < ll; ++i) a[i] = 0;
		solve(len, a);
		
		int sum = 0, ans = 0;
		for (int i = 0; i < ll; ++i) sum = (sum + 1ll * i * a[i]) % mod;
		for (int i = 0; i < ll; ++i) ans = (ans + 1ll * (sum - i + mod) * i % mod * a[i]) % mod;
		printf("%d\n", int(1ll * ans * 499122177 % mod));
		/*
		int ans1=0,ans2=0;
		for(int i=0;i<ll;i++)
			ans1=(ans1+1ll*i*a[i])%mod,ans2=(ans2+1ll*i*i%mod*a[i])%mod;
		printf("%lld\n",(1ll*ans1*ans1-ans2+mod)%mod*(mod+1>>1)%mod);
		*/
	}
	return 0;
}
