#include <cstdio>
#include <algorithm>

int n, a, sum;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        sum = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a);
            sum += a + (a + 9) / 10;
        }
        printf("Case #%d: %d\n", cas, sum);
    }
    return 0;
}
