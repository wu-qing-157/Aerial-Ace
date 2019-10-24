#include <cstdio>
#include <vector>

const int N = 10;
int k, m, n, e[N], p[N], lans;
std::vector<int> vec;
bool v[N];

void dfs(int ce, int cp, int ans) {
    for (int i : vec) printf("%d", i);
    printf("    (%d %d %d)\n", ce, cp, ans);
    lans = std::max(lans, ans + (ce - 1) / k);
    if (ce <= k) return;
    for (int i = 1; i <= n; i++) if (!v[i]) {
        int cur = ans, cure = ce, curp = cp, f1 = true, f2 = true;
        while (cure > k && (f1 || f2)) {
            cur++, cure -= k, curp = std::max(curp - m, 0);
            if (f1 && curp + p[i] < 100) {
                v[i] = true;
                vec.push_back(i);
                dfs(std::min(cure + e[i], 100), curp + p[i], cur);
                vec.pop_back();
                v[i] = false;
                f1 = false;
            }
            if (f2 && cure + e[i] < 100) {
                v[i] = true;
                vec.push_back(i);
                dfs(std::min(cure + e[i], 100), curp + p[i], cur);
                vec.pop_back();
                v[i] = false;
                f1 = false;
            }
        }
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &k, &m, &n);
        lans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", e + i);
        for (int i = 1; i <= n; i++) scanf("%d", p + i);
        dfs(100, 0, 0);
        printf("%d\n", lans);
    }
    return 0;
}
