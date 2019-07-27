#include <cstdio>
#include <algorithm>

int n, k;
int ans;

int main() {
    while (true) {
        ans = 0;
        scanf("%d%d", &n, &k);
        for (int l = 1; l <= 2 * n; l++)
            for (int i = -n; i + l <= n; i++)
                for (int j = -n; j + l <= n; j++) {
                    if (std::abs(i) <= k && std::abs(j) <= k) continue;
                    if (std::abs(i) <= k && std::abs(j + l) <= k) continue;
                    if (std::abs(i + l) <= k && std::abs(j) <= k) continue;
                    if (std::abs(i + l) <= k && std::abs(j + l) <= k) continue;
                    ans++;
                }
        printf("%d\n", ans);
    }
    return 0;
}
