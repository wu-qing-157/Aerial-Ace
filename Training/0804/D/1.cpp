#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <deque>

struct point {
    double x, y;
    point(double x, double y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, double b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator/(const point &a, double b) {
        return point(a.x / b, a.y / b);
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

struct line {
    point a, b;
    line(const point &a, const point &b) : a(a), b(b) {}
};

point intersect(const line &a, const line &b) {
    double s1 = det(a.b - a.a, b.a - a.a);
    double s2 = det(a.b - a.a, b.b - a.a);
    return (b.a * s2 - b.b * s1) / (s2 - s1);
}

bool right(const point &p, const line &l) {
    return det(p - l.a, l.b - l.a) >= 0;
}

const int N = 1e5 + 10;
int n;
int64_t l[N], s[N], v[N];
std::deque<point> deque;

void add(const line &l) {
    point last = deque.front();
    while (deque.size() && right(deque.front(), l)) {
        last = deque.front();
        deque.pop_front();
    }
    if (deque.empty())
        deque.push_front(l.b);
    else
        deque.push_front(intersect(l, line(last, deque.front())));
    deque.push_front(l.a);
    /*
    for (auto p : deque)
        printf("(%.3f %.3f)\n", p.x, p.y);
    puts("");
    */
}

int main() {
    while (scanf("%d", &n) != EOF) {
        n++;
        for (int i = 1; i <= n; i++) scanf("%lld", l + i);
        for (int i = 1; i <= n; i++) scanf("%lld", s + i);
        for (int i = 1; i <= n; i++) scanf("%lld", v + i);
        std::reverse(l + 1, l + n + 1);
        std::reverse(s + 1, s + n + 1);
        std::reverse(v + 1, v + n + 1);
        for (int i = 1; i <= n; i++) l[i] += l[i - 1];
        for (int i = 1; i <= n; i++) s[i] -= l[i - 1];
        deque.clear();
        deque.emplace_back(0, 0);
        for (int i = 1; i <= n; i++)
            add(line(point(0, s[i]), point(double(s[i] + l[n - 1]) / v[i], -l[n - 1])));
        point a = deque.back(), b = deque[deque.size() - 2];
        printf("%.10f\n", deque.back().x);
    }
    return 0;
}
