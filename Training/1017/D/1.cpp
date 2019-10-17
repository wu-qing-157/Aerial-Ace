#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10;
int n, m, r, a[N], t[N];
int64_t ans;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d%d", &n, &m, &r);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i < r; i++) t[i] = i;
        t[r] = 1;
        for (int i = r + 1; i <= n; i++) t[i] = r;
        for (int i = 1; i <= m; i++) {
            static int u, v;
            scanf("%d%d", &u, &v);
            if (u > v) std::swap(u, v);
            t[v] = std::min(t[v], u);
        }
        std::sort(t + 1, t + n + 1);
        for (int i = n, j = n; i; i--) {
            if (j > t[i]) j = t[i];
            while (j && a[j] == 0) j--;
            if (j == 0) break;
            a[j]--;
        }
        ans = 0;
        for (int i = 1; i <= n; i++) ans += a[i];
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
