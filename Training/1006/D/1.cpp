#include <cstdio>
#include <algorithm>
#include <map>
#include <utility>

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
    point rotate90() const {
        return point(-y, x);
    }
};

struct rect {
    int xl, xr, yl, yr;
    rect() {}
    rect(int xl, int xr, int yl, int yr) : xl(xl), xr(xr), yl(yl), yr(yr) {}
    rect rotate90() const {
        return rect(-yr, -yl, xl, xr);
    }
};

const int N = 3e5 + 10;
int n;
point s, e;
rect a[N];
std::map<int, int64_t> map;

int64_t solve() {
    map.clear();
    int64_t ans = INT64_MAX >> 5;
    std::sort(a, a + n, [](const auto &a, const auto &b) {
        return a.xl < b.xl;
    });
    map[0] = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].xl < 0) continue;
        if (a[i].xl >= e.x) break;
        auto lit = map.insert(std::make_pair(a[i].yl, INT64_MAX >> 5)).first;
        auto rit = map.insert(std::make_pair(a[i].yr, INT64_MAX >> 5)).first;
        while (true) {
            auto nit = lit++; std::swap(lit, nit);
            if (nit == rit) break;
            lit->second = std::min(lit->second, nit->second + nit->first - lit->first);
            rit->second = std::min(rit->second, nit->second + rit->first - nit->first);
            map.erase(nit);
        }
        if (lit != map.begin()) {
            auto nit = lit--; std::swap(lit, nit);
            lit->second = std::min(lit->second, nit->second + lit->first - nit->first);
        }
        if (rit != --map.end()) {
            auto nit = rit++; std::swap(rit, nit);
            rit->second = std::min(rit->second, nit->second + nit->first - rit->first);
        }
    }
    int min = INT32_MIN, max = INT32_MAX;
    for (int i = 0; i < n; i++)
        if (a[i].xl < e.x && a[i].xr > e.x) {
            if (a[i].yr <= e.y) min = std::max(min, a[i].yr);
            else max = std::min(max, a[i].yl);
        }
    for (auto p : map)
        if (p.first >= min && p.first <= max)
            ans = std::min(ans, p.second + std::abs(p.first - e.y));
    return ans + e.x;
}

int main() {
    scanf("%d%d%d%d%d", &n, &s.x, &s.y, &e.x, &e.y);
    for (int i = 0; i < n; i++) scanf("%d%d%d%d", &a[i].xl, &a[i].yl, &a[i].xr, &a[i].yr);
    e.x -= s.x, e.y -= s.y;
    for (int i = 0; i < n; i++) a[i].xl -= s.x, a[i].xr -= s.x, a[i].yl -= s.y, a[i].yr -= s.y;
    while (e.x < 0 || e.y < 0) {
        e = e.rotate90();
        for (int i = 0; i < n; i++) a[i] = a[i].rotate90();
    }
    int64_t ans = solve();
    std::swap(e.x, e.y);
    for (int i = 0; i < n; i++) std::swap(a[i].xl, a[i].yl), std::swap(a[i].xr, a[i].yr);
    ans = std::min(ans, solve());
    printf("%lld\n", ans);
    return 0;
}
