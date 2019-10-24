#include <cstdint>
#include <cstdio>

const int N = 1e5 + 10;
const int64_t MOD = 1e9 + 7;
int64_t fac[N], inv[N];
int n, m;
int64_t ans;

int64_t c(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    fac[0] = fac[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] *= inv[i - 1]) %= MOD;
    while (scanf("%d%d", &n, &m), n || m) {
        ans = 0;
        for (int x1 = 0; x1 <= m; x1++)
            for (int k = 0; k < n; k++) {
                if ((n - 1) * x1 + n - 1 - (m + 1) * k - 1 < n - 2) break;
                int64_t cur = c(n - 1, k) * c((n - 1) * x1 + n - 1 - (m + 1) * k - 1, n - 2) % MOD;
                if (k & 1) (ans += MOD - cur) %= MOD;
                else (ans += cur) %= MOD;
            }
        printf("%lld\n", ans * n % MOD);
    }
    return 0;
}
