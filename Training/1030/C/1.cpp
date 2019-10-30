#include <cstdint>
#include <cstdio>
#include <cstring>

const int64_t MOD = 2147493647;

template <int N, int M>
struct matrix {
    int64_t a[N][M];
    matrix() {
        memset(a, 0, sizeof a);
    }
    int64_t *operator[](int i) {
        return a[i];
    }
    const int64_t *operator[](int i) const {
        return a[i];
    }
};

template <int N>
matrix<N, N> epsilon() {
    matrix<N, N> mat;
    for (int i = 0; i < N; i++) mat[i][i] = 1;
    return mat;
}

template <int N, int M, int K>
matrix<N, K> operator*(const matrix<N, M> &a, const matrix<M, K> &b) {
    matrix<N, K> ret;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < K; k++)
                (ret[i][k] += a[i][j] * b[j][k] % MOD) %= MOD;
    return ret;
}

int a, b, n;

template <int N>
matrix<N, N> pow(matrix<N, N> a, int exp) {
    auto ret = a; exp--;
    while (exp) {
        if (exp & 1) ret = ret * a;
        a = a * a;
        exp >>= 1;
    }
    return ret;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &a, &b);
        if (n == 1) {
            printf("%d\n", a);
        } else if (n == 2) {
            printf("%d\n", b);
        } else {
            matrix<1, 7> m1;
            m1[0][0] = a, m1[0][1] = b, m1[0][2] = 1, m1[0][3] = 3, m1[0][4] = 9, m1[0][5] = 27, m1[0][6] = 81;
            matrix<7, 7> t;
            t[0][1] = 2;
            t[1][0] = t[1][1] = 1;
            t[2][2] = t[2][3] = t[2][4] = t[2][5] = t[2][6] = 1;
            t[3][3] = 1, t[3][4] = 2, t[3][5] = 3, t[3][6] = 4;
            t[4][4] = 1, t[4][5] = 3, t[4][6] = 6;
            t[5][5] = 1, t[5][6] = 4;
            t[6][1] = t[6][6] = 1;
            matrix<1, 7> ret = m1 * pow(t, n - 2);
            printf("%lld\n", ret[0][1]);
        }
    }
    return 0;
}
