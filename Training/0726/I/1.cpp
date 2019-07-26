#include <cstdio>
#include <algorithm>

const int N = 2e4 + 10, M = 1e2 + 10, INF = ~0u >> 2;
struct seg {
    int v[N << 2];
    void build(int id, int l, int r) {
        if (l == r) {
            v[id] = INF;
        } else {
            int mid = (l + r) >> 1;
            build(id << 1, l, mid);
            build((id << 1) | 1, mid + 1, r);
            v[id] = std::min(v[id << 1], v[(id << 1) | 1]);
        }
    }
    void modify(int id, int l, int r, int t, int x) {
        if (l == r) {
            v[id] = x;
        } else {
            int mid = (l + r) >> 1;
            if (t <= mid) modify(id << 1, l, mid, t, x);
            else modify((id << 1) | 1, mid + 1, r, t, x);
            v[id] = std::min(v[id << 1], v[(id << 1) | 1]);
        }
    }
    int query(int id, int l, int r, int tl, int tr) {
        if (r < tl || tr < l) return INF;
        if (tl <= l && r <= tr) return v[id];
        int mid = (l + r) >> 1;
        return std::min(query(id << 1, l, mid, tl, tr), query((id << 1) | 1, mid + 1, r, tl, tr));
    }
} s[M];

struct interval {
    int first, second, cost;
    interval() {}
    interval(int first, int second, int cost) : first(first), second(second), cost(cost) {}
};

int n, m, x[N], c[N], R[N], p[N], dp[N][M], ans;
interval t[N];

int main() {
    for (int cas = 1; scanf("%d%d", &n, &m), n && m; cas++) {
        for (int i = 2; i <= n; i++) scanf("%d", x + i);
        x[n + 1] = INF;
        for (int i = 1; i <= n; i++) scanf("%d", c + i);
        for (int i = 1; i <= n; i++) scanf("%d", R + i), t[i] = interval(x[i] - R[i], x[i] + R[i], c[i]);
        t[n + 1] = interval(-INF, INF, 0);
        for (int i = 1; i <= n; i++) scanf("%d", p + i);

        for (int i = 0; i <= n; i++) for (int j = 0; j <= m; j++) dp[i][j] = INF;
        for (int i = 0; i <= m; i++) s[i].build(1, 0, n);
        dp[0][0] = 0;
        s[0].modify(1, 0, n, 0, 0);

        std::sort(t + 1, t + n + 1, [](const auto &a, const auto &b) { return a.second < b.second; });

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= m; j++) {
                dp[i][j] = std::min(dp[i][j], dp[i - 1][j] + p[i]);
                if (j) {
                    int kk = std::lower_bound(t + 1, t + n + 1, std::make_pair(0, x[i]), [](const auto &a, const auto &b) { return a.second < b.second; }) - t;
                    for (int k = kk; t[k].second < x[i + 1]; k++) {
                        int fr = std::lower_bound(x + 1, x + n + 1, t[k].first) - x - 1;
                        dp[i][j] = std::min(dp[i][j], s[j - 1].query(1, 0, n, fr, i - 1) + t[k].cost);
                        s[j].modify(1, 0, n, i, dp[i][j]);
                    }
                }
                printf("%d %d     %d\n", i, j, dp[i][j]);
            }

        ans = INF;
        for (int j = 0; j <= m; j++) ans = std::min(ans, dp[n][j]);
        printf("Case %d: %d\n", cas, ans);
    }
    return 0;
}
