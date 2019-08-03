#include <cstdio>
#include <algorithm>
#include <cstring>

const int maxn = 410, N = 410 * 510;
const int64_t MOD = 998244353;
int n, gcd;
int64_t fac[N], inv[N], ans, cur, det, ccnt[N];
int64_t a[maxn][maxn], dd[maxn][maxn];
int deg[maxn], rec[maxn];
int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}
void calc_det() {
    det = 1;
    for (int i = 1; i < n; ++i) {
        if (a[i][i] == 0) {
            for (int j = i + 1; j < n; ++j)
                if (a[j][i] != 0) {
                    det = MOD - det;
                    for (int k = i; k < n; ++k)
                        std::swap(a[i][k], a[j][k]);
                    break;
                }
        }
        if (a[i][i] == 0) {
            det = 0;
            break;
        }
        det = det * a[i][i] % MOD;
        for (int j = i + 1; j < n; ++j) {
            int64_t temp = a[j][i] * pow(a[i][i], MOD - 2) % MOD;
            for (int k = i; k < n; ++k)
                a[j][k] = (a[j][k] - a[i][k] * temp % MOD + MOD) % MOD;
        }
    }
}
int64_t c(int64_t n, int64_t m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}
int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] *= inv[i - 1]) %= MOD;
	for (int cas = 1; scanf("%d", &n) != EOF; cas++) {
        gcd = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
                scanf("%lld", &dd[i][j]);
                aa[i][j] = -(dd[i][j] > 0);
            }
        for (int i = 1; i <= n; i++) deg[i] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; i++)
                deg[i] -= aa[i][j], ddeg += dd[i][j];
		for (int i = 1; i <= n; ++i)
			a[i][i] += deg[i];
        calc_det();
        for (int i = 1; i <= n; i++) {
            (det *= ddeg[i]) %= MOD;
            for (int j = 1; j <= n; j++)
                (det *= inv[
        }
	}
	return 0;
}
/*
2
1 2
2 1
4
1 0 0 2
0 3 0 1
2 1 0 0
0 0 3 1
4
0 1 0 0
1 0 0 0
0 0 0 1
0 0 1 0

2
1 2
2 1
-3 -3 
2 -2 
-2 2 
8
4
1 0 0 2
0 3 0 1
2 1 0 0
0 0 3 1
-3 -4 -3 -4 
2 0 0 -2 
0 1 0 -1 
-2 -1 3 0 
0 0 -3 3 
864
4
0 1 0 0
1 0 0 0
0 0 0 1
0 0 1 0
-1 -1 -1 -1 
1 -1 0 0 
-1 1 0 0 
0 0 1 -1 
0 0 -1 1 
0

*/
