#include <cassert>
#include <cstdio>
#include <cstdint>
#include <algorithm>

const int N = 4e5 + 10;
const int64_t MOD1 = 998244353, MOD2 = 1045430273, MOD3 = 1051721729;
int rev[N];

int64_t extend_gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int64_t res = extend_gcd(b, a % b, x, y);
    int64_t t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

int64_t crt(int64_t r1, int64_t m1, int64_t r2, int64_t m2) {
    int64_t x, y, g = extend_gcd(m1, m2, x, y);
    x = (r2 - r1) * x % m2;
    if (x < 0) x += m2;
    x /= g;
    return r1 + m1 * x;
}

int64_t mul(int64_t x, int64_t y, int64_t p) {
    int64_t t = (x * y - (int64_t) ((long double) x / p * y + 1e-3) * p) % p;
    return t < 0 ? t + p : t;
}

int64_t crt2(int64_t r1, int64_t m1, int64_t r2, int64_t m2, int64_t mod) {
    int64_t x, y;
    extend_gcd(m1, m2, x, y);
    // x = (r2 - r1) * x % m2;
    x = mul((r2 - r1 + m2 * mod) % (m2 * mod), x, m2 * mod);
    x %= m2;
    if (x < 0) x += m2;
    return r1 + (x % mod) * (m1 % mod);
}

int64_t pow(int64_t a, int64_t exp, int64_t MOD) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

namespace ntt {
void solve(int64_t *p, int n, int idft, int64_t MOD, int64_t G) {
    for (int i = 0; i < n; i++)
        if (i < rev[i])
            std::swap(p[i], p[rev[i]]);
    for (int j = 1; j < n; j <<= 1) {
        static int64_t wn1, w, t0, t1;
        wn1 = pow(G, (MOD - 1) / (j << 1), MOD);
        if (idft == -1)
            wn1 = pow(wn1, MOD - 2, MOD);
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
        int64_t nInv = pow(n, MOD - 2, MOD);
        for (int i = 0; i < n; i++)
            (p[i] *= nInv) %= MOD;
    }
}
}

int64_t MOD;
int n, m;
int64_t fac[N], inv[N], l[N], r[N];

void init() {
    fac[0] = fac[1] = 1;
    int NN = std::max(n, m);
    for (int i = 2; i <= NN; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= NN; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i <= NN; i++) (inv[i] *= inv[i - 1]) %= MOD;
}

int64_t a[N], b[N], ta[N], tb[N], r1[N], r2[N], r3[N];

void solve(int n, int64_t *r, int64_t mod, int64_t prt) {
    static int nn, len;
    len = 0;
    for (nn = 1; nn < n + n; nn <<= 1) len++;
    for (int i = 0; i < n; i++) ta[i] = a[i], tb[i] = b[i];
    for (int i = n; i < nn; i++) ta[i] = tb[i] = 0;
    rev[0] = 0;
    for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
    ntt::solve(ta, nn, 1, mod, prt);
    ntt::solve(tb, nn, 1, mod, prt);
    for (int i = 0; i <= nn; i++) (ta[i] *= tb[i]) %= mod;
    ntt::solve(ta, nn, -1, mod, prt);
    for (int i = 0; i < n; i++) r[i] = ta[i];
}

void process(int64_t *x, int n) {
    for (int i = 0; i <= n; i++) {
        a[i] = inv[i];
        if (i & 1) a[i] = MOD - a[i];
        b[i] = inv[i] * pow(i, n, MOD) % MOD;
    }
    solve(n + 1, r1, MOD1, 3);
    solve(n + 1, r2, MOD2, 3);
    solve(n + 1, r3, MOD3, 6);
    for (int i = 0; i <= n; i++) x[i] = crt2(crt(r1[i], MOD1, r2[i], MOD2), MOD1 * MOD2, r3[i], MOD3, MOD) % MOD * fac[i] % MOD;
}

int64_t ans;
int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d%lld", &n, &m, &MOD);
        init();
        process(l, n);
        process(r, m);
        ans = 0;
        for (int k = 1; k <= std::min(n, m); k++) (ans += l[k] * r[k]) %= MOD;
        (ans <<= 1) %= MOD;
        for (int k = 1; k <= std::min(n - 1, m); k++) (ans += l[k + 1] * r[k]) %= MOD;
        for (int k = 1; k <= std::min(n, m - 1); k++) (ans += l[k] * r[k + 1]) %= MOD;
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
