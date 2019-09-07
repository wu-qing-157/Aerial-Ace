#include <cstdio>
#include <cmath>
#include <cstring>

#define maxn 200010
typedef long long ll;
int pr[maxn / 10], prcnt, N, lim;
bool vis[maxn];
const int moha = 333331;
const int mod = 998244353;
struct Hash {
	int next, ans; ll key;
} mem[moha * 21], *tot = mem;
int last[moha];
int S(int n, int k)
{
	if (!k) return 1;
	if (n <= pr[k]) return n;
	if (n < 1ll * pr[k] * pr[k]) return S(n, k - 1) + n / pr[k];
	int ret;
	ll key = 1ll * n * prcnt + k - 1; int pos = key % moha;
	for (int iter = last[pos]; iter; iter = mem[iter].next)
		if (mem[iter].key == key) return mem[iter].ans;
	ret = S(n, k - 1) + S(n / pr[k], k);
	*++tot = (Hash) {last[pos], ret, key}; last[pos] = tot - mem;
	return ret;
}
int main()
{
	ll n; scanf("%lld", &n);
	N = sqrt(n);
	for (int i = 2; i <= N; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i;
		for (int j = 1; j <= prcnt && i * pr[j] <= N; ++j)
		{
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
	printf("%d\n", S(n, prcnt));
	return 0;
}
