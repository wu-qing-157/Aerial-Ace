#include <cstdint>
#include <cstdio>

const int N = 1e5 + 10;
int n;
int64_t a[N], pre[N], suf[N], ans;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d", &n);
        for (int i = 2; i <= n; i++) scanf("%lld", a + i);
        for (int i = 3; i <= n; i++) a[i] += a[i - 1];
        for (int i = 1, j = 0, k = 0; i <= n; i++) {
            if (i & 1) {
                j++;
                ans += a[j] * (j - 1) - pre[j - 1];
                ans += suf[k] - a[j] * k;
                pre[j] = pre[j - 1] + a[j];
            } else {
                k++;
                ans += suf[k - 1] - a[n + 1 - k] * (k - 1);
                ans += a[n + 1 - k] * j - pre[j];
                suf[k] = suf[k - 1] + a[n + 1 - k];
            }
            printf("%lld%c", ans, " \n"[i == n]);
        }
    }
    return 0;
}
