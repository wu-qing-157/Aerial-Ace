#include <cstdio>

int T, n, ans, a, b;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        while (n--) {
            scanf("%d%d", &a, &b);
            ans += a * b;
        }
        printf("%d\n", ans);
    }
    return 0;
}
