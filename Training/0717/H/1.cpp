#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

template<typename T>
struct point {
    T x, y;
    point() {}
    point(T x, T y) : x(x), y(y) {}
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, T &b) {
        return point(a.x * b, a.y * b);
    }
    friend T det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend T dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }

};

template<typename T>
struct line {
    point<T> a, b;
    line() {}
    line(point<T> a, point<T> b) : a(a), b(b) {}
    point<T> v() const {
        return b - a;
    }
};

std::vector<line<int64_t>> sa, a, b;
point<int64_t> cur;

void pure_line(line<int64_t> &l) {
    if (l.a.y > l.b.y) {
        std::swap(l.a, l.b);
    } else if (l.a.y == l.b.y) {
        if (l.a.x > l.b.x) std::swap(l.a, l.b);
    }
}

bool cmp(const line<int64_t> &a, const line<int64_t> &b) {
    int64_t de = det(a.v(), b.v());
    if (de != 0) return de > 0;
    de = det(a.v(), b.b - a.a);
    if (de != 0) return de > 0;
    if (a.a.y == a.b.y) return a.a.x < b.a.x;
    else return a.a.y < b.a.y;
}

bool cmp2(const point<int64_t> &a, const point<int64_t> &b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

bool merge(line<int64_t> &a, const line<int64_t> &b) {
    if (det(a.v(), b.v()) != 0) return false;
    if ((a.a.y == a.b.y && a.b.x >= b.a.x) || a.b.y >= b.a.y) {
        a = line<int64_t>(std::min(a.a, b.a, cmp2), std::max(a.b, b.b, cmp2));
        return true;
    }
    return false;
}

void process(std::vector<line<int64_t>> &ret) {
    ret.clear();
    point<int64_t> cur = point<int64_t>(0, 0);
    while (true) {
        static char op;
        static int64_t dx, dy;
        scanf(" %c", &op);
        if (op == 'Q') exit(0);
        if (op == 'E') break;
        scanf("%lld%lld", &dx, &dy);
        if (op == 'L') {
            sa.emplace_back(cur, cur + point<int64_t>(dx, dy));
            pure_line(sa.back());
        }
        cur = cur + point<int64_t>(dx, dy);
    }
    std::sort(sa.begin(), sa.end(), cmp);
    for (int i = 0; i < (int) sa.size(); i++) {
        line<int64_t> cur = sa[i];
        while (i + 1 < (int) sa.size() && merge(cur, sa[i + 1])) continue;
        ret.push_back(cur);
    }
}

point<int64_t> trans(const point<int64_t> a, double rotate, double scale) {
    double len = a.len() * scale;
    double angle = a.angle() + rotate();
    return std::point<int64_t>(len * std::cos(angle) + 0.5, len * std::sin(angle) + 0.5);
}

bool judge(const std::point<int64_t> delta, double rotate, double scale) {
    set.clear();
    for (auto i : b) set.insert(i);
    for (auto i : a) {
        line<int64_t> l = line<int64_t>(trans(i.a, rotate, scale), trans(i.b, rotate, scale));
        pure_line(l);
        if (!set.count(l))
            return false;
    return true;
}

int main() {
    while (true) {
        process(a);
        process(b);
        if (a.size() != b.size()) {
            puts("NO");
            continue;
        }
        bool flag = true;
        for (auto i : b) {
            if (judge(i.a - a[0].a, i.angle() - a[0].angle(), i.len() / a[0].len()) ||
                    judge(i.b - a[0].a, -i.angle() - a[0].angle(), i.len() / a[0].len())) {
                puts("YES");
                flag = false;
                break;
            }
        }
        if (flag) puts("NO");
    }
}
