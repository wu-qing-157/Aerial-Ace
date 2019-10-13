#include <cstdint>
#include <cstdio>

const int64_t MOD = 1e9 + 7;
int n, m, k;
int64_t ans, sing;

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
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d%d", &n, &m, &k);
        ans = pow(k, m * n);
        sing = 0;
        for (int i = 1; i <= k; i++)
            (sing += pow(i - 1, (m - 1) + (n - 1)) * pow(k, (m - 1) * (n - 1))) %= MOD;
        (ans += sing * m * n) %= MOD;
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
