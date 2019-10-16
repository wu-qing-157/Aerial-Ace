#include <cstdio>

int x, y, k;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d%d", &x, &y, &k);
        if (y > x)
            printf("Case #%d: %d\n", cas, k);
        else
            printf("Case #%d: %d\n", cas, (11 * k * y) / (11 * x + 2 * y));
    }
    return 0;
}
