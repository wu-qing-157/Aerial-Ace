#include <cstdint>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 3e5 + 10;
int n, m, a[N], x[N], y[N], cu, cd, cl, cr, mu, md, ml, mr, dx, dy;

int lowbit(int x) {
    return x & (-x);
}

struct bit {
    int a[N];
    void init() {
        memset(a, 0, (n + 1) * sizeof(int));
    }
    void add(int x) {
        for (; x <= n; x += lowbit(x)) a[x]++;
    }
    int query(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x)) ret += a[x];
        return ret;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
} up, down;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        cu = mu = cl = ml = 1, cd = md = cr = mr = n;
        dx = dy = 0;
        up.init(), down.init();
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", x + i, y + i);
            a[x[i]] = y[i];
        }
        up.add(a[1]), down.add(a[n]);
        for (int qq = 1; qq <= m; qq++) {
            static char opp[2], &op = opp[0]; static int k;
            scanf("%s", opp);
            if (op == 'U') {
                scanf("%d", &k);
                if (cu + k > md) k = md - cu;
                dx -= k;
                cu += k, cd += k;
                if (cu > mu) {
                    for (int i = mu + 1; i <= cu; i++)
                        up.add(a[i]);
                    mu = cu;
                }
            } else if (op == 'D') {
                scanf("%d", &k);
                if (cd - k < mu) k = cd - mu;
                dx += k;
                cd -= k, cu -= k;
                if (cd < md) {
                    for (int i = md - 1; i >= cd; i--)
                        down.add(a[i]);
                    md = cd;
                }
            } else if (op == 'L') {
                scanf("%d", &k);
                if (cl + k > mr) k = mr - cl;
                dy -= k;
                cl += k, cr += k;
                ml = std::max(ml, cl);
            } else if (op == 'R') {
                scanf("%d", &k);
                if (cr - k < ml) k = cr - ml;
                dy += k;
                cr -= k, cl -= k;
                mr = std::min(mr, cr);
            } else if (op == '?') {
                scanf("%d", &k);
                printf("%d %d\n", std::min(md, std::max(mu, x[k])) + dx, std::min(mr, std::max(ml, y[k])) + dy);
            } else if (op == '!') {
                if (mu == md && ml == mr) {
                    printf("%lld\n", 1ll * n * (n - 1) / 2);
                } else if (ml == mr) {
                    printf("%lld\n", 1ll * mu * (mu - 1) / 2 + 1ll * (n - md + 1) * (n - md) / 2);
                } else if (mu == md) {
                    printf("%lld\n", 1ll * ml * (ml - 1) / 2 + 1ll * (n - mr + 1) * (n - mr) / 2);
                } else {
                    int64_t ans = 0, c;
                    c = up.query(ml), ans += c * (c - 1) / 2;
                    c = up.query(mr, n), ans += c * (c - 1) / 2;
                    c = down.query(ml), ans += c * (c - 1) / 2;
                    c = down.query(mr, n), ans += c * (c - 1) / 2;
                    printf("%lld\n", ans);
                }
            } else {
                puts("FUCK");
            }
            // printf("--> %d %d %d %d   %d %d %d %d   %d %d\n", cu, cd, cl, cr, mu, md, ml, mr, dx, dy);
        }
    }
    return 0;
}
