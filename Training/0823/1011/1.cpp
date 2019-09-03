#include <cstdio>
#include <cstdint>
#include <utility>

#pragma GCC optimize(3)
#define __ __attribute__((optimize("-O3")))

const int PP = 8388608;
int a2[8388700], a7[8], a17[18];

__ void init() {
    a2[0] = 1;
    for (int i = 1; i < PP; i++)
        a2[i] = 1ll * a2[i - 1] * (i / (1 << __builtin_ctz(i))) % PP;
    a7[0] = 1;
    for (int i = 1; i < 7; i++)
        a7[i] = 1ll * a7[i - 1] * i % 7;
    a17[0] = 1;
    for (int i = 1; i < 17; i++)
        a17[i] = 1ll * a17[i - 1] * i % 17;
}

__ int pow(int a, int exp, int MOD) {
    int ans = 1;
    while (exp) {
        exp & 1 ? ans = 1ll * ans * a % MOD : 0;
        a = 1ll * a * a % MOD;
        exp >>= 1;
    }
    return ans;
}

__ int inv(int a, int MOD) {
    if (MOD == PP) return pow(a, PP / 2 - 1, MOD);
    return pow(a, MOD - 2, MOD);
}

__ int cntx(int P, int n) {
    int ans = 0;
    for (n /= P; n; n /= P) ans += n;
    return ans;
}

__ int cfac(int PP, int *a, int n) {
    int x = n / PP, y = n % PP;
    return 1ll * pow(a[PP - 1], x, PP) * a[y] % PP;
}

__ int singc(int P, int PP, int *a, int n, int m) {
    int retb = cntx(P, n) - cntx(P, m) - cntx(P, n - m);
    if (retb >= 23) return 0;
    auto a1 = cfac(PP, a, n), b1 = cfac(PP, a, m), b2 = cfac(PP, a, n - m);
    return 1ll * a1 * inv(1ll * b1 * b2 % PP, PP) % PP * pow(P, retb, PP) % PP;
}

__ int c(int n, int m) {
    if (m < 0 || m > n) return 0;
    return (981467137ll * singc(2, PP, a2, n, m) + 427819008ll * singc(7, 7, a7, n, m) + 587202560ll * singc(17, 17, a17, n, m)) % 998244352;
}

int ans, t1, t2, p, q, n, m, x, y, v;

__ int main() {
    init();
    while (scanf("%d%d%d%d%d%d", &t1, &t2, &p, &q, &n, &m) != EOF) {
        ans = 1;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d", &x, &y, &v);
            if (x % p || y % q) continue;
            int A = x / p, B = y / q;
            ans = 1ll * ans * pow(v, 1ll * pow(t1, A, 998244352) * pow(t2, B, 998244352) % 998244352 * c(n, A) % 998244352 * c(n - A, B) % 998244352, 998244353) % 998244353;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
