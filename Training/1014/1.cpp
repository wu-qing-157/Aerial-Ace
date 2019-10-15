#include <cstdint>
#include <cstdio>

const int64_t MOD = 998244353;
int m;
int64_t p, q;

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
    while (T--) {
        scanf("%d", &m);
        int64_t ans = 1;
        for (int i = 1; i <= m; i++) {
            scanf("%lld%lld", &p, &q);
            (ans *= (p * q + p - q) % MOD * pow(p, q - 1) % MOD) %= MOD;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
