#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

const int N = 210;

int sgn(int x) {
    return (x > 0) - (x < 0);
}

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend int det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend int dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
};

int n, ansk, ans = ~0u >> 2;
point a[N];
std::pair<point, int> aa[N];
bool nostart[N], nostop[N];
std::pair<int, int> anspair;
std::vector<std::pair<int, int>> from[N];
std::vector<int> output;
std::unordered_map<int, std::pair<int, int>> dp[N][N];

int main() {
    freopen("division.in", "r", stdin);
    freopen("division.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d", &aa[i].first.x, &aa[i].first.y), aa[i].second = i;
    std::sort(aa, aa + n, [](const auto &a, const auto &b) { return a.first.x < b.first.x; });
    for (int i = 0; i < n; i++) a[i] = aa[i].first;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (a[i].y == a[j].y)
        nostart[j] = nostop[i] = true;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (a[j].x > a[i].x) {
        bool ok = true;
        for (int k = 0; k < n; k++) if (det(a[k] - a[i], a[k] - a[j]) == 0 && dot(a[k] - a[i], a[j] - a[i]) > 0 && dot(a[k] - a[j], a[i] - a[j]) > 0) {
            ok = false;
            break;
        }
        if (ok) {
            int num = 0;
            for (int k = 0; k < n; k++) if (i != k && j != k && a[k].x >= a[i].x && a[k].x < a[j].x)
                num += sgn(det(a[j] - a[i], a[k] - a[i]));
            from[j].emplace_back(i, num);
        }
    }
    /*
    for (int j = 0; j < n; j++) for (auto p : from[j])
        printf("%d %d %d\n", p.first, j, p.second);
        */
    for (int i = 0; i < n; i++) if (!nostart[i]) {
        int num = 0;
        for (int k = 0; k < n; k++) if (i != k && a[k].x < a[i].x) {
            if (a[k].y > a[i].y) num++;
            else num--;
        }
        dp[i][1][num] = std::make_pair(-1, 0);
    }
    for (int j = 0; j < n; j++) for (auto p : from[j]) {
        int i = p.first, delta = p.second;
        // printf("%d %d\n", i, j);
        for (int k = 1; k < n; k++) for (auto pp : dp[i][k])
            dp[j][k + 1][pp.first + delta] = std::make_pair(i, pp.first);
    }
    for (int i = 0; i < n; i++) if (!nostop[i]) {
        int num = 0;
        for (int k = 0; k < n; k++) if (i != k && a[k].x >= a[i].x) {
            if (a[k].y > a[i].y) num++;
            else num--;
        }
        for (int k = 1; k <= n; k++) for (auto pp : dp[i][k]) {
            int resnum = pp.first + num;
            int up = (n - k + resnum) / 2;
            int down = up - resnum;
            int result = std::max(k, std::max(up, down)) - std::min(k, std::min(up, down));
            if (result < ans) {
                ans = result;
                ansk = k;
                anspair = std::make_pair(i, pp.first);
            }
        }
    }
    /*
    for (int i = 0; i < n; i++) printf("%d %d\n", a[i].x, a[i].y);
    for (int i = 0; i < n; i++) for (int k = 0; k <= n; k++) for (auto pp : dp[i][k])
        printf("%d %d %d %d\n", i, k, pp.first, pp.second.first);
    puts("");
    */
    fflush(stdout);
    while (anspair.first != -1) {
        output.push_back(anspair.first);
        anspair = dp[anspair.first][ansk][anspair.second];
        ansk--;
    }
    printf("%d\n", (int) output.size());
    for (auto it = output.rbegin(); it != output.rend(); it++)
        printf("%d%c", aa[*it].second + 1, " \n"[it + 1 == output.rend()]);
    return 0;
}
