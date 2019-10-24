#include <cmath>
#include <cstdint>
#include <cstdio>
#include <algorithm>

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int res = exgcd(b, a % b, x, y);
    int t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

#define y1 yyyy
int x1, y1, x2, y2, k, dx, dy, gcd;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
        gcd = std::__gcd(x2 - x1, y2 - y1);
        x2 = (x2 - x1) / gcd + x1, y2 = (y2 - y1) / gcd + y1;
        exgcd(y1 - y2, x2 - x1, dx, dy);
        for (int64_t x = x1 + dx, y = y1 + dy; ; x += x2 - x1, y += y2 - y1) {
            if (!k) break;
            if (llabs(x) >= 100000000000000ll || llabs(y) >= 100000000000000ll) break;
            printf("%lld %lld\n", x, y);
            k--;
        }
        for (int64_t x = x1 + dx - (x2 - x1), y = y1 + dy - (y2 - y1); ; x -= x2 - x1, y -= y2 - y1) {
            if (!k) break;
            if (llabs(x) >= 100000000000000ll || llabs(y) >= 100000000000000ll) break;
            printf("%lld %lld\n", x, y);
            k--;
        }
        for (int64_t x = x1 - dx, y = y1 - dy; ; x += x2 - x1, y += y2 - y1) {
            if (!k) break;
            if (llabs(x) >= 100000000000000ll || llabs(y) >= 100000000000000ll) break;
            printf("%lld %lld\n", x, y);
            k--;
        }
        for (int64_t x = x1 - dx - (x2 - x1), y = y1 - dy - (y2 - y1); ; x -= x2 - x1, y -= y2 - y1) {
            if (!k) break;
            if (llabs(x) >= 100000000000000ll || llabs(y) >= 100000000000000ll) break;
            printf("%lld %lld\n", x, y);
            k--;
        }
    }
    return 0;
}
