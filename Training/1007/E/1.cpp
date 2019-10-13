#include <cstdio>
#include <algorithm>

const int N = 200;
int n, ans;
long double a[N], cur;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            static long double s, t;
            scanf("%Lf:%Lf", &s, &t);
            a[i] = s / (s + t);
        }
        std::sort(a + 1, a + n + 1);
        long double cur = 0;
        for (ans = 0; ans <= n; ans++, cur += a[ans])
            if (ans == n || cur + a[ans + 1] >= 1)
                break;
        printf("Case #%d: %d\n", cas, ans);
    }
    return 0;
}
