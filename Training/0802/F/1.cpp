#include <cstdio>
#include <cstdint>
#include <algorithm>

const int N = 4e5 + 10;
const int64_t MOD = 998244353, G = 3;

int rev[N];

int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

void ntt(int64_t *p, int n, int idft) {
    for (int i = 0; i < n; i++) if (i < rev[i]) std::swap(p[i], p[rev[i]]);
    for (int j = 1; j < n; j <<= 1) {
        static int64_t wn1, w, t0, t1;
        wn1 = pow(G, (MOD - 1) / (j << 1));
        if (idft == -1) wn1 = pow(wn1, MOD - 2);
        for (int i = 0; i < n; i += j << 1) {
            w = 1;
            for (int k = 0; k < j; k++) {
                t0 = p[i + k];
                t1 = w * p[i + j + k] % MOD;
                p[i + k] = (t0 + t1) % MOD;
                p[i + j + k] = (t0 - t1 + MOD) % MOD;
                (w *= wn1) %= MOD;
            }
        }
    }
    if (idft == -1) {
        int64_t nInv = pow(n, MOD - 2);
        for (int i = 0; i < n; i++) (p[i] *= nInv) %= MOD;
    }
}

void ntt_solve(int64_t *a, int64_t *b, int n, int m) {
    static int64_t aa[N], bb[N];
    static int nn, len;
    len = 0;
    for (nn = 1; nn <= m + n; nn <<= 1) len++;
    for (int i = 0; i < nn; i++) {
        aa[i] = i < n ? a[i] : 0;
        bb[i] = i < m ? b[i] : 0;
    }
    rev[0] = 0;
    for (int i = 0; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    ntt(aa, nn, 1);
    ntt(bb, nn, 1);
    for (int i = 0; i < nn; i++) (aa[i] *= bb[i]) %= MOD;
    ntt(aa, nn, -1);
    for (int i = 0; i < n; i++) a[i] = aa[i];
}

int n, m, c[N];
int64_t fac[N], inv[N], da, a[N], b[N];

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] *= inv[i - 1]) %= MOD;
}

int main() {
    init();
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i <= n; i++) scanf("%d", c + i);
        scanf("%d", &m);
        da = 0;
        for (int i = 1; i <= m; i++) {
            static int tmp;
            scanf("%d", &tmp);
            (da += tmp) %= MOD;
        }
        for (int i = 0; i <= n; i++) a[i] = c[i] * fac[i] % MOD;
        std::reverse(a, a + n + 1);
        for (int i = 0; i <= n; i++) b[i] = pow((MOD - da) % MOD, i) * inv[i] % MOD;
        ntt_solve(a, b, n + 1, n + 1);
        std::reverse(a, a + n + 1);
        for (int i = 0; i <= n; i++) (a[i] *= inv[i]) %= MOD;
        for (int i = 0; i <= n; i++)
            printf("%lld ", a[i]);
        puts("");
    }
    return 0;
}
