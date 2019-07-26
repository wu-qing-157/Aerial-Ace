#include <cstdio>
#include <cstring>

const int mod = 1e9 + 7;
#define maxn 110
#define maxm 10010
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxm], *ecnt = e, *rlast[maxn], re[maxm], *recnt = re;
int deg[maxn];
inline void link(int a, int b)
{
	++deg[a];
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
	*++recnt = (Edge) {rlast[b], a}; rlast[b] = recnt;
}
int sg[maxn];
bool mex[maxn];
int f[maxn][maxn][129];
const int maxs = 20010;
int pw[maxs], inv[maxs], q[maxn];
inline int C(int n, int m)
{
	return 1ll * pw[n] * inv[m] % mod * inv[n - m] % mod;
}
int main()
{
	int T; scanf("%d", &T);
	pw[0] = 1;
	for (int i = 1; i < maxs; ++i) pw[i] = 1ll * pw[i - 1] * i % mod;
	inv[maxs - 1] = qpow(pw[maxs - 1], mod - 2);
	for (int i = maxs - 1; i; --i) inv[i - 1] = 1ll * inv[i] * i % mod;
	for (; T; --T)
	{
		int n, m, s; scanf("%d%d%d", &n, &m, &s);
		memset(last, 0, (n + 1) * sizeof (Edge *)); ecnt = e;
		memset(rlast, 0, (n + 1) * sizeof (Edge *)); recnt = re;
		memset(deg, 0, (n + 1) << 2);
		memset(f, 0, sizeof (f));
		for (int i = 1; i <= m; ++i)
		{
			int a, b; scanf("%d%d", &a, &b); ++a; ++b;
			link(a, b);
		}
		int head = 0, tail = 0;
		for (int i = 1; i <= n; ++i) if (!deg[i]) sg[q[++tail] = i] = 0;
		while (head < tail)
		{
			int now = q[++head];
			for (Edge *iter = rlast[now]; iter; iter = iter -> next)
				if (--deg[iter -> to] == 0) q[++tail] = iter -> to;
			memset(mex, 0, (n + 1));
			for (Edge *iter = last[now]; iter; iter = iter -> next)
				mex[sg[iter -> to]] = 1;
			for (int i = 0; i <= n; ++i) if (!mex[i]) {sg[now] = i; break;}
		}
		f[0][0][0] = 1;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= i; ++j)
				for (int S = 0; S < 128; ++S)
				{
					(f[i][j][S] += f[i - 1][j - 1][S ^ sg[i]]) %= mod;
					(f[i][j - 1][S] += f[i - 1][j - 1][S]) %= mod;
				}
		}
		int ans = 0;
		for (int i = s & 1; i <= s && i <= n; i += 2)
			ans = (ans + 1ll * f[n][i][0] * C((s - i) / 2 + n - 1, n - 1)) % mod;
		printf("%d\n", ans);
	}
	return 0;
}
/*
3
2 1 3
0 1
4 3 3
0 1
1 2
2 3
3 3 5
0 1
1 2
0 2
*/
