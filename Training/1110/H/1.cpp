#include <cstdio>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

const int N = 1e5 + 10;
int n;
int64_t a[N], b[N];
int64_t ans;
std::vector<std::pair<int64_t, int64_t>> v, v1;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld%lld", a + i, b + i);
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, a[i] * b[i]);
        v.push_back(std::minmax(a[i], b[i]));
    }
    std::sort(v.begin(), v.end(), std::greater<std::pair<int64_t, int64_t>>());
    for (auto p : v) {
        if (!v1.empty() && v1.back().first >= p.first && v1.back().second >= p.second)
            ans = std::max(ans, p.first * p.second * 2);
        else
            v1.push_back(p);
    }
    int m = int(v1.size());
    for (int i = 1; i < m; i++) ans = std::max(ans, v1[i].first * v1[i - 1].second * 2);
    printf("%lld.%s\n", ans / 2, ans & 1 ? "5" : "0");
    return 0;
}
