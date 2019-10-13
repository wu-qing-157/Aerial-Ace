#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int &a, int b) {
	a += b;
	return a >= mod ? a -= mod : a;
}

int sub(int &a, int b) {
	a -= b;
	return a < 0 ? a += mod : a;
}

int fpw(int a, int b) {
	int c = 1;
	while (b) {
		if (b & 1) c = 1ll * a * c % mod;
		a = 1ll * a * a % mod; b >>= 1;
	} return c;
}

int inv(int a) {
	return fpw(a, mod - 2);
}

int bf(int n, int m) {
	int sg = 0, g = 0;
	for (int i = m + 1; i <= n; i++) {
		g = ((i - 1) + inv(i) * 2ll * sg) % mod;
		add(sg, g);
	} return g;
}

int mt[3][3];

void work() {
	int n, m; scanf("%d%d", &n, &m);
	cout << "ans = " << bf(n, m) << endl;
	int ans = 0;
	
}

int main() {
	int T; scanf("%d", &T);
	while (T--) 
		work();
	return 0;
}
