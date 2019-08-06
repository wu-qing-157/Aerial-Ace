#include <cstdio>

namespace poly {
	const int P = 998244353;
	const int E = 3;
	const int maxn = 1e6 + 10;
	inline int inc(int a, int b) {a += b; return a >= P ? a - P : a;}
	inline int dec(int a, int b) {a -= b; return a < 0 ? a + P : a;}
	typedef long long ll;
	inline int mul(int a, int b) {return int(ll(a) * b % P);}
	inline int ksm(int a, int b, int c = 1) {
		for (; b; a = mul(a, a), b >>= 1)
			if (b & 1) c = mul(a, c);
		return c;
	}
	void dft(int *f, int n, int R) {
		static int rev[maxn], Last = 0;
		if (n != Last)
			for (int i = 1; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1 ? (n >> 1) : 0);
		Last = n;
		for (int i = 0; i < n; ++i) if (i < rev[i]) std::swap(f[i], f[rev[i]]);
		for (int i = 1; i < n; i <<= 1)
			for (int e = ksm(R, (P - 1) / (i << 1)), j = 0; j < n; j += i << 1)
				for (int x = 1, k = j; k < j + i; ++k, x = mul(x, e)) {
					int a1 = f[k], a2 = f[k + i] * ll(x) % P;
					f[k] = inc(a1, a2); f[k + i] = dec(a1, a2);
				}
		if (R != E) for (int I = ksm(n, P - 2), i = 0; i < n; ++i) f[i] = mul(f[i], I);
	}
	void conv(int *f, int *g, int *h, int n, int m) {
		static int F[maxn], G[maxn];
		int s = n + m - 1; while (s != (s & -s)) s += s & -s;
		memset(F, 0, sizeof (int) * s); memset(G, 0, sizeof (int) * s);
		for (int i = 0; i < n; ++i) F[i] = f[i];
		for (int i = 0; i < m; ++i) G[i] = g[i];
		dft(F, s, E); dft(G, s, E);
		for (int i = 0; i < s; ++i) h[i] = mul(F[i], G[i]);
		dft(h, s, ksm(E, P - 2));
	}
	void getdao(int *f, int *g, int n) {
		for (int i = 0; i < n - 1; ++i) g[i] = mul(i + 1, f[i + 1]); g[n - 1] = 0;
	}
	void getfen(int *f, int *g, int n) {
		static int inv[maxn], now = 1; inv[1] = 1;
		while (now < n) ++now, inv[now] = dec(0, mul(inv[P % now], P / now));
		for (int i = n - 1; i; --i) g[i] = mul(f[i - 1], inv[i]); g[0] = 0;
	}
	void getinv(int *f, int *g, int n) {
		static int h[maxn];
		if (n == 1) return void(g[0] = ksm(f[0], P - 2));
		else
		{
			int m = n + 1 >> 1;
			getinv(f, g, m);
			conv(f, g, h, n, m);
			for (int i = 0; i < n; ++i) h[i] = dec(0, h[i]); h[0] = inc(h[0], 2);
			conv(g, h, g, m, n);
		}
	}
}

const int maxn = 1e6 + 10;
int main()
{
	
	return 0;
}
