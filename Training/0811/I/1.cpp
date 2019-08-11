#include <cstdio>
#include <map>
#include <set>

const int N = 1e5 + 10;
int n, a[N];
std::multiset<int64_t> set;
std::map<int, int64_t> map;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        set.clear(), map.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            auto it = map.upper_bound(a[i]);
            if (it == map.begin()) {
                map[a[i]] = a[i];
                set.insert(a[i]);
            } else {
                --it;
                auto p = *it;
                map.erase(it);
                set.erase(set.find(p.second));
                map[a[i]] = p.second + a[i];
                set.insert(p.second + a[i]);
            }
#define it iit
            auto it = set.rbegin();
            int j = 0;
            int64_t ans = 0;
            for (; it != set.rend() && j < 5; ++it, j++) ans += *it;
            printf("%lld%c", ans, " \n"[i == n]);
        }
    }
    return 0;
}
