// long double seems unnecessary
using number = double;
const int EXP = 15, POW2 = (1 << EXP) - 1, N = 3e5 + 10;;
const int64_t MOD = 1e9 + 7;
const number pi = std::acos((number) -1);

int nn, rev[N];

struct complex {
    number r, i;
    complex() : r(0), i(0) {}
    complex(number theta) : r(std::cos(theta)), i(std::sin(theta)) {}
    complex(number r, number i) : r(r), i(i) {}
    friend complex operator+(const complex &a, const complex &b) {
        return complex(a.r + b.r, a.i + b.i);
    }
    friend complex operator-(const complex &a, const complex &b) {
        return complex(a.r - b.r, a.i - b.i);
    }
    friend complex operator*(const complex &a, const complex &b) {
        return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
    }
    complex operator~() const {
        return complex(r, -i);
    }
} w[N];

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

// A & B must be in [0, MOD), ret will be in [0, MOD)
// A & B & ret being int32 doesn't matter
void mtt_main(int n, int m, int64_t *A, int64_t *B, int64_t *ret) {
    prepare(n + m);
    static complex a[N], b[N], Da[N], Db[N], Dc[N], Dd[N];
    for (int i = 0; i < nn; i++) a[i] = complex(A[i] & POW2, A[i] >> EXP);
    for (int i = 0; i < nn; i++) b[i] = complex(B[i] & POW2, B[i] >> EXP);
    fft(a), fft(b);
    for (int i = 0; i < nn; i++) {
        int j = (nn - i) & (nn - 1);
        static complex da, db, dc, dd;
        da = (a[i] + ~a[j]) * complex(0.5, 0);
        db = (a[i] - ~a[j]) * complex(0, -0.5);
        dc = (b[i] + ~b[j]) * complex(0.5, 0);
        dd = (b[i] - ~b[j]) * complex(0, -0.5);
        Da[j] = da * dc, Db[j] = da * dd, Dc[j] = db * dc, Dd[j] = db * dd;
    }
    for (int i = 0; i < nn; i++) a[i] = Da[i] + Db[i] * complex(0, 1);
    for (int i = 0; i < nn; i++) b[i] = Dc[i] + Dd[i] * complex(0, 1);
    fft(a), fft(b);
    for (int i = 0; i < nn; i++) {
        static int64_t da, db, dc, dd;
        da = int64_t(a[i].r / nn + 0.5) % MOD;
        db = int64_t(a[i].i / nn + 0.5) % MOD;
        dc = int64_t(b[i].r / nn + 0.5) % MOD;
        dd = int64_t(b[i].i / nn + 0.5) % MOD;
        ret[i] = (da + ((db + dc) << EXP) + (dd << (EXP << 1))) % MOD;
    }
}
