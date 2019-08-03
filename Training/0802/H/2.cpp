#include <cstdio>
#include <cstdint>

const int MOD = 1e9 + 7;

__int128_t pow(__int128_t a, int64_t exp) {
    __int128_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int64_t n, k;

int main() {
    for (int cas = 1; scanf("%lld%lld", &n, &k) != EOF; cas++)
        printf("Case #%d: %lld\n", cas, (int64_t) pow(n, k));
    return 0;
}
