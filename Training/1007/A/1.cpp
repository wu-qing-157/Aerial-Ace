#include <cstdio>

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        static int n;
        scanf("%d", &n);
        printf("Case #%d: %d\n", cas, n / 3);
    }
    return 0;
}
