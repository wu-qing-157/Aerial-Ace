#include <cstdint>
#include <cstdio>

const int64_t MOD = 1e9 + 7, i4 = 250000002, i12 = 83333334, i8 = 125000001;
int n;
int64_t ans;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = i4 * n % MOD * (n + 1) % MOD * (n + 1) % MOD * (n + 2) % MOD;
        ans += MOD - i12 * n % MOD * (n + 1) % MOD * (2 * n + 1) % MOD * (2 * n + 3) % MOD;
        ans %= MOD;
        ans += i8 * n % MOD * n % MOD * (n + 1) % MOD * (n + 1) % MOD;
        ans %= MOD;
        printf("%lld\n", ans);
    }
}
