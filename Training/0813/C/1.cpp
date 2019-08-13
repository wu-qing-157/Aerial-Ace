#include <cstdio>
#include <cstdint>

struct point {
    int64_t x, y;
    point() {}
    point(int64_t x, int64_t y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend int64_t det(const poitn &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

point A, B, D, E, M, N, X, Y;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld", &A.x, &A.y);
        scanf("%lld%lld", &B.x, &B.y);
        scanf("%lld%lld", &M.x, &M.y);
        scanf("%lld%lld", &N.x, &N.y);
        scanf("%lld%lld", &X.x, &X.y);
        scanf("%lld%lld", &Y.x, &Y.y);
        scanf("%lld%lld", &S.x, &S.y);
        scanf("%lld%lld", &D.x, &D.y);
        scanf("%lld%lld", &T.x, &T.y);
        scanf("%lld%lld", &E.x, &E.y);

        D = D - S;
        E = E - T;

        int64_t a1 = det(D, A - B) - det(M - N, D);
        int64_t b1 = -det(E, M - N);
        int64_t c1 = det(M - N, S - N) + det(T - N, M - N) - det(S - B, A - B);
        int64_t a2 = -det(M - N, D);
        int64_t b2 = det(X - Y, E) - det(E, M - N);
        int64_t c2 = det(M - N, S - N) + det(T - N, M - N) - det(X - Y, T - Y);

int64_t :
    }
    return 0;
}
