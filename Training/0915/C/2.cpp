#include <cmath>
#include <cstdint>
#include <cstdio>
#include <algorithm>

const int N = 4e5 + 10;

using number = long double;
const number pi = std::acos((number) -1);

struct complex {
    number r, i;
    complex() : r(0), i(0) {}
    complex(number r, number i) : r(r), i(i) {}
    explicit complex(number t) : r(std::cos(t)), i(std::sin(t)) {}
    friend complex operator+(const complex &a, const complex &b) {
        return complex(a.r + b.r, a.i + b.i);
    }
    friend complex operator-(const complex &a, const complex &b) {
        return complex(a.r - b.r, a.i - b.i);
    }
    friend complex operator*(const complex &a, const complex &b) {
        return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
    }
} w[N];
int nn, rev[N];

void prepare(int len) {
    int x = 0;
    for (nn = 1; nn < len; nn <<= 1) x++;
    for (int i = 1; i < nn; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (x - 1));
    for (int i = 0; i < nn; i++) w[i] = complex(2 * pi * i / nn);
}

void fft(complex *a) {
    for (int i = 0; i < nn; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int i = 2, d = nn >> 1; i <= nn; i <<= 1, d >>= 1)
        for (int j = 0; j < nn; j += i) {
            complex *l = a + j, *r = a + j + (i >> 1), *p = w, tp;
            for (int k = 0; k < (i >> 1); k++, l++, r++, p += d)
                tp = *r * *p, *r = *l - tp, *l = *l + tp;
        }
}

void fft_main(int n, int m, int *A, int *B, int64_t *ret) {
    prepare(n + m);
    static complex a[N], b[N];
    for (int i = 0; i < nn; i++) a[i] = complex(A[i], 0);
    for (int i = 0; i < nn; i++) b[i] = complex(B[i], 0);
    fft(a), fft(b);
    for (int i = 0; i < nn; i++) a[i] = a[i] * b[i];
    std::reverse(a + 1, a + nn);
    fft(a);
    // for (int i = 0; i < 2e5; i++) if (a[i].r / nn >= 0.4 || a[i].r / nn <= -0.4) printf("%.2f\n", a[i].r / nn);
    for (int i = 0; i < nn; i++) ret[i] = int64_t(a[i].r / nn + 0.5);
}

const int E = 100000;
int n, tmp, a[N], b[N], cnt[N];
int64_t ret[N], ans;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d", &n);
        if (n > 1000) {
            for (int i = 1; i <= E; i++) a[i] = b[i] = cnt[i] = 0;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), a[tmp]++;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), b[tmp]++;
            for (int i = 1; i <= n; i++) scanf("%d", &tmp), cnt[tmp]++;
            for (int i = 1; i <= E; i++) cnt[i] += cnt[i - 1];
            ans = 1ll * n * n * n;
            fft_main(E + 1, E + 1, a, b, ret);
            for (int i = 0; i <= E; i++) printf("%lld\n", ret[i]);
            return 0;
            // for (int i = 0; i <= 2 * E; i++) if (ret[i]) printf("%d %lld\n", i, ret[i]);
            for (int i = 0; i <= E; i++) ans -= ret[i] * (cnt[E] - cnt[i]);
            std::reverse(b, b + E + 1);
            fft_main(E + 1, E + 1, a, b, ret);
            // for (int i = 0; i <= 2 * E; i++) if (ret[i]) printf("%d %lld\n", i, ret[i]);
            for (int i = 0; i < E; i++) ans -= ret[i] * cnt[E - i - 1];
            for (int i = E + 1; i <= 2 * E; i++) ans -= ret[i] * cnt[i - E - 1];
            printf("Case #%d: %lld\n", cas, ans);
        } else {
            for (int i = 1; i <= E; i++) cnt[i] = 0;
            for (int i = 1; i <= n; i++) scanf("%d", a + i);
            for (int i = 1; i <= n; i++) scanf("%d", b + i);
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
