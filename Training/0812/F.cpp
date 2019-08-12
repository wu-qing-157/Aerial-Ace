#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 1000010
typedef long long ll;
char tmp[maxn];
int fail[maxn];
void build_fail(char *s, int len)
{
	fail[1] = 0; int p = 0; memset(fail, 0, (len + 1) << 2);
	for (int i = 2; i <= len; ++i)
	{
		while (p && s[p + 1] != s[i]) p = fail[p];
		s[p + 1] == s[i] ? ++p : 0; fail[i] = p;
	}
}
int build(char *a, int n)
{
	int i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n)
	{
		int tmp = a[(i + k) % n] - a[(j + k) % n];
		if (!tmp) k++;
		else
		{
			if (tmp > 0) i += k + 1;
			else j += k + 1;
			if (i == j) ++j;
			k = 0;
		}
	}
	j = std::min(i, j);
	int l = 0;
	for (int p = j; p < n; ++p) tmp[++l] = a[p];
	for (int p = 0; p < j; ++p) tmp[++l] = a[p];
	memcpy(a, tmp + 1, l);
	return j;
}
char s[maxn], t[maxn];
char ps[maxn], pt[maxn];
int to[maxn];
bool vis[maxn];
struct item {
	int x, mod;
} mem[maxn];
ll exgcd(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	ll res = exgcd(b, a % b, x, y);
	ll t = y;
	y = x - a / b * y;
	x = t;
	return res;
}
bool CRT(ll &r1, ll &m1, ll r2, ll m2)
{
	ll x, y, g = exgcd(m1, m2, x, y);
	if ((r2 - r1) % g != 0) return false;
	x = 1ll * (r2 - r1) * x % m2;
	if (x < 0) x += m2;
	x /= g;
	r1 += m1 * x;
	m1 *= m2 / g;
	return true;
}
int main()
{
	scanf("%s%s", s + 1, t + 1);
	int n = strlen(s + 1);
	memset(vis, 0, sizeof (vis));
	for (int i = 1, j = 1; i <= n; i += 2, ++j) to[j] = i;
	for (int i = 2, j = n / 2 + 1; i <= n; i += 2, ++j) to[j] = i;
	int tot = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
		{
			int len = 0; vis[i] = 1;
			ps[++len] = s[i];
			pt[len] = t[i];
			for (int j = to[i]; j != i; j = to[j])
				ps[++len] = s[j],
				pt[len] = t[j],
				vis[j] = 1;
			int pa = build(ps + 1, len);
			int pb = build(pt + 1, len);
			for (int i = 1; i <= len; ++i)
				if (ps[i] != pt[i])
				{
					puts("-1");
					return 0;
				}
			build_fail(ps, len);
			
			bool flag = 0;
			for (int i = fail[len]; ; i = fail[i])
			{
				if (len % (len - i) != 0) continue;
				int nn = len - i;
				mem[++tot] = (item) {(pa - pb + nn) % nn, nn};
				break;
			}
		}
	ll r = 0, m = 1;
	for (int i = 1; i <= tot; ++i)
		if (!CRT(r, m, mem[i].x, mem[i].mod))
		{
			puts("-1");
			return 0;
		}
	printf("%lld\n", r);
	return 0;
}
