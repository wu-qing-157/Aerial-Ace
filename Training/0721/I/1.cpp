#include <cstdio>
#include <cmath>
#include <algorithm>
#include <deque>
#include <vector>

using number = long double;
const number eps = 1e-9, pi = std::acos((number) -1);

number _sqrt(number x) {
    return std::sqrt(std::max<number>(x, 0));
}
int sgn(number x) {
    return (x > eps) - (x < -eps);
}
int cmp(number x, number y) {
    return sgn(x - y);
}

struct point {
    number x, y;
    point() {}
    point(number x, number y) : x(x), y(y) {}

    number len2() const {
        return x * x + y * y;
    }
    number len() const {
        return _sqrt(len2());
    }
    point unit() const {
        return point(x / len(), y / len());
    }
    point rotate90() const {
        return point(-y, x);
    }
    number angle() const {
        return std::atan2(y, x);
    }

    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, number b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator/(const point &a, number b) {
        return point(a.x / b, a.y / b);
    }
    friend number det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend number dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend bool operator==(const point &a, const point &b) {
        return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0;
    }
};

struct line {
    point a, b;
    line() {}
    line(const point &a, const point &b) : a(a), b(b) {}
    point value() const {
        return b - a;
    }
};

struct circle {
    point o;
    number r;
    circle() {}
    circle(const point &o, number r) : o(o), r(r) {}
};

number dis(const point &a, const point &b) {
    return (a - b).len();
}

point intersect(const line &a, const line &b) {
    number s1 = det(a.b - a.a, b.a - a.a);
    number s2 = det(a.b - a.a, b.b - a.a);
    return (b.a * s2 - b.b * s1) / (s2 - s1);
}

bool intersect(const line &l, const circle &a, point &p1, point &p2) {
    number x = dot(l.a - a.o, l.b - l.a);
    number y = (l.b - l.a).len2();
    number d = x * x - y * ((l.a - a.o).len2() - a.r * a.r);
    if (sgn(d) < 0) return false;
    point p = l.a - (l.b - l.a) * (x / y), delta = (l.b - l.a) * (_sqrt(d) / y);
    p1 = p + delta, p2 = p - delta;
    return true;
}

bool intersect(const circle &a, const circle &b, point &p1, point &p2) {
    if (a.o == b.o) return false;
    number s1 = (b.o - a.o).len();
    if (cmp(s1, a.r + b.r) > 0 || cmp(s1, std::abs(a.r - b.r)) < 0) return false;
    number s2 = (a.r * a.r - b.r * b.r) / s1;
    number aa = (s1 + s2) / 2, bb = (s1 - s2) / 2;
    point p = (b.o - a.o) * (aa / (aa + bb)) + a.o;
    point delta = (b.o - a.o).unit().rotate90() * _sqrt(a.r * a.r - aa * aa);
    p1 = p + delta, p2 = p - delta;
    return true;
}

const int N = 14;
int n;
number d, D, ans = 1e60;
point p[N], ansp;
std::vector<line> lv;
std::vector<circle> cv;
std::deque<number> deque;

void check(const point &cur) {
    for (int i = 1; i <= n; i++)
        if (cmp(dis(cur, p[i]), d) < 0 || cmp(dis(cur, p[i]), D) > 0)
            return;
    deque.clear();
    for (int i = 1; i <= n; i++) {
        point delta = p[i] - cur;
        deque.push_back(delta.angle());
    }
    std::sort(deque.begin(), deque.end());
    for (int i = 0; i <= n; i++) {
        number curans = deque.back() - deque.front();
        if (cmp(curans, pi) <= 0 && curans < ans) {
            ans = curans;
            ansp = cur;
        }
        deque.push_back(deque.front() + 2 * pi);
        deque.pop_front();
    }
}

int main() {
    freopen("shepherd.in", "r", stdin);
    freopen("shepherd.out", "w", stdout);
    scanf("%d%Lf%Lf", &n, &d, &D);
    for (int i = 1; i <= n; i++) scanf("%Lf%Lf", &p[i].x, &p[i].y);
    // printf("%.20Lf (%.20Lf, %.20Lf)\n", ans, ansp.x, ansp.y);
    for (int i = 1; i <= n; i++) {
        cv.emplace_back(p[i], d);
        cv.emplace_back(p[i], D);
    }
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++)
        lv.emplace_back(p[i], p[j]);
    for (const auto &l1 : lv) for (const auto &l2 : lv)
        if (sgn(det(l1.value(), l2.value())) != 0) check(intersect(l1, l2));
    for (const auto &l : lv) for (const auto &c : cv) {
        point p1, p2;
        // printf("%.20Lf %.20Lf\n", p1.x, p1.y);
        if (intersect(l, c, p1, p2)) check(p1), check(p2);
    }
    for (const auto &c1 : cv) for (const auto &c2 : cv) {
        point p1, p2;
        if (intersect(c1, c2, p1, p2)) check(p1), check(p2);
    }
    // printf("%.20Lf (%.20Lf %.20Lf)\n", ans, ansp.x, ansp.y);
    if (ans > 1e50)
        puts("impossible");
    else
        printf("%.20Lf %.20Lf\n", ansp.x, ansp.y);
    return 0;
}
