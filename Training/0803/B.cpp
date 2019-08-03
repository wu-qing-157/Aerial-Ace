#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long ll;
#define maxn 100010
int l[maxn];
std::vector<ll> v[maxn], sum[maxn];
int r[maxn];
ll s[maxn];
inline bool cmp(int a, int b)
{
	return v[a].size() > v[b].size();
}
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
struct Frac {
	ll a, b;
	inline bool operator < (const Frac &that) const
	{
		return a * that.b - b * that.a < 0;
	}
	inline void simple() {ll gcc = gcd(a, b); a /= gcc; b /= gcc;}
} ans;
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i)
		{
			scanf("%d", l + i);
			r[i] = i;
			sum[i].clear();
			v[i].clear();
		}
		memset(s, 0, (m + 1) << 3);
		for (int i = 1; i <= n; ++i)
		{
			int a, b; scanf("%d%d", &a, &b);
			v[b].push_back(a);
		}
		std::sort(r + 1, r + m + 1, cmp);
		for (int i = 1; i <= m; ++i)
		{
			std::sort(v[i].begin(), v[i].end());
			std::reverse(v[i].begin(), v[i].end());
			ll tmp = 0; int num = 0;
			for (auto it : v[i])
			{
				tmp += it; ++num;
				sum[i].push_back(num >= l[i] ? tmp : 0);
			}
			s[i] = num >= l[i] ? tmp : 0;
			//printf("%lld\n", s[i]);
		}
		Frac ans = (Frac) {0, 1};
		ll tot = 0;
		for (int i = 1, j = m; i <= n; ++i)
		{
			while (j && v[r[j]].size() < i) --j;
			for (int k = 1; k <= j; ++k)
				tot += sum[r[k]][i - 1] - (i > 1 ? sum[r[k]][i - 2] : 0);
			//printf("%lld %d %d\n", tot, i, j);
			Frac now = (Frac) {tot, i};
			now.simple();
			ans < now ? ans = now, 1 : 0;
		}
		printf("%lld/%lld\n", ans.a, ans.b);
	}
	return 0;
}
/*
2
2 1
2
7 1
2 1

3 2
1 2
2 1
5 2
3 2
*/
