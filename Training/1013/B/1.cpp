#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

struct info {
    int type, x, v1, v2;
    info() {}
    info(int type, int x, int v1, int v2) : type(type), x(x), v1(v1), v2(v2) {}
    friend bool operator<(const info &a, const info &b) {
        return a.x < b.x;
    }
};

const int N = 1e5 + 10;
int X, Y, ys[N], n, bit[N];
int64_t ans;
std::vector<info> vert;
std::set<int> set;
std::map<int, int> map;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int delta) {
    for (; x < N; x += lowbit(x)) bit[x] += delta;
}

int query(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) ret += bit[x];
    return ret;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &X, &Y, &n);
        memset(bit, 0, sizeof bit);
        map.clear();
        set.clear();
        vert.clear();
        ans = 0;
        for (int i = 1; i <= n; i++) {
            int x, &y = ys[i];
            char op;
            scanf("%d%d %c", &x, &y, &op);
            if (op == 'U')
                vert.emplace_back(1, x, y, Y);
            else if (op == 'D')
                vert.emplace_back(1, x, 0, y);
            else if (op == 'L')
                vert.emplace_back(0, 0, y, 1), vert.emplace_back(0, x, y, -1);
            else
                vert.emplace_back(0, x, y, 1), vert.emplace_back(0, X, y, -1);
        }
        std::sort(ys + 1, ys + n + 1);
        for (int i = 1; i <= n; i++) map[ys[i]] = i;
        map[0] = 0, map[Y] = n + 1;
        std::sort(vert.begin(), vert.end());
        for (auto p : vert) {
            if (p.type == 0)
                add(map[p.v1], p.v2);
            else
                ans += query(map[p.v2]) - query(map[p.v1]);
        }
        printf("%lld\n", ans + 1);
    }
    return 0;
}
