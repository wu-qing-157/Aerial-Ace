#include <cstdio>
#include <algorithm>

const int N = 6;
using number = long double;
number dp[N][N][N][N];

number solve(int a, int b, int c, int d) {
    for (int ia = 0; ia <= a; ia++)
        for (int ib = 0; ib <= b; ib++)
            for (int ic = 0; ic <= c; ic++)
                for (int id = 0; id <= d; id++)
                    dp[ia][ib][ic][id] = 1e50;
    dp[a][b][c][d] = 0;
    for (int i = 1; i <= 2000; i++) {
        for (int ia = 0; ia <= a; ia++)
            for (int ib = 0; ib <= b; ib++)
                for (int ic = 0; ic <= c; ic++)
                    for (int id = 0; id <= d; id++)
                        for (int *choi : { &a, &b, &c, &d }) {
                            number result = 0;
                            int cnt = 0;
                            for (int ta : { ia - 1, ia, ia + 1 }) {
                                if (ta < 0 || ta > a) continue;
                                if (choi == &a && ta != ia + 1) continue;
                                for (int tb : { ib - 1, ib, ib + 1 }) {
                                    if (tb < 0 || tb > b) continue;
                                    if (choi == &b && tb != ib + 1) continue;
                                    for (int tc : { ic - 1, ic, ic + 1 }) {
                                        if (tc < 0 || tc > c) continue;
                                        if (choi == &c && tc != ic + 1) continue;
                                        for (int td : { id - 1, id, id + 1 }) {
                                            if (td < 0 || td > d) continue;
                                            if (choi == &d && td != id + 1) continue;
                                            result += dp[ta][tb][tc][td] + 1;
                                            cnt++;
                                        }
                                    }
                                }
                            }
                            result /= cnt;
                            dp[ia][ib][ic][id] = std::min(dp[ia][ib][ic][id], result);
                        }
        // printf("%.20f\n", dp[0][0][0][0]);
    }
    return dp[0][0][0][0];
}

int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    printf("%.20Lf\n", solve(a, b, c, d));
    return 0;
}
