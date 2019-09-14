#include <cstdio>
#include <cstdint>

const int N = 1e6 + 10;
int n, MOD, fac[N], inv[N], b[N];

int c(int n, int m) {
    return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &MOD);
        fac[0] = 1;
        for (int i = 1; i < MOD; i++)
            fac[i] = fac[i - 1] * i % MOD;
        inv[0] = inv[1] = 1;
        for (int i = 2; i < MOD; i++)
            inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        for (int i = 2; i < MOD; i++)
            (inv[i] *= inv[i - 1]) %= MOD;
        b[0] = 1;
        for (int i = 1; i < MOD; i++) {
            b[i] = 0;
            for (int j = 0; j < i; j++)
                (b[i] += b[j] * c(i - 1, j)) %= MOD;
        }
        for (int i = MOD; i <= n; i++)
            b[i] = (b[i - MOD] + b[i - MOD + 1]) % MOD;
        printf("%d\n", b[n]);
    }
    return 0;
}
