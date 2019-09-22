#include <cstdio>
#include <cstdint>

const int N = 2e5 + 10;
const int64_t MOD = 1e9 + 7, inv2 = (MOD + 1) / 2;
int64_t fac[N], inv[N];

int64_t n, ans;
int m, s, t;

int64_t c(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] *= inv[i - 1]) %= MOD;
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%d", &n, &m);
        ans = 0, s = m / 2, t = m - s;
        for (int i = 0; i <= s; i++)
            (ans += c(s, i) * pow(t + 2 * i - s, n)) %= MOD;
        (ans *= pow(inv2, s)) %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
