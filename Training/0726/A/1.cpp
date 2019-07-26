#include <cstdio>
#include <cmath>
#include <algorithm>

using number = long double;
const number eps = 1e-10;

number _sqrt(number x) {
    return std::sqrt(std::max<number>(x, 0));
}

struct point {
    number x, y, z;
    point() {}
    point(number x, number y, number z) : x(x), y(y), z(z) {}
    
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y, a.z - b.z);
    }
    friend point operator*(const point &a, number b) {
        return point(a.x * b, a.y * b, a.z * b);
    }
    friend number dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    number len2() const {
        return x * x + y * y + z * z;
    }
    number len() const {
        return _sqrt(len2());
    }
    point norm(number v) const {
        return *this * (v / len());
    }
};

const int N = 1e3 + 10;
int n;
point a[N], b[N], v[N];
number r[N], t[N], T[N], V[N], ans;

void solve(number a, number b, number c, number l, number r) {
    // printf("%Lf %Lf %Lf    %Lf %Lf\n", a, b, c, l, r);
    number delta = b * b - 4 * a * c;
    if (delta < -eps) return;
    for (number x : { (-b + _sqrt(delta)) / (2 * a), (-b - _sqrt(delta)) / (2 * a) })
        if (x >= l - eps && x <= r + eps)
            ans = std::min(ans, x);
}

int main() {
    while (scanf("%d", &n), n != -1) {
        ans = 1e60;
        for (int i = 1; i <= n; i++) {
            static int x1, y1, z1, x2, y2, z2, r1, t1, v1;
            scanf("%d%d%d%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2, &r1, &t1, &v1);
            a[i] = point(x1, y1, z1);
            b[i] = point(x2, y2, z2);
            r[i] = r1, t[i] = t1, V[i] = v1;
            T[i] = t[i] + (b[i] - a[i]).len() / V[i];
            v[i] = (b[i] - a[i]).norm(V[i]);
        }
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j) {
            if (i < j) solve(
                    (v[i] - v[j]).len2(),
                    2 * dot(a[i] - a[j] - (v[i] * t[i] - v[j] * t[j]), v[i] - v[j]),
                    (a[i] - a[j] - (v[i] * t[i] - v[j] * t[j])).len2() - (r[i] + r[j]) * (r[i] + r[j]),
                    std::max(t[i], t[j]), std::min(T[i], T[j]));
            solve(
                    v[i].len2(),
                    2 * dot(a[i] - a[j] - v[i] * t[i], v[i]),
                    (a[i] - a[j] - v[i] * t[i]).len2() - (r[i] + r[j]) * (r[i] + r[j]),
                    t[i], std::min(T[i], t[j]));
            solve(
                    v[i].len2(),
                    2 * dot(a[i] - b[j] - v[i] * t[i], v[i]),
                    (a[i] - b[j] - v[i] * t[i]).len2() - (r[i] + r[j]) * (r[i] + r[j]),
                    std::max(t[i], T[j]), T[i]);
        }
        if (ans > 1e50) puts("Never");
        else printf("%.2f\n", (double) ans);
    }
    return 0;
}
