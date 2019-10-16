#include <cstdint>
#include <cstdio>

uint64_t n;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%llu", &n);
        if (n == 0) printf("Case #%d: 1\n", cas);
        else if (n == 1) printf("Case #%d: 9\n", cas);
        else if (n == 2) printf("Case #%d: 41\n", cas);
        else if (n == 3) printf("Case #%d: 109\n", cas);
        else printf("Case #%d: %llu\n", cas, 14ull * n * n - 6ull * n + 5ull);
    }
    return 0;
}
