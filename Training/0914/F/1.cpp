#include <cstdio>
#include <algorithm>

const int N = 5e5 + 10;
int n, k;
int64_t sum, a[N], l, r, ltar, rtar;

int main() {
    while (scanf("%d%d", &n, &k) != EOF) {
        sum = 0;
        for (int i = 1; i <= n; i++) scanf("%lld", a + i), sum += a[i];
        ltar = sum / n, rtar = ltar + (sum % n != 0);
        std::sort(a + 1, a + n + 1);
        l = a[1], r = a[n];
        for (int i = 1, j = k; i <= n; i++) {
            if (a[i + 1] >= ltar && j >= (ltar - l) * i) {
                l = ltar;
                break;
            }
            if (j < (a[i + 1] - l) * i) {
                l = l + j / i;
                break;
            }
            j -= (a[i + 1] - l) * i;
            l = a[i + 1];
        }
        for (int i = n, j = k; i; i--) {
            if (a[i - 1] <= rtar && j >= (r - rtar) * (n - i + 1)) {
                r = rtar;
                break;
            }
            if (j < (r - a[i - 1]) * (n - i + 1)) {
                r = r - j / (n - i + 1);
                break;
            }
            j -= (r - a[i - 1]) * (n - i + 1);
            r = a[i - 1];
        }
        printf("%lld\n", r - l);
    }
    return 0;
}
