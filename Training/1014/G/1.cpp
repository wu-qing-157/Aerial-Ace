#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

const int64_t MOD = 998244353;
const int N = 4e5 + 10;

namespace ntt {

int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

const int64_t G = 3;
using ::MOD;
int nn, rev[N];
int64_t w[N], invn;

void prepare(int len) {
    int x = 0;
    for (nn = 1; nn < len; nn <<= 1) x++;
    for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (x - 1));
    w[0] = 1, w[1] = pow(G, (MOD - 1) / nn);
    for (int i = 2; i < nn; i++) w[i] = w[i - 1] * w[1] % MOD;
    invn = pow(nn, MOD - 2);
}

void ntt(int64_t *a) {
    for (int i = 0; i < nn; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int i = 2, d = nn >> 1; i <= nn; i <<= 1, d >>= 1)
        for (int j = 0; j < nn; j += i) {
            int64_t *l = a + j, *r = a + j + (i >> 1), *p = w, tp;
            for (int k = 0; k < (i >> 1); k++, l++, r++, p += d) {
                tp = *r * *p % MOD;
                *r = *l - tp < 0 ? *l - tp + MOD : *l - tp;
                *l = *l + tp < MOD ? *l + tp : *l + tp - MOD;
            }
        }
}

void ntt_main(std::vector<int64_t> &A, std::vector<int64_t> &B) {
    int n = int(A.size()), m = int(B.size());
    prepare(n + m);
    static int64_t a[N], b[N];
    for (int i = 0; i < n; i++) a[i] = A[i];
    for (int i = n; i < nn; i++) a[i] = 0;
    for (int i = 0; i < m; i++) b[i] = B[i];
    for (int i = m; i < nn; i++) b[i] = 0;
    A.clear();
    ntt(a), ntt(b);
    for (int i = 0; i < nn; i++) (a[i] *= b[i]) %= MOD;
    std::reverse(a + 1, a + nn);
    ntt(a);
    for (int i = 0; i < n + m - 1; i++) A.push_back(a[i] * invn % MOD);
}

}

int64_t fac[N], inv[N];

int n, a, b, sum;
int64_t ans;
std::vector<int64_t> vec[N];

struct vec_cmp {
    bool operator()(const int &a, const int &b) const {
        return vec[a].size() > vec[b].size();
    }
};

std::priority_queue<int, std::vector<int>, vec_cmp> queue;

int main() {
    fac[0] = inv[0] = inv[1] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 2; i < N; i++) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    for (int i = 2; i < N; i++) (inv[i] *= inv[i - 1]) %= MOD;
    static int T;
    scanf("%d", &T);
    while (T--) {
        sum = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            sum += a;
            vec[i].clear();
            for (int k = 0; k <= std::min(a, b); k++)
                vec[i].push_back(fac[a] * fac[b] % MOD * inv[a - k] % MOD * inv[b - k] % MOD * inv[k] % MOD);
        }
        while (!queue.empty()) queue.pop();
        for (int i = 1; i <= n; i++) queue.push(i);
        while (queue.size() >= 2) {
            int i = queue.top(); queue.pop();
            int j = queue.top(); queue.pop();
            //printf("first   "); for (int k : vec[i]) printf(" %d", k); puts("");
            //printf("second  "); for (int k : vec[j]) printf(" %d", k); puts("");
            ntt::ntt_main(vec[i], vec[j]);
            //printf("result  "); for (int k : vec[i]) printf(" %d", k); puts("");
            //puts("");
            queue.push(i);
        }
        std::vector<int64_t> &ret = vec[queue.top()];
        ans = 0;
        for (int i = 0, op = 1; i <= sum && i < int(ret.size()); i++, op = -op) {
            (ans += op * ret[i] * fac[sum - i]) %= MOD;
            if (ans < 0) ans += MOD;
        }
        printf("%lld\n", ans);
    }
}
