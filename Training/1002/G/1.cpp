#include <cstdint>
#include <cstdio>

const int N = 1e5 + 10;
const int64_t MOD = 1e9 + 7;
int64_t ans[N], inv[N];
int a, b;

int main() {
    inv[1] = 1;
    for (int i = 2; i <= 10; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int64_t n = 3; n <= 100000; n++) {
        ans[n] += n * (n - 2) % MOD * (n - 1) % MOD * n % MOD * inv[3] % MOD;
        ans[n] -= n * n % MOD * (n - 1) % MOD * (n - 1) % MOD * inv[4] % MOD;
        ans[n] += MOD, ans[n] %= MOD;
        ans[n] += (n - 1) * n % MOD * (2 * n - 1) % MOD * inv[6] % MOD;
        ans[n] %= MOD;
        ans[n] *= inv[2];
        ans[n] %= MOD;
        //if (n <= 10)
        //printf("%d %ld %ld %ld\n", n, n * (n - 2) % MOD * (n - 1) % MOD * n % MOD * inv[3] % MOD, (n - 1) * (n - 1) % MOD * (n - 2) % MOD * (n - 2) % MOD * inv[4] % MOD, (n - 1) * n % MOD * (2 * n - 1) % MOD * inv[6] % MOD);
    }
    //for (int i = 2; i <= 10; i++) printf("%ld\n", ans[i]);
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d", &a, &b);
        printf("Case %d: %lld\n", cas, ans[a] * ans[b] % MOD);
    }
    return 0;
}
