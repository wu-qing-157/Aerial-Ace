#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int N = 20, MOD = 60;
int n, m, x[N], y[N], k[N], t[N], xl[N], xr[N], yl[N], yr[N];
std::vector<std::pair<int, int>> same, diff;
bool vs[MOD], vd[MOD];
int64_t ans;

int check(int xl, int xr, int yl, int yr) {
    for (int i = 0; i < MOD; i++) {
        vs[i] = vd[i] = true;
        for (auto p : same) if (i % p.first != p.second) vs[i] = false;
        for (auto p : diff) if (i % p.first != p.second) vd[i] = false;
    }
    int cnt = 0;
    for (int i = xl; i <= xr; i++)
        for (int j = yl; j <= yr; j++)
            if (vs[(i + j) % MOD] && vd[(MOD + i - j % MOD) % MOD])
                cnt++; // printf("        >> (%d %d)\n", i, j), cnt++;
    // printf("    >> (%d %d) (%d %d) %d\n", xl, yl, xr, yr, cnt);
    return cnt;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++)
            scanf("%d%d%d%d", x + i, y + i, k + i, t + i);
        for (int i = 1; i <= n; i++) xl[i] = x[i], yl[i] = y[i];
        std::sort(xl + 1, xl + n + 1);
        std::sort(yl + 1, yl + n + 1);
        for (int i = 0; i < n; i++) {
            xr[i] = xl[i + 1] - 1;
            yr[i] = yl[i + 1] - 1;
        }
        xr[n] = yr[n] = m;
        ans = 0;
        for (int i = 0; i <= n; i++) if (xl[i] <= xr[i])
            for (int j = 0; j <= n; j++) if (yl[j] <= yr[j]) {
                int64_t backup = ans;
                same.clear(), diff.clear();
                for (int ii = 1; ii <= n; ii++) {
                    if (xr[i] >= x[ii] && yr[j] >= y[ii])
                        same.emplace_back(k[ii], (x[ii] + y[ii] + t[ii]) % k[ii]);
                    else if (xr[i] >= x[ii])
                        diff.emplace_back(k[ii], (x[ii] - y[ii] % k[ii] + t[ii] + k[ii]) % k[ii]);
                    else if (yr[j] >= y[ii])
                        diff.emplace_back(k[ii], (x[ii] - y[ii] % k[ii] - t[ii] + k[ii] * 2) % k[ii]);
                    else
                        same.emplace_back(k[ii], (x[ii] + y[ii] - t[ii] + k[ii]) % k[ii]);
                }
                // for (auto p : same) printf("same %d %d\n", p.first, p.second);
                // for (auto p : diff) printf("diff %d %d\n", p.first, p.second);
                ans += check(xl[i], (xl[i] / MOD + 1) * MOD - 1, yl[j], (yl[j] / MOD + 1) * MOD - 1);
                ans += check(xl[i], (xl[i] / MOD + 1) * MOD - 1, yr[j] / MOD * MOD, yr[j]);
                ans += check(xr[i] / MOD * MOD, xr[i], yl[j], (yl[j] / MOD + 1) * MOD - 1);
                ans += check(xr[i] / MOD * MOD, xr[i], yr[j] / MOD * MOD, yr[j]);
                ans += 1ll * (xr[i] / MOD - xl[i] / MOD - 1) * check(0, MOD - 1, yl[j], (yl[j] / MOD + 1) * MOD - 1);
                ans += 1ll * (xr[i] / MOD - xl[i] / MOD - 1) * check(0, MOD - 1, yr[j] / MOD * MOD, yr[j]);
                ans += 1ll * (yr[j] / MOD - yl[j] / MOD - 1) * check(xl[i], (xl[i] / MOD + 1) * MOD - 1, 0, MOD - 1);
                ans += 1ll * (yr[j] / MOD - yl[j] / MOD - 1) * check(xr[i] / MOD * MOD, xr[i], 0, MOD - 1);
                ans += 1ll * (xr[i] / MOD - xl[i] / MOD - 1) * (yr[j] / MOD - yl[j] / MOD - 1) * check(0, MOD - 1, 0, MOD - 1);
                // printf("big (%d %d) (%d %d)  %lld\n", xl[i], yl[j], xr[i], yr[j], ans - backup);
            }
        printf("%lld\n", ans);
    }
    return 0;
}
