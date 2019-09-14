#include <cstdio>
#include <cstdint>

const int N = 1e6 + 10;
const int64_t MOD = 1e9 + 7;
int n, x;
int64_t inv[N];

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] += inv[i - 1]) %= MOD;
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &x);
        if (x >= n)
            puts("1");
        else
            printf("%lld\n", (MOD + 1 + inv[x] - inv[n]) % MOD);
    }
    return 0;
}
