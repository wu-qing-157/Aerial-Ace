#include <cstdio>
#include <algorithm>
#include <vector>

namespace seg {
    const int N = 1e6 + 10;
    int min[N], tag[N];
#define nl id << 1, l, (l + r) / 2
#define nr (id << 1) | 1, (l + r) / 2 + 1, r
    void pushdown(int id) {
        min[id << 1] += tag[id];
        min[(id << 1) | 1] += tag[id];
        tag[id << 1] += tag[id];
        tag[(id << 1) | 1] += tag[id];
        tag[id] = 0;
    }
    void build(int id, int l, int r, int *v) {
        if (l == r) {
            min[id] = v[l];
            return;
        }
        build(nl, v);
        build(nr, v);
        min[id] = std::min(min[id << 1], min[(id << 1) | 1]);
    }
    void add(int id, int l, int r, int ll, int rr, int delta) {
        if (ll > r || rr < l) return;
        if (ll <= l && r <= rr) {
            min[id] += delta;
            tag[id] += delta;
            return;
        }
        pushdown(id);
        add(nl, ll, rr, delta);
        add(nr, ll, rr, delta);
        min[id] = std::min(min[id << 1], min[(id << 1) | 1]);
    }
}

const int N = 1e5 + 10;
int n, m, q, a[N], r[N], cnt[N], v[N];
std::vector<int> b[N];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] >= a[1]) cnt[0]++;
    }
    for (int i = 1; i <= m; i++) {
        cnt[i] += cnt[i - 1];
        scanf("%d", r + i);
        b[i].resize(r[i] + 1);
        for (int j = 1; j <= r[i]; j++) {
            static int t;
            scanf("%d", &t);
            b[i][j] = t;
            if (b[i][j] >= a[1]) cnt[i]++;
        }
    }
    for (int i = 1; i <= m; i++) v[i] = n - r[i] - cnt[i - 1];
    seg::build(1, 1, m, v);
    while (q--) {
        static int i, j, v;
        scanf("%d%d%d", &i, &j, &v);
        if (b[i][j] < a[1] && v >= a[1]) seg::add(1, 1, m, i + 1, m, -1);
        if (b[i][j] >= a[1] && v < a[1]) seg::add(1, 1, m, i + 1, m, 1);
        b[i][j] = v;
        puts(seg::min[1] >= 0 ? "1" : "0");
    }
    return 0;
}
