#include <cstdio>
#include <cstdint>
#include <algorithm>

const int N = 1e6 + 10;
int n;
int64_t sum1, sum2;
std::pair<int, int> a[N];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        sum1 = sum2 = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d", &a[i].first, &a[i].second), sum1 += a[i].first, sum2 += a[i].second;
        for (int i = 0; i < n; i++) {
            if (a[i].first >= sum2 - a[i].second) {
                int64_t delta = a[i].first - (sum2 - a[i].second);
                a[i].first -= delta;
                sum1 -= delta;
            }
            if (a[i].second >= sum1 - a[i].first) {
                int64_t delta = a[i].second - (sum1 - a[i].first);
                a[i].second -= delta;
                sum2 -= delta;
            }
        }
        printf("%lld\n", std::min(sum1, sum2));
    }
    return 0;
}
