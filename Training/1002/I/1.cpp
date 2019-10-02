#include <cstdio>
#include <unordered_set>
#include <unordered_map>

const int N = 1e5 + 10;
int n, x[N], y[N], maxx, maxy;
int64_t cnt1, cnt2;
std::unordered_map<int, int> mapx, mapy;
std::unordered_set<int> x1, x2, y1, y2;

int cnt(std::unordered_set<int> &xx, std::unordered_set<int> &yy) {
    int ret = 0;
    for (int i = 1; i <= n; i++)
        if (xx.count(x[i]) && yy.count(y[i]))
            ret++;
    return ret;
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        mapx.clear(), mapy.clear();
        maxx = maxy = 0;
        x1.clear(), x2.clear(), y1.clear(), y2.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
        for (int i = 1; i <= n; i++) mapx[x[i]]++, mapy[y[i]]++;
        if (mapx.size() == 1u || mapy.size() == 1u) {
            printf("Case %d: %d %d\n", cas, n, 1);
            continue;
        }
        for (auto p : mapx) maxx = std::max(maxx, p.second);
        for (auto p : mapy) maxy = std::max(maxy, p.second);
        for (auto p : mapx) {
            if (p.second == maxx)
                x1.insert(p.first);
            if (p.second == maxx - 1)
                x2.insert(p.first);
        }
        for (auto p : mapy) {
            if (p.second == maxy)
                y1.insert(p.first);
            if (p.second == maxy - 1)
                y2.insert(p.first);
        }
        cnt1 = 1ll * x1.size() * y1.size() - cnt(x1, y1);
        if (cnt1) {
            if (maxx + maxy == 2)
                printf("Case %d: %d %lld\n", cas, 2, 1ll * n * (n - 1) / 2);
            else
                printf("Case %d: %d %lld\n", cas, maxx + maxy, cnt1);
            continue;
        }
        cnt2 = 1ll * x1.size() * y1.size();
        cnt2 += 1ll * x2.size() * y1.size() - cnt(x2, y1);
        cnt2 += 1ll * x1.size() * y2.size() - cnt(x1, y2);
        printf("Case %d: %d %lld\n", cas, maxx + maxy - 1, cnt2);
    }
    return 0;
}
