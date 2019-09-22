#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 4e5 + 10;
const int64_t MOD = 4179340454199820289LL, G = 3;
int nn, rev[N];
int64_t w[N], invn;

int64_t mul(int64_t x, int64_t y) {
    int64_t t = (x * y - (int64_t) ((long double) x / MOD * y + 1e-3) * MOD) % MOD;
    return t < 0 ? t + MOD : t;
}

int64_t pow(int64_t a, int64_t exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) ret = mul(ret, a);
        a = mul(a, a);
        exp >>= 1;
    }
    return ret;
}

void prepare(int len) {
    int x = 0;
    for (nn = 1; nn < len; nn <<= 1) x++;
    for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (x - 1));
    w[0] = 1, w[1] = pow(G, (MOD - 1) / nn);
    for (int i = 2; i < nn; i++) w[i] = mul(w[i - 1], w[1]);
    invn = pow(nn, MOD - 2);
}

void ntt(int64_t *a) {
    for (int i = 0; i < nn; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int i = 2, d = nn >> 1; i <= nn; i <<= 1, d >>= 1)
        for (int j = 0; j < nn; j += i) {
            int64_t *l = a + j, *r = a + j + (i >> 1), *p = w, tp;
            for (int k = 0; k < (i >> 1); k++, l++, r++, p += d) {
                tp = mul(*r, *p) % MOD;
                *r = *l - tp < 0 ? *l - tp + MOD : *l - tp;
                *l = *l + tp < MOD ? *l + tp : *l + tp - MOD;
            }
        }
}

void ntt_main(int n, int m, int64_t *A, int64_t *B, int64_t *ret) {
    prepare(n + m);
    static int64_t a[N], b[N];
    for (int i = 0; i < nn; i++) a[i] = A[i];
    for (int i = 0; i < nn; i++) b[i] = B[i];
    ntt(a), ntt(b);
    for (int i = 0; i < nn; i++) a[i] = mul(a[i], b[i]);
    std::reverse(a + 1, a + nn);
    ntt(a);
    for (int i = 0; i < nn; i++) ret[i] = mul(a[i], invn);
}

const int E = 100000;
int n, tmp, cnt[N];
int64_t ans, ret[N], a[N], b[N];

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d", &n);
        if (n > 0) {
            for (int i = 1; i <= E; i++) a[i] = b[i] = cnt[i] = 0;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), a[tmp]++;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), b[tmp]++;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), cnt[tmp]++;
            for (int i = 1; i <= E; i++) cnt[i] += cnt[i - 1];
            ans = 1ll * n * n * n;
            ntt_main(E + 1, E + 1, a, b, ret);
            for (int i = 0; i <= E; i++) printf("%lld\n", ret[i]);
            return 0;
            // for (int i = 0; i <= 2 * E; i++) if (ret[i]) printf("%d %lld\n", i, ret[i]);
            for (int i = 0; i <= 2 * E; i++) ans -= ret[i] * (cnt[E] - cnt[i]);
            std::reverse(b, b + E + 1);
            ntt_main(E + 1, E + 1, a, b, ret);
            // for (int i = 0; i <= 2 * E; i++) if (ret[i]) printf("%d %lld\n", i, ret[i]);
            for (int i = 0; i < E; i++) ans -= ret[i] * cnt[E - i - 1];
            for (int i = E + 1; i <= 2 * E; i++) ans -= ret[i] * cnt[i - E - 1];
            printf("Case #%d: %lld\n", cas, ans);
        } else {
            for (int i = 1; i <= E; i++) cnt[i] = 0;
            for (int i = 1; i <= n; i++) scanf("%lld", a + i);
            for (int i = 1; i <= n; i++) scanf("%lld", b + i);
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), cnt[tmp]++;
            for (int i = 1; i <= E; i++) cnt[i] += cnt[i - 1];
            ans = 1ll * n * n * n;
            for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
                if ((tmp = a[i] + b[j]) <= E) ans -= cnt[E] - cnt[tmp];
                if (tmp = std::abs(a[i] - b[j])) ans -= cnt[tmp - 1];
            }
            printf("Case #%d: %lld\n", cas, ans);
        }
    }
    return 0;
}
