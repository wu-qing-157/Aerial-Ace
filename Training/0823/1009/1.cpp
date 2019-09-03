#include <cstdio>
#include <cstdint>
#include <algorithm>

int n, m;
int64_t ans, MOD;

#define pow powww

int64_t pow(int64_t a, int64_t exp) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int64_t inv(int64_t a) {
    return pow(a, MOD - 2);
}

int64_t p(int m, int n) {
    int64_t ans = 1;
    for (int i = 1, j = m; i <= n; i++, j--)
        (ans *= j) %= MOD;
    return ans;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%d%lld", &n, &m, &MOD);
        for (int i = 1; i <= std::min(n, m); i++)
            (ans += (2 * i - 1) * p(n - 1, i - 1) % MOD * p(m - 1, i - 1) % MOD *  pow(2, n * m - i * i) % MOD) %= MOD;
        (ans *= inv(pow(2, n * m))) %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
