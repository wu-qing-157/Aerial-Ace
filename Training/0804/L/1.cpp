#include <cstdio>
#include <cstdint>
#include <utility>

const int N = 1e6 + 10, M = 2e6 + 10;
const int64_t MOD = 998244353, G = 3;
int rev[N];

int64_t pow(int64_t a, int64_t exp) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
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

void ntt_main(int n, int64_t *a, int64_t *b, int64_t *c, int64_t *d) {
     static int nn, len;
     len = 0;
     for (nn = 1; nn <= n * 4; nn <<= 1) len++;
     for (int i = n; i < nn; i++) a[i] = b[i] = c[i] = d[i] = 0;
     rev[0] = 0;
     for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
     ntt(a, nn, 1);
     ntt(b, nn, 1);
     ntt(c, nn, 1);
     ntt(d, nn, 1);
     for (int i = 0; i < nn; i++) a[i] = a[i] * b[i] % MOD * c[i] % MOD * d[i] % MOD;
     ntt(a, nn, -1);
}

int n, m, cnt[4];
int64_t a[N], b[4][N], fac[M], inv[M], ans;

int64_t c(int n, int m) {
    if (m == -1) return n == -1 ? 1 : 0;
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    static int T;
    scanf("%d", &T);
    fac[0] = inv[0] = inv[1] = 1;
    for (int i = 1; i < M; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < M; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < M; i++) (inv[i] *= inv[i - 1]) %= MOD;
    while (T--) {
        cnt[1] = cnt[2] = cnt[3] = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%lld", a + i);
        for (int i = 0; i < m; i++) {
            static int op;
            scanf("%d", &op);
            cnt[op]++;
        }
        for (int i = 0; i < n; i++)
            for (int j : { 1, 2, 3 }) {
                if (i % j == 0)
                    b[j][i] = c(i / j + cnt[j] - 1, cnt[j] - 1);
                else
                    b[j][i] = 0;
            }
        // for (int i = 0; i < n; i++)
            // printf("abcd %lld %lld %lld %lld\n", a[i], b[1][i], b[2][i], b[3][i]);
        ntt_main(n, a, b[1], b[2], b[3]);
        // for (int i = 0; i < n; i++) printf("%lld%c", a[i], " \n"[i == n - 1]);
        ans = 0;
        for (int i = 0; i < n; i++) ans ^= (i + 1) * a[i];
        printf("%lld\n", ans);
    }
    return 0;
}
