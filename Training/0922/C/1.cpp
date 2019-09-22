#include <cstdio>
#include <algorithm>

const int N = 1e4 + 10;
int n;
double a[N], ans, sum, prod;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf", a + i);
        std::sort(a, a + n);
        ans = a[n - 1];
        sum = 0, prod = 1;
        int m = std::lower_bound(a, a + n, 0.5 - 1e-8) - a - 1;
        for (int i = m; i >= 0; i--) {
            if (a[i] > 1 - 1e-8) break;
            sum += a[i] / (1 - a[i]);
            prod *= 1 - a[i];
            ans = std::max(ans, sum * prod);
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
