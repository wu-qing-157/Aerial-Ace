#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <algorithm>

#define y1 yyyy

const int MOD = 1025436931;

template <int N, int M>
struct matrix {
    int64_t a[3][3];
    int64_t *operator[](int i) {
        return a[i];
    }
    const int64_t *operator[](int i) const {
        return a[i];
    }
};

template <int N, int M, int K>
matrix<N, K> operator*(const matrix<N, M> &a, const matrix<M, K> &b) {
    matrix<N, K> ret;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < K; j++)
            ret[i][j] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            for (int k = 0; k < K; k++)
                (ret[i][k] += a[i][j] * b[j][k]) %= MOD;
    return ret;
}

matrix<1, 3> init;
matrix<3, 3> sing;

matrix<3, 3> pow(matrix<3, 3> a, int64_t exp) {
    exp--;
    auto ans = a;
    while (exp) {
        if (exp & 1) ans = ans * a;
        a = a * a;
        exp >>= 1;
    }
    return ans;
}

int64_t step2(int64_t x) {
    if (x == 1) return 1;
    else if (x == 2) return 2;
    else {
        init[0][0] = 1, init[0][1] = 2, init[0][2] = 4;
        sing[0][0] = 0, sing[0][1] = 0, sing[0][2] = -1;
        sing[1][0] = 1, sing[1][1] = 0, sing[1][2] = 0;
        sing[2][0] = 0, sing[2][1] = 1, sing[2][2] = 2;
        auto ret = init * pow(sing, x - 1);
        return ret[0][0];
    }
    assert(false);
}

int64_t n, m, x1, y1, x2, y2;

int64_t step1() {
    if (x1 == x2 && y1 == y2) return 1;
    if (n == 1) n = m, x1 = y1, x2 = y2;
    if (m == 1) {
        if (x2 > x1) return n - x2;
        else return x2 - 1;
    }
    if ((x1 ^ y1 ^ x2 ^ y2) & 1) return -1;
    if (llabs(x1 - x2) == llabs(y1 - y2)) {
        if (x1 <= x2 && y1 <= y2) return x2 - 2 + y2 - 2 + 1;
        else if (x1 >= x2 && y1 <= y2) return n - 1 - x2 + y2 - 2 + 1;
        else if (x1 <= x2 && y1 >= y2) return x2 - 2 + m - 1 - y2 + 1;
        else return n - 1 - x2 + m - 1 - y2 + 1;
    } else {
        if (std::abs(x1 - x2) < std::abs(y1 - y2)) {
            if (y1 <= y2) return std::max(x2 - 2, n - 1 - x2) + y2 - 2 + 1;
            else return std::max(x2 - 2, n - 1 - x2) + m - 1 - y2 + 1;
        } else {
            if (x1 <= x2) return x2 - 2 + std::max(y2 - 2, m - 1 - y2) + 1;
            else return n - 1 - x2 + std::max(y2 - 2, m - 1 - y2) + 1;
        }
    }
    assert(false);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld%lld%lld%lld", &n, &m, &x1, &y1, &x2, &y2);
        auto ret = step1();
        if (ret == -1)
            puts("countless");
        else
            printf("%lld\n", step2(ret));
    }
    return 0;
}
