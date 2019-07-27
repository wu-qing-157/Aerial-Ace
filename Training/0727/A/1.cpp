#include <cstdio>
#include <cassert>
#include <algorithm>

using number = long double;
const number eps = 1e-9;

int sgn(number x) {
    return (x > eps) - (x < -eps);
}

struct point {
    number x, y;
    point() {}
    point(number x, number y) : x(x), y(y) {}
    
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, number b) {
        return point(a.x * b, a.y * b);
    }
    friend number dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend number det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

struct line {
    point a, b;
    line() : a(), b() {}
    line(point a, point b) : a(a), b(b) {}
};

number ans;
point p[2][3], v[2];
line l[2][3];

bool point_on_seg(const point &p, const line &l) {
    //printf("%Lf\n", det(p - l.a, p - l.b));
    //assert(sgn(det(p - l.a, p - l.b)) == 0);
    return sgn(dot(p - l.a, l.b - l.a)) >= 0 && sgn(dot(p - l.b, l.a - l.b)) >= 0;
}

void solve(const point &p, const line &l, const point &v) {
    number a = det(v, l.b - l.a);
    number b = det(p - l.a, p - l.b);
    //printf("%Lf %Lf\n", a, b);
    if (sgn(a) == 0) return;
    number ret = b / a;
    if (sgn(ret) <= 0) return;
    if (point_on_seg(p + v * ret, l)) ans = std::min(ans, ret);
}

int main() {
    /*
    while (true) {
        point p, v;
        line l;
        scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf", &p.x, &p.y, &l.a.x, &l.a.y, &l.b.x, &l.b.y, &v.x, &v.y);
        solve(p, l, v);
        return 0;
        */
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 1e60;
        for (int i : { 0, 1 }) {
            for (int j : { 0, 1, 2 }) {
                static int tx, ty;
                scanf("%d%d", &tx, &ty);
                p[i][j] = point(tx, ty);
            }
            for (int j : { 0, 1, 2 }) l[i][j] = line(p[i][j], p[i][(j + 1) % 3]);
            static int tx, ty;
            scanf("%d%d", &tx, &ty);
            v[i] = point(tx, ty);
        }
        for (int i : { 0, 1 }) for (int j1 : { 0, 1, 2 }) for (int j2 : { 0, 1, 2 })
            solve(p[i][j1], l[!i][j2], v[i] - v[!i]);
        if (ans > 1e50) puts("NO COLLISION");
        else printf("%.10f\n", (double) ans);
    }
    return 0;
}
