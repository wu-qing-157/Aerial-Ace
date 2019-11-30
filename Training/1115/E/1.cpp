#include <cstdio>
#include <algorithm>
#include <utility>

#define double long double

const int N = 3e5 + 10;
int n;
std::pair<int, int> a[N];

bool check(double m) {
    int cur = 0;
    while (cur < n && a[cur].second <= m) cur++;
    if (cur == n) return true;
    double pl = 0, pr = 1e9 + m;
    while (cur < n && std::max(pl, a[cur].second - m) <= std::min(pr, a[cur].second + m))
        pl = std::max(pl, a[cur].second - m), pr = std::min(pr, a[cur].second + m), cur++;
    if (cur == n) return true;
    pr = 1e9 + m;
    while (cur < n && std::max(pl, a[cur].second - m) <= std::min(pr, a[cur].second + m))
        pl = std::max(pl, a[cur].second - m), pr = std::min(pr, a[cur].second + m), cur++;
    if (cur == n) return true;
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);
    std::sort(a, a + n);
    double l = 0, r = 1e9;
    if (a[0].first == 0) l = a[0].second;
    for (int i = 1; i <= 100; i++) {
        double m = (l + r) / 2;
        (check(m) ? r : l) = m;
    }
    printf("%.1Lf\n", l);
}
