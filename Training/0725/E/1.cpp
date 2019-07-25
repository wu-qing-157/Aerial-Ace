#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <unordered_map>

const int64_t MOD = 1e9 + 7;

const int N = 12, M = 100;
__int128_t n;
int m, p[N], k[N];
int64_t jie[M], inv[M], invj[M];
std::unordered_map<int, int64_t> map[2];

void init() {
    jie[0] = 1;
    for (int i = 1; i < M; i++) jie[i] = jie[i - 1] * i % MOD;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < M; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    invj[0] = 1;
    for (int i = 1; i < M; i++) invj[i] = invj[i - 1] * inv[i] % MOD;
}

int64_t pow(int64_t a, int64_t exp) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int64_t c(int n, int m) {
    return jie[n] * invj[m] % MOD * invj[n - m] % MOD;
}

void read() {
    n = 0;
    static char c;
    while ((c = getchar()) < '0')
        if (c == -1)
            exit(0);
    n = c - '0';
    while ((c = getchar()) >= '0')
        n = n * 10 + c - '0';
}

int main() {
    init();
    for (int cas = 1; true; cas++) {
        read();
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d", p + i);
            k[i] = 0;
            while (n % p[i] == 0) {
                k[i]++;
                n /= p[i];
            }
            k[i]++;
        }
        map[0].clear();
        map[0][1] = 1;
        for (int i = 1; i <= m; i++) {
            int cur = i & 1, las = !cur;
            map[cur].clear();
            for (int j = 0; j <= k[i] - 2; j++)
                for (const auto &p : map[las])
                    (map[cur][(k[i] - j) * p.first % MOD] += p.second * ((k[i] - j) & 1 ? -1 : 1) * c(k[i] - 1, j)) %= MOD;
        }
        auto &ret = map[m & 1];
        int64_t ans = 0;
        for (const auto &p : ret)
            printf("map %d %lld\n", p.first, p.second), (ans += p.second * p.first % MOD * pow(p.first - 1, MOD - 2)) %= MOD;
        if (ans < 0) ans += MOD;
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
