#include <cstdio>
#include <cstdint>
#include <vector>

const int64_t MOD = 1e9 + 7;
const int N = 1e6 + 10;
int64_t inv[N], f[N];
int n, d1[N], d2[N];
std::vector<int> to[N];

int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

void dfs1(int cur, int fa) {
    d1[cur] = d1[fa] + 1;
    for (int ch : to[cur]) if (ch != fa)
        dfs1(ch, cur);
    d2[fa] = std::max(d2[fa], d2[cur] + 1);
}

void dfs2(int cur, int fa) {
    for (int ch : to[cur]) if (ch != fa)
        dfs2(ch, cur);
    if (d1[cur] + d2[cur] != d2[0]) {
        f[cur] = 0;
    } else {
        f[cur] = 1;
        int sz = (int) to[cur].size();
        if (cur != 1) sz--;
        if (sz != 0) {
            int64_t q = 0;
            for (int ch : to[cur]) if (ch != fa)
                (q += inv[sz] * (1 - f[ch])) %= MOD;
            f[cur] = (1 - pow(q, sz)) % MOD;
            if (f[cur] < 0) f[cur] += MOD;
        }
    }
}

int main() {
    inv[1] = 1;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        static int s, t;
        scanf("%d%d", &s, &t);
        to[s].push_back(t);
        to[t].push_back(s);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld\n", f[1]);
    return 0;
}
