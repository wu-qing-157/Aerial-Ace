#include <cstdio>
#include <cstdint>
#include <vector>

int k;

int64_t exgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int64_t res = exgcd(b, a % b, x, y);
    int64_t t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

bool crt(int64_t &r1, int64_t &m1, int64_t r2, int64_t m2) {
    int64_t x, y, g = exgcd(m1, m2, x, y);
    if ((r2 - r1) % g != 0) return false;
    x = (r2 - r1) * x % m2;
    if (x < 0) x += m2;
    x /= g;
    r1 += m1 * x;
    m1 *= m2 / g;
    return true;
}

int main() {
    scanf("%d", &k);
    int64_t r = 0, m = 1;
    for (int i = 1; i <= k; i++) {
        static int64_t m1, r1;
        scanf("%lld%lld", &r1, &m1);
        if (!crt(r, m, r1, m1)) {
            puts("Tankernb!");
            return 0;
        }
    }
    if (r <= 1) r += m;
    int64_t a = 0, b = 1, c = 1;
    while (true) {
        c = a + b;
        a = b;
        b = c;
        if (c > r) {
            puts("Zgxnb!");
            return 0;
        }
        if (c == r) {
            puts("Lbnb!");
            return 0;
        }
    }
    return 0;
}
