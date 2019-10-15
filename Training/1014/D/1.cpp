#include <cstdint>
#include <cstdio>

const int64_t MOD = 998244353;
const int N = 1e5 + 10;
int64_t inv[N];

int n;
int64_t a[N], sum, tot;

int main() {
    static int T;
    scanf("%d", &T);
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        sum = tot = 0;
        for (int i = n; i; i--) {
            int64_t cur = (a[i] + sum) % MOD;
            (sum += cur * inv[i - 1]) %= MOD;
            (tot += cur) %= MOD;
        }
        printf("%lld\n", tot * inv[n] % MOD);
    }
    return 0;
}
