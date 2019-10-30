#include <cstdint>
#include <cstdio>

const int N = 260;

namespace odd {

uint16_t dp[N][N][N];

void init() {
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++) {
                if (i & 1) {
                    uint16_t va = dp[i - 1][j][k] + 1, vb;
                    for (int x = 1; x < N; x++) {
                        if (k < x || (vb = dp[i - 1][j][k - x]) >= va) {
                            dp[i][j][k] = va;
                            break;
                        }
                        if (j < x || (va = dp[i - 1][j - x][k] + 1) <= vb) {
                            dp[i][j][k] = vb;
                            break;
                        }
                    }
                } else {
                    uint16_t va, vb = dp[i - 1][j][k];
                    for (int x = 0; x < N; x++) {
                        if (j < x || (va = dp[i - 1][j - x][k] + 1) <= vb) {
                            dp[i][j][k] = vb;
                            break;
                        }
                        if (k < x || (vb = dp[i - 1][j][k - x]) >= va) {
                            dp[i][j][k] = va;
                            break;
                        }
                    }
                }
            }
}

} // namespace odd

namespace even {

uint16_t dp[N][N][N];

void init() {
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++) {
                if (i & 1) {
                    uint16_t va, vb = dp[i - 1][j][k];
                    for (int x = 0; x < N; x++) {
                        if (j < x || (va = dp[i - 1][j - x][k] + 1) <= vb) {
                            dp[i][j][k] = vb;
                            break;
                        }
                        if (k < x || (vb = dp[i - 1][j][k - x]) >= va) {
                            dp[i][j][k] = va;
                            break;
                        }
                    }
                } else {
                    uint16_t va = dp[i - 1][j][k] + 1, vb;
                    for (int x = 1; x < N; x++) {
                        if (k < x || (vb = dp[i - 1][j][k - x]) >= va) {
                            dp[i][j][k] = va;
                            break;
                        }
                        if (j < x || (va = dp[i - 1][j - x][k] + 1) <= vb) {
                            dp[i][j][k] = vb;
                            break;
                        }
                    }
                }
            }
}

} // namespace even

int main() {
    odd::init();
    even::init();
    static int T;
    scanf("%d", &T);
    while (T--) {
        static int n, a, b, alice;
        scanf("%d%d%d", &n, &a, &b);
        alice = n & 1 ? odd::dp[n][a][b] : even::dp[n][a][b];
        printf("Alice %d Bob %d\n", alice, n - alice);
    }
    return 0;
}
