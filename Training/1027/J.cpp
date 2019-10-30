#include <cstdio>
#include <vector>

#define maxn 1000010
typedef long long ll;
bool vis[maxn];
int pr[maxn], prcnt, mp[maxn];
std::vector<int> v[maxn];
int main()
{
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) mp[pr[++prcnt] = i] = i;
		for (int j = 1; j <= prcnt && i * pr[j] < maxn; ++j)
		{
			vis[i * pr[j]] = 1;
			mp[i * pr[j]] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
	int n; scanf("%d", &n);
	const int oo = 1e6;
	for (int i = 1; i <= n; ++i)
	{
		int x; scanf("%d", &x);
		while (x != 1)
		{
			int now = mp[x];
			v[now].push_back(i);
			while (x % now == 0) x /= now;
		}
	}
	ll ans = 0;
	for (int i = 2; i <= oo; ++i)
		if (v[i].size())
		{
			int lst = 0;
			ans += 1ll * n * (n + 1) / 2;
			for (int it : v[i])
			{
				ans -= 1ll * (it - lst) * (it - lst - 1) / 2;
				lst = it;
			}
			ans -= 1ll * (n + 1 - lst) * (n + 1 - lst - 1) / 2;
		}
	printf("%lld\n", ans);
	return 0;
}
