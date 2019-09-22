#include <cmath>
#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>

const int N = 1e5 + 10;
int n;
int64_t out, ans;
std::pair<int64_t, int64_t> a[N];
std::multiset<int64_t> in;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = INT64_MAX / 4;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lld%lld", &a[i].first, &a[i].second);
        std::sort(a, a + n, std::greater<std::pair<int64_t, int64_t>>());
        for (int i = 0; i < n; i++)
            in.insert(a[i].second);
        out = INT64_MIN / 4;
        for (int i = 0; i < n; i++) {
            in.erase(in.find(a[i].second));
            auto it = in.lower_bound(a[i].first);
            if (it != in.end())
                ans = std::min<int64_t>(ans, llabs(a[i].first - std::max(out, *it)));
            if (it != in.begin())
                ans = std::min<int64_t>(ans, llabs(a[i].first - std::max(out, *--it)));
            ans = std::min<int64_t>(ans, llabs(a[i].first - out));
            out = std::max(out, a[i].second);
        }
        in.clear();
        printf("%lld\n", ans);
    }
    return 0;
}
