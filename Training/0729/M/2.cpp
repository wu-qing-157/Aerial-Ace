#include <cstdio>
#include <cstdint>
#include <algorithm>

const int N = 4e5 + 10;

int64_t pow(int64_t a, int64_t exp, int64_t MOD) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
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

int64_t c(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

void process(int64_t *x, int n) {
    for (int i = 0; i <= n; i++) {
        x[i] = 0;
        for (int j = 0; j <= i; j++) {
            int64_t ret = c(i, j) * pow(j, n, MOD);
            if ((i - j) & 1) (x[i] -= ret) %= MOD;
            else (x[i] += ret) %= MOD;
        }
        if (x[i] < 0) x[i] += MOD;
    }
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
