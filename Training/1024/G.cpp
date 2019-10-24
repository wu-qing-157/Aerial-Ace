#include <bits/stdc++.h>

struct Matrix {
	int m, n;
	int a[3][3];
	Matrix(int x, int y) {
		clear(x, y);
	}
	int &at(int i, int j) {
		return a[i][j];
	}
	void clear(int x, int y) {
		m = x; n = y;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				a[i][j] = 0;		
	}
};

const int mod = 1e9 + 7;

Matrix mul(Matrix a, Matrix b) {
	int m = a.m, n = a.n, s = b.n;
	Matrix c(m, s);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < s; j++)
			for (int k = 0; k < n; k++) {
				c.at(i, j) += int(1ll * a.at(i, k) * b.at(k, j) % mod);
				if (c.at(i, j) >= mod) c.at(i, j) -= mod;
			}
	return c;
}

Matrix pow(Matrix a, long long b) {
	Matrix c(a.m, a.n);
	for (int i = 0; i < a.m; i++) c.at(i, i) = 1;
	while (b) {
		if (b & 1) c = mul(a, c);
		b >>= 1; a = mul(a, a);
	} return c;
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		long long L, R, K; 
		scanf("%lld%lld%lld", &L, &R, &K);
		
		Matrix g(2, 2), tg(2, 2);
		g.at(0, 0) = 1;
		g.at(1, 1) = 1;
		tg.at(0, 0) = 1;
		tg.at(0, 1) = 1;
		tg.at(1, 0) = 1;

		g = mul(pow(tg, K - 1), g);
		
		Matrix f(3, 1), tf(3, 3);
		tf.at(0, 0) = (g.at(0, 0) + g.at(1, 0)) % mod;
		tf.at(0, 1) = g.at(0, 0);
		tf.at(1, 0) = (g.at(1, 1) + g.at(0, 1)) % mod;
		tf.at(1, 1) = g.at(0, 1);
		for (int i = 0; i < 3; i++)
			tf.at(2, i) = 1;
		
		long long KR = R / K, KL = (L - 1) / K, ans = 0;
		
		
		f.at(0, 0) = (g.at(0, 0) + g.at(1, 0)) % mod;
		f.at(1, 0) = (g.at(0, 1) + g.at(1, 1)) % mod;
		f.at(2, 0) = 0;
		f = mul(pow(tf, KR), f);
		
		(ans += f.at(2, 0)) %= mod;
		
		f.clear(3, 1); 
		
		f.at(0, 0) = (g.at(0, 0) + g.at(1, 0)) % mod;
		f.at(1, 0) = (g.at(0, 1) + g.at(1, 1)) % mod;
		f.at(2, 0) = 0;
		f = mul(pow(tf, KL), f);
		(ans -= f.at(2, 0)) %= mod;
		
		(ans += mod) %= mod;
		printf("Case %d: %lld\n", t, ans);
	}
	return 0;	
}

