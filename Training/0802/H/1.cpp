#include <cmath>
#include <cstdio>
#include <cstdint>

const int N = 1e6 + 10;
int vis[N], pr[N], pcnt, mu[N];

void solve() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            pr[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt && i * pr[j] < N; j++) {
            vis[i * pr[j]] = 1;
            if (i % pr[j] == 0) {
                mu[i * pr[j]] = 0;
                break;
            }
            mu[i * pr[j]] = -mu[i];
        }
    }
}

int64_t ans = 0;
int64_t calc(int n) {
    ans = 0;
    for (int i = 1; i <= n; i++) if (mu[i]) ans += std::floor(std::sqrt(1. * n / i));
    return ans;
}

int main() {
    solve();
    for (int i = 1; i <= 100; i++)
        printf("ans[%d] =\t%lld\n", i, calc(i));
    return 0;
}
