#include <cstdio>
#include <cstdint>
#include <algorithm>

int64_t sqr(int64_t x) {
    return x * x;
}

int n, k;
int64_t ans;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n * 2; i++)
            ans += sqr(2 * n + 1 - i);
        for (int i = 1; i <= 2 * k; i++)
            ans -= sqr(std::min(2 * k + i + 1, 2 * n + 1 - i));
        for (int i = 2 * k + 1; i <= n + k; i++)
            ans -= 4 * sqr(std::min(2 * k + 1, n + k + 1 - i));
        printf("%lld\n", ans);
    }
    return 0;
}
