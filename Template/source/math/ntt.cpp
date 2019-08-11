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

void ntt_main(int n, int m, int64_t *A, int64_t *B, int64_t *ret) {
    prepare(n + m);
    static int64_t a[N], b[N];
    for (int i = 0; i < nn; i++) a[i] = A[i];
    for (int i = 0; i < nn; i++) b[i] = B[i];
    ntt(a), ntt(b);
    for (int i = 0; i < nn; i++) (a[i] *= b[i]) %= MOD;
    std::reverse(a + 1, a + nn);
    ntt(a);
    for (int i = 0; i < nn; i++) ret[i] = a[i] * invn % MOD;
}
