#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

#define maxn 1000010
#define maxm 100010
const int mod = 1e9 + 7;
int s[maxn];
int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn];
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
inline void build(int n, int m)
{
	int *x = wa, *y = wb, *t;
	for (int i = 1; i <= n; ++i) cnt[x[i] = s[i]]++;
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i; --i) sa[cnt[x[i]]--] = i;
	
	for (int j = 1; j < n || (j == 1 && m < n); j <<= 1, t = x, x = y, y = t)
	{
		memset(cnt + 1, 0, m << 2);
		int p = 0;
		for (int i = n - j + 1; i <= n; ++i) y[++p] = i;
		for (int i = 1; i <= n; ++i)
		{
			++cnt[x[i]];
			sa[i] > j ? y[++p] = sa[i] - j : 0;
		}
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i; --i) sa[cnt[x[y[i]]]--] = y[i];
		m = 0;
		for (int i = 1; i <= n; ++i)
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	for (int i = 1; i <= n; ++i) rank[sa[i]] = i;
}
std::vector<int> v[maxm], pos[maxm];
struct Queue {
	int id, now;
	inline bool operator < (const Queue &that) const {return rank[pos[id][now]] > rank[pos[that.id][that.now]];}
} ;
std::priority_queue<Queue> q;
int main()
{
	int n, m = 0; scanf("%d", &n);
	int tot = 0, pw, inp = qpow(365, mod - 2), ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		int sz; scanf("%d", &sz); tot += sz;
		for (int j = 0; j < sz; ++j)
		{
			int x; scanf("%d", &x);
			v[i].push_back(x);
		}
		for (int it : v[i])
		{
			s[++m] = it;
			pos[i].push_back(m);
		}
		s[++m] = 301;
	}
	pw = qpow(365, tot);
	build(m, 301);
	for (int i = 1; i <= n; ++i) q.push((Queue) {i, 0});
	for (int i = 1; i <= tot; ++i)
	{
		Queue now = q.top(); q.pop();
		ans = (ans + 1ll * pw * v[now.id][now.now]) % mod;
		if (now.now + 1 < v[now.id].size())
			q.push((Queue) {now.id, now.now + 1});
		pw = 1ll * pw * inp % mod;
	}
	printf("%d\n", ans);
	return 0;
}
