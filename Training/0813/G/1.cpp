#include <cstdio>
#include <initializer_list>

const int N = 1e5 + 10, MOD = 998244353;
int dp[N][2][3][3], ans, x, n, y;

void inc(int &a, int b) {
    a = a + b < MOD ? a + b : a + b - MOD;
}

void left(int i) {
    for (int k1 : {0, 1})
        for (int k2 : {1, 2}) {
            inc(dp[i][1][0][2], dp[i - 1][k1][0][k2]);
            inc(dp[i][0][0][k2], dp[i - 1][k1][k2][0]);
        }
}

void right(int i) {
    for (int k1 : {0, 1})
        for (int k2 : {0, 2}) {
            inc(dp[i][1][1][2], dp[i - 1][k1][1][k2]);
            inc(dp[i][0][1][k2], dp[i - 1][k1][k2][1]);
        }
}

void mid(int i) {
    for (int k1 : {0, 1, 2})
        for (int k2 : {0, 1, 2})
            inc(dp[i][1][2][k1], dp[i - 1][1][k1][k2]);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &x, &y);
        dp[2][1][1][0] = x != 2 && y != 1;
        dp[2][1][0][1] = x != 1 && y != 2;
        for (int i = 3; i <= n; i++) {
            for (int k1 : {0, 1})
                for (int k2 : {0, 1, 2})
                    for (int k3 : {0, 1, 2})
                        dp[i][k1][k2][k3] = 0;
            if (i == x) {
                left(i);
            } else if (i == y) {
                right(i);
            } else if (i < x) {
                left(i), mid(i), right(i);
            } else if (i < y) {
                mid(i), right(i);
            } else {
                mid(i);
            }
            /*
            for (int k1 : {0, 1})
                for (int k2 : {0, 1, 2})
                    for (int k3 : {0, 1, 2})
                        printf("dp[%d][%d][%d][%d] = %d\n", i, k1, k2, k3, dp[i][k1][k2][k3]);
                        */
        }
        ans = 0;
        for (int k1 : {0, 1})
            for (int k2 : {0, 1, 2})
                for (int k3 : {0, 1, 2})
                    inc(ans, dp[n][k1][k2][k3]);
        printf("%d\n", ans);
    }
    return 0;
}
