#include <cstdio>
#include <map>
#include <bitset>
#include <algorithm>

unsigned long long k1, k2;
unsigned long long rng()
{
	unsigned long long k3 = k1, k4 = k2;
	k1 = k4;
	k3 ^= k3 << 23;
	k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
	return k2 + k4;
}
std::bitset<1000000010> vis, vis2;
std::map<int, int> id;
#define maxn 1000010
int hash[maxn], hcnt;
int a[maxn], b[maxn], cnt[maxn][2];
int c[maxn];
inline bool cmp(int i, int j)
{
	return cnt[i][0] + cnt[i][1] > cnt[j][0] + cnt[j][1];
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, p; scanf("%d%d%d", &n, &m, &p);
		if (p == 1)
		{
			hcnt = 0;
			for (int i = 1; i <= n; ++i)
				scanf("%d", a + i), hash[++hcnt] = a[i];
			for (int i = 1; i <= m; ++i)
				scanf("%d", b + i), hash[++hcnt] = b[i];
			std::sort(hash + 1, hash + hcnt + 1);
			hcnt = std::unique(hash + 1, hash + hcnt + 1) - hash - 1;
			for (int i = 1; i <= hcnt; ++i)
				cnt[i][0] = cnt[i][1] = 0;
			
			for (int i = 1; i <= n; ++i)
				a[i] = std::lower_bound(hash + 1, hash + hcnt + 1, a[i]) - hash, ++cnt[a[i]][0];
			for (int i = 1; i <= m; ++i)
				b[i] = std::lower_bound(hash + 1, hash + hcnt + 1, b[i]) - hash, ++cnt[b[i]][1];
			int now = 0;
			for (int i = 1; i <= hcnt; ++i)
				if (cnt[i][0] && cnt[i][1]) c[++now] = i;
			std::sort(c + 1, c + now + 1, cmp);
			int cc[2] = {n, m};
			for (int i = 1, t = 1; i <= now; ++i, t ^= 1)
				cc[t] -= cnt[c[i]][t];
			if (cc[0] > cc[1]) puts("Cuber QQ");
			else puts("Quber CC");
		}
		else
		{
			unsigned long long mod;
			scanf("%llu%llu%llu", &k1, &k2, &mod);
			for (int i = 1; i <= n; ++i) a[i] = rng() % mod, vis[a[i]] = 1;
			scanf("%llu%llu%llu", &k1, &k2, &mod);
			for (int i = 1; i <= m; ++i) b[i] = rng() % mod;
			
			int now = 0;
			for (int i = 1; i <= m; ++i)
				if (vis[b[i]])
				{
					if (!id[b[i]]) id[b[i]] = ++now, c[now] = id[b[i]], cnt[now][1] = 1;
					else ++cnt[id[b[i]]][1];
					vis2[b[i]] = 1;
				}
			for (int i = 1; i <= n; ++i)
				if (vis2[a[i]]) ++cnt[id[a[i]]][0];

			std::sort(c + 1, c + now + 1, cmp);
			int cc[2] = {n, m};
			for (int i = 1, t = 1; i <= now; ++i, t ^= 1)
				cc[t] -= cnt[c[i]][t];
			if (cc[0] > cc[1]) puts("Cuber QQ");
			else puts("Quber CC");

			id.clear();
			for (int i = 1; i <= now; ++i) cnt[i][0] = cnt[i][1] = 0;
			for (int i = 1; i <= n; ++i) vis[a[i]] = 0;
			for (int i = 1; i <= m; ++i) vis2[b[i]] = 0;
		}
	}
	return 0;
}
