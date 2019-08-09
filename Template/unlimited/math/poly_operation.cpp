void inv_main(int n, int64_t *a, int64_t *b) {
    if (n == 1) {
        b[0] = pow(a[0], MOD - 2);
        return;
    }
    inv_main(n >> 1, a, b);
    prepare(n << 1);
    static int64_t tmp[N];
    for (int i = 0; i < n; i++) tmp[i] = a[i];
    for (int i = n; i < nn; i++) tmp[i] = 0;
    ntt(tmp), ntt(b);
    for (int i = 0; i < nn; i++) b[i] = (MOD + 2 - tmp[i] * b[i] % MOD) * b[i] % MOD;
    std::reverse(b + 1, b + nn);
    ntt(b);
    for (int i = 0; i < n; i++) b[i] = b[i] * invn % MOD;
    for (int i = n; i < nn; i++) b[i] = 0;
}
