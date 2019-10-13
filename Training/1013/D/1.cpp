#include <cstdint>
#include <cstdio>

const int64_t MOD = 998244353, INF = 6e17;
int64_t n, ans;

int64_t pow(int64_t a, int exp) {
    int64_t ret = 1;
    for (int i = 1; i <= exp; i++) {
        if (INF / ret <= a) return INF;
        else ret = ret * a;
    }
    return ret;
}

const int N = 1e8 + 10;
bool vis[N];
int pr[N], phi[N], prcnt;

int main() {
    static int T;
    scanf("%d", &T);
    printf("%ld\n", sizeof vis + sizeof pr + sizeof phi);
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) phi[pr[++prcnt] = i] = i - 1;
        for (int j = 1; j <= prcnt && i * pr[j] < N; ++j) {
            vis[i * pr[j]] = 1;
            if (i % pr[j]) {
                phi[i * pr[j]] = phi[i] * phi[pr[j]];
            } else {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            }
        }
    }
    while (T--) {
        scanf("%lld", &n);
        ans = n & 1 ? (n + 1) / 2 % MOD * (n % MOD) % MOD : n / 2 % MOD * ((n + 1) % MOD) % MOD;
        for (int l = 3, flag = true; flag; l++) {
            flag = false;
            for (int i = 2; true; i++) {
                if (pow(i, l) <= n) {
                    //printf("%d %d %lld\n", i, l, pow(i, l));
                    (ans += n / pow(i, l) * phi[i] % MOD) %= MOD;
                    flag = true;
                } else {
                    break;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
