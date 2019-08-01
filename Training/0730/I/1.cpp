#include <cstdio>
#include <cstdint>
#include <unordered_map>

int n;
int64_t a, P, ans;
std::unordered_map<int64_t, int> amap, map;

int64_t calc(__int128_t a) {
    a %= P;
    return a * a % P * a % P;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        amap.clear();
        map.clear();
        scanf("%d%lld", &n, &P);
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &a);
            if (a == 0) continue;
            map[calc(a)]++;
            amap[a]++;
        }
        ans = 0;
        for (auto p : map)
            ans += 1ll * p.second * (p.second - 1) / 2;
        for (auto p : amap)
            if ((__int128_t) p.first * p.first * 3 % P != 0)
                ans -= 1ll * p.second * (p.second - 1) / 2;
        printf("%lld\n", ans);
    }
    return 0;
}
