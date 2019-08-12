#include <cassert>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

const int N = 1e5 + 10;
int n, a[N], v[N], cur, ret;
std::vector<int> odd, even;
std::unordered_set<int> set;
std::unordered_map<int, int> map;
std::pair<int, int> p[N];

void output() {
    for (int i = 1; i <= n; i++)
        if (!map.count(i))
            map[i] = i;
    for (int i = 1; i <= n; i++) {
        assert(!set.count(map[i]));
        set.insert(map[i]);
    }
    printf("%d\n", n);
    ret = n;
    for (int i = 1; i < n; i++) {
        ret ^= map[p[i].first] ^ map[p[i].second];
        printf("%d %d\n", map[p[i].first], map[p[i].second]);
    }
    assert(ret == 0);
}

int main() {
    scanf("%d", &n);
    cur = n;
    for (int i = 1; i <= n; i++) scanf("%d", v + i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
        a[p[i].first] ^= 1;
        a[p[i].second] ^= 1;
    }
    for (int i = 1; i <= n; i++)
        if (a[i])
            cur ^= i;
    for (int i = 1; i <= n; i++)
        if (v[i])
            (a[i] ? odd : even).push_back(i);
    if (odd.size() == 0) {
        if (cur == 0)
            output();
        else
            puts("-1");
    } else if (odd.size() == 1) {
        int x = odd.front();
        int tobe = cur ^ x;
        if (tobe > n || tobe == x) {
            map[x] = tobe;
            output();
        } else {
            bool flag = true;
            for (auto i : even) {
                if (tobe == i) {
                    map[x] = i;
                    map[i] = n + 1;
                    output();
                    flag = false;
                    break;
                }
            }
            if (flag) puts("-1");
        }
    } else if (odd.size() == 2) {
        int x = odd.front(), y = odd.back();
        int tobe = cur ^ x ^ y;
        if (tobe == 0) {
            puts("-1");
        } else {
            int tx = 1048576, ty = tobe ^ tx;
            map[x] = tx, map[y] = ty;
            output();
        }
    } else {
        int x = odd[0], y = odd[1], z = odd[2];
        int tobe = cur ^ x ^ y ^ z;
        int tx = 1048576, ty = tx << 1, tz = tobe ^ tx ^ ty;
        map[x] = tx, map[y] = ty, map[z] = tz;
        output();
    }
    return 0;
}
