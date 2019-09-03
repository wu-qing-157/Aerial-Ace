#include <cstdio>
#include <cstdint>
#include <utility>

#pragma GCC optimize(3)

const int PP = 8388608;
int64_t a2[8388700], a7[8], a17[18];

void init() {
    a2[0] = 1;
    for (int i = 1; i < PP; i++)
        a2[i] = a2[i - 1] * (i / (1 << __builtin_ctz(i))) % PP;
    a7[0] = 1;
    for (int i = 1; i < 7; i++)
        a7[i] = a7[i - 1] * i % 7;
    a17[0] = 1;
    for (int i = 1; i < 17; i++)
        a17[i] = a17[i - 1] * i % 17;
}

int64_t pow(int64_t a, int64_t exp, int64_t MOD) {
    if (exp < 0) printf("%d\n", 1 / 0);
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int64_t inv(int64_t a, int64_t MOD) {
    if (MOD == PP) return pow(a, PP / 2 - 1, MOD);
    return pow(a, MOD - 2, MOD);
}

int64_t cntx(int P, int n) {
    int64_t ans = 0;
    for (n /= P; n; n /= P) ans += n;
    return ans;
}

std::pair<int64_t, int64_t> cfac(int P, int PP, int64_t *a, int n) {
    int x = n / PP, y = n % PP;
    return {pow(a[PP - 1], x, PP) * a[y] % PP, cntx(P, n)};
}

int64_t singc(int P, int PP, int64_t *a, int n, int m) {
    auto a1 = cfac(P, PP, a, n), b1 = cfac(P, PP, a, m), b2 = cfac(P, PP, a, n - m);
    auto reta = a1.first * inv(b1.first * b2.first % PP, PP) % PP, retb = a1.second - b1.second - b2.second;
    if (retb >= 23) return 0;
    return reta * pow(P, retb, PP) % PP;
}

int64_t c(int n, int m) {
    if (m < 0 || m > n) return 0;
    return (981467137 * singc(2, PP, a2, n, m) + 427819008 * singc(7, 7, a7, n, m) + 587202560 * singc(17, 17, a17, n, m)) % 998244352;
}

int t1, t2, p, q, n, m, x, y, v;
int64_t ans;

int main() {
    init();
    while (scanf("%d%d%d%d%d%d", &t1, &t2, &p, &q, &n, &m) != EOF) {
        ans = 1;
        for (int i = 1; i <= m; i++) {
            scanf("%d%d%d", &x, &y, &v);
            if (x % p || y % q) continue;
            int A = x / p, B = y / q;
            (ans *= pow(v, pow(t1, A, 998244352) * pow(t2, B, 998244352) % 998244352 * c(n, A) % 998244352 * c(n - A, B) % 998244352, 998244353)) %= 998244353;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
