#include <cstdint>
#include <cstdio>

int f(int64_t a, int64_t b, int64_t c, int64_t n) {
    if (a == 0) {
        return b / c & (n + 1) & 1;
    } else if (a >= c || b >= c) {
        return f(a % c, b % c, c, n) ^ (a / c & 1 & (n & 1 ? n & (n + 1) / 2 : n / 2 & (n + 1))) ^ (n + 1 & b / c & 1);
    } else {
        int m = (a * n + b) / c & 1;
        return n & m & 1 ^ f(c, c - b - 1, a, m - 1);
    }
}

const int64_t LIM = 4e7;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        int64_t n, ans = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= LIM && i <= n; i++)
            ans ^= n % i;
        for (int64_t i = LIM + 1, j; i <= n; i = j + 1) {
            j = n / (n / i);
            if (j > n) j = n;
            for (int k = 0; k < 45; k++)
                ans ^= (1ll << k) * f(n / j, n % j, 1ll << k, j - i);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
