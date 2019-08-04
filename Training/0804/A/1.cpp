#include <cstdio>
#include <vector>

const int N = 110;
const int MOD = 998244353;
int n, m, dp[2][N][N][N], ans;
std::vector<std::pair<int, int>> cond[N];

void inc(int &a, int b) {
    a = a + b;
    a >= MOD ? a -= MOD : 0;
}

bool check(int r, int j, int k, int l) {
    for (auto p : cond[r]) {
        if (p.second == 1) {
            if (!(p.first > j)) return false;
        } else if (p.second == 2) {
            if (!(p.first <= j && p.first > k)) return false;
        } else if (p.second == 3) {
            if (!(p.first <= k && p.first > l)) return false;
        } else {
            if (!(p.first <= l)) return false;
        }
    }
    return true;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 4; i <= n + 3; i++) cond[i].clear();
        for (int i = 1; i <= m; i++) {
            static int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            cond[r + 3].emplace_back(l + 3, x);
        }
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < j; k++)
                for (int l = 0; l < k; l++)
                    dp[0][j][k][l] = 0;
        dp[0][3][2][1] = 1;
        dp[0][3][2][0] = 1;
        dp[0][3][1][0] = 1;
        dp[0][2][1][0] = 1;
        for (int i = 4; i <= n + 3; i++) {
            int ci = i & 1, ni = !ci;
            for (int j = 0; j <= i; j++)
                for (int k = 0; k < j; k++)
                    for (int l = 0; l < k; l++)
                        dp[ni][j][k][l] = 0;
            for (int j = 0; j < i; j++)
                for (int k = 0; k < j; k++)
                    for (int l = 0; l < k; l++)
                        if (check(i, j, k, l)) {
                            inc(dp[ni][j][k][l], dp[ci][j][k][l]);
                            inc(dp[ni][i][k][l], dp[ci][j][k][l]);
                            inc(dp[ni][i][j][l], dp[ci][j][k][l]);
                            inc(dp[ni][i][j][k], dp[ci][j][k][l]);
                        }
        }
        ans = 0;
        int ci = (n + 3) & 1;
        for (int j = 0; j < n + 3; j++)
            for (int k = 0; k < j; k++)
                for (int l = 0; l < k; l++)
                    if (check(n + 3, j, k, l))
                        inc(ans, dp[ci][j][k][l]);
        printf("%d\n", ans);
    }
    return 0;
}
