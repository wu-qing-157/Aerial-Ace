#include <cstdio>
#include <cstdint>
#include <algorithm>

int cas, a, b;

int64_t solve(int64_t x, int64_t y) {
    if (cas == 1)
        return b * (llabs(x) + llabs(y));
    else if (cas == 2)
        return a * std::min(llabs(x), llabs(y)) + b * llabs(llabs(x) - llabs(y));
    else
        return a * std::max(llabs(x), llabs(y)) + ((x ^ y) & 1) * (b - a);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        int x, y;
        scanf("%d%d%d%d", &a, &b, &x, &y);
        if (a >= 2 * b) cas = 1;
        else if (a >= b) cas = 2;
        else cas = 3;
        printf("%lld\n", std::min({solve(x, y), solve(x, y + 1), solve(x - 1, y), solve(x - 1, y + 1)}));
    }
    return 0;
}
