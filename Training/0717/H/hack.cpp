#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>
#include <vector>

const double eps = 1e-7, pi = std::acos(-1);

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

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
    T len2() const {
        return x * x + y * y;
    }
    double angle() const {
        return std::atan2(y, x);
    }
    friend bool operator==(const point &a, const point &b) {
        return a.x == b.x && a.y == b.y;
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
    friend bool operator==(const line &a, const line &b) {
        return a.a == b.a && a.b == b.b;
    }
};

struct line_hash {
    size_t operator()(const line<int64_t> &a) const {
        return a.a.x ^ (a.b.x << 18) ^ (a.b.x >> 14) ^
            (a.a.y << 6) ^ (a.a.y >> 26) ^
            (a.b.y << 16) ^ (a.b.y >> 16);
    }
};

std::vector<line<int64_t>> sa, a, b;
point<int64_t> cur;
std::unordered_set<line<int64_t>, line_hash> set;

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
    if (det(a.v(), b.b - a.a)) return false;
    if ((a.a.y == a.b.y && a.b.x >= b.a.x) || a.b.y >= b.a.y) {
        a = line<int64_t>(std::min(a.a, b.a, cmp2), std::max(a.b, b.b, cmp2));
        return true;
    }
    return false;
}

void process(std::vector<line<int64_t>> &ret) {
    sa.clear();
    ret.clear();
    point<int64_t> cur = point<int64_t>(0, 0);
    while (true) {
        static char str[10], &op = str[0];
        static int64_t dx, dy;
        scanf("%s", str);
        if (op == 'Q') exit(0);
        if (op == 'E') break;
        scanf("%lld%lld", &dx, &dy);
        if (op == 'L') {
            sa.emplace_back(cur, cur + point<int64_t>(dx, dy));
            pure_line(sa.back());
        }
        cur = cur + point<int64_t>(dx, dy);
    }
    //puts("READ");
    //for (auto i : sa) printf("(%ld, %ld) -> (%ld, %ld)\n", i.a.x, i.a.y, i.b.x, i.b.y);
    std::sort(sa.begin(), sa.end(), cmp);
    //puts("SORTED");
    //for (auto i : sa) printf("(%ld, %ld) -> (%ld, %ld)\n", i.a.x, i.a.y, i.b.x, i.b.y);
    for (int i = 0; i < (int) sa.size(); i++) {
        line<int64_t> cur = sa[i];
        while (i + 1 < (int) sa.size() && merge(cur, sa[i + 1])) i++;
        ret.push_back(cur);
    }
}

bool trans(const point<int64_t> a, double rotate, double scale2, point<int64_t> &ret) {
    double len2 = a.len2() * scale2;
    double angle = a.angle() + rotate;
    double x = std::sqrt(len2) * std::cos(angle);
    double y = std::sqrt(len2) * std::sin(angle);
    ret.x = std::llround(x);
    ret.y = std::llround(y);
    //printf("%f %f (%ld, %ld) --> (%f, %f)(%ld, %ld)\n", rotate, scale, a.x, a.y, x, y, ret.x, ret.y);
    return sgn(ret.x - x) == 0 && sgn(ret.y - y) == 0;
}

bool judge(const point<int64_t> delta, double rotate, double scale2) {
    //printf("case (%ld, %ld) %ld %ld\n", delta.x, delta.y, rotate, scale);
    set.clear();
    for (auto i : b) set.insert(i);
    for (auto i : a) {
        line<int64_t> l;
        if (!trans(i.a, rotate, scale2, l.a) ||
                !trans(i.b, rotate, scale2, l.b))
            return false;
        l.a = l.a + delta;
        l.b = l.b + delta;
        pure_line(l);
        //printf("(%ld, %ld) -> (%ld %ld)\n", l.a.x, l.a.y, l.b.x, l.b.y);
        if (!set.count(l))
            return false;
    }
    return true;
}

int main() {
    for (int cas = 1; true; cas++) {
        process(a);
        process(b);
        if (cas == 187) {
            printf("%lld %lld\n", (int64_t) a.size(), (int64_t) b.size());
        }
        if (a.size() != b.size()) continue;
        if (a.size() == 0) continue;
        bool flag = true;
        for (auto i : b) {
            //printf("try (%lld, %lld) -> (%lld, %lld)\n", i.a.x, i.a.y, i.b.x, i.b.y);
            if (judge(i.a - a[0].a, i.v().angle() - a[0].v().angle(),
                        ((double) i.v().len2()) / a[0].v().len2()) ||
                    judge(i.b - a[0].a, i.v().angle() - a[0].v().angle() + pi,
                        ((double) i.v().len2()) / a[0].v().len2())) {
                if (cas <= 3) puts("YES");
                flag = false;
                break;
            }
        }
        if (cas <= 3 && flag) puts("NO");
    }
}
