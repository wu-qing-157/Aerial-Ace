#include<vector>
#include<cstdio>
#include<cmath>

using namespace std;

const int MOD = 100003;

const int maxn = 2e5 + 10;

typedef long long ll;

int s[maxn], ID;

vector<ll>g[maxn];

int fpw(int a, int b, int p) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = 1ll * ans * a % p;
		a = 1ll * a * a % p; b >>= 1;
	} return ans;
}

using number = double;

const int EX = 15, POW2 = (1 << EX) - 1, N = 4e5 + 10;
const number pi = acos(-1);

int nn, rev[N];

struct complex {
	number r, i;
	complex() : r(0), i(0) {}
	complex(number theta) : r(cos(theta)), i(sin(theta)) {}
	complex(number r, number i) : r(r), i(i) {}
	friend complex operator + (const complex &a, const complex &b) {
		return complex(a.r + b.r, a.i + b.i);
	}
	friend complex operator - (const complex &a, const complex &b) {
		return complex(a.r - b.r, a.i - b.i);
	}
	friend complex operator * (const complex &a, const complex &b) {
		return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
	}
	complex operator ~ () const {
		return complex(r, -i);
	}
} w[N];

void prepare(int len) {
	int x = 0;
	for (nn = 1; nn < len; nn <<= 1) x++;
	for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (x - 1));
	for (int i = 0; i < nn; i++) w[i] = complex(2 * pi * i / nn);
}

void fft(complex * a) {
	for (int i = 0; i < nn; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int i = 2, d = nn >> 1; i <= nn; i <<= 1, d >>= 1) 
		for (int j = 0; j < nn; j += i) {
			complex *l = a + j, *r = a + j + (i >> 1), *p = w, tp;
			for (int k = 0; k < (i >> 1); k++, l++, r++, p += d)
				tp = *r * *p, *r = *l - tp, *l = *l + tp;
		}
}

void mul2(vector<ll>&A, vector<ll>&B, vector<ll>&C) {
	int n = A.size(), m = B.size();
	static complex a[N], b[N], Da[N], Db[N], Dc[N], Dd[N];
	prepare(n + m);
	for (int i = 0; i < nn; i++) a[i] = i < n ? complex(A[i] & POW2, A[i] >> EX) : complex(0, 0);
	for (int i = 0; i < nn; i++) b[i] = i < m ? complex(B[i] & POW2, B[i] >> EX) : complex(0, 0);
	fft(a); fft(b);
	for (int i = 0; i < nn; i++) {
		int j = (nn - i) & (nn - 1);
		static complex da, db, dc, dd;
		da = (a[i] + ~a[j]) * complex(0.5, 0);
		db = (a[i] - ~a[j]) * complex(0, -0.5);
		dc = (b[i] + ~b[j]) * complex(0.5, 0);
		dd = (b[i] - ~b[j]) * complex(0, -0.5);
		Da[j] = da * dc, Db[j] = da * dd, Dc[j] = db * dc, Dd[j] = db * dd;
	}
	for (int i = 0; i < nn; i++) a[i] = Da[i] + Db[i] * complex(0, 1);
	for (int i = 0; i < nn; i++) b[i] = Dc[i] + Dd[i] * complex(0, 1);
	fft(a); fft(b);
	C.clear();
	C.resize(n + m - 1);
	for (int i = 0; i < n + m - 1; i++) {
		static ll da, db, dc, dd;
		da = ll(a[i].r / nn + 0.5) % MOD;
		db = ll(a[i].i / nn + 0.5) % MOD;
		dc = ll(b[i].r / nn + 0.5) % MOD;
		dd = ll(b[i].i / nn + 0.5) % MOD;
		C[i] = (da + ((db + dc) << EX) + (dd << (EX << 1))) % MOD;
	}
} 

void mul(vector<ll>&A, vector<ll>&B, vector<ll>&C) {
	int n = A.size(), m = B.size();
	if (n > 100) return mul2(A, B, C);
	
	C.clear();
	C.resize(n + m - 1);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++)
			C[i + j] += A[i] * B[j];
	for (int i = 0; i < n + m - 1; i++)
		C[i] %= MOD;
}



int solve(int l, int r) {
	if (l == r) return l;
	else {
		int mid = (l + r) / 2;
		int L = solve(l, mid);
		int R = solve(mid + 1, r);
		mul(g[L], g[R], g[++ID]);
		return ID;
	}
}

int fac[maxn], ifac[maxn];

int C(int n, int m) {
	return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}

void init() {
	fac[0] = ifac[0] = 1;
	for (int i = 1; i < maxn; i++)	{
		fac[i] = 1ll * fac[i - 1] * i % MOD;
		ifac[i] = fpw(fac[i], MOD - 2, MOD);
	}
}

int main() {
	init();
	int N, a, Q;
	scanf("%d%d%d", &N, &a, &Q);

	for (int i = 1; i <= N; i++)
		scanf("%d", &s[i]);
	for (int i = 1; i <= N; i++) {
		g[i].resize(2);
		g[i][0] = 1;
		g[i][1] = fpw(a, s[i], MOD);
	}
	ID = N;
	int x = solve(1, N);
	
	int ia = fpw(a, MOD - 2, MOD);
	int ia_1 = fpw(a - 1, MOD - 2, MOD);
	/*
	for (int i = 0; i < g[x].size(); i++)
		cout << g[x][i] << ' ';
	cout << endl;
	*/
	while (Q--) {
		int k; scanf("%d", &k);
		int ans = 0;
		ans += 1ll * g[x][k] * ia % MOD;
		ans += 1ll * ans * ia_1 % MOD;
		ans %= MOD;
		ans -= 1ll * ia_1 * C(N, k) % MOD;
//		cout << C(N, k) << endl;
		ans %= MOD;
		ans += MOD;
		ans %= MOD;
		printf("%d\n", ans);
	}
	return 0;
}
