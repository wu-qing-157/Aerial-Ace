#include <cstdio>
#include <utility>

const double eps = 1e-8;

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, double b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator/(const point &a, double b) {
        return point(a.x / b, a.y / b);
    }
    friend double dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }

    point rotate90() const {
        return point(-y, x);
    }
    double len2() const {
        return x * x + y * y;
    }
};

struct line {
    point a, b;
    line() {}
    line(const point &a, const point &b) : a(a), b(b) {}
};

const int N = 3e3 + 10;
int n;
point p[N], p1, p2;
std::pair<int, point> checker[2];

point projection(const point &p, const line &l) {
    return l.a + (l.b - l.a) * dot(p - l.a, l.b - l.a) / (l.b - l.a).len2();
}

point sym(const point &p, const line &l) {
    return projection(p, l) * 2 - p;
}

bool intersect(const line &a, const line &b) {
    return sgn(det(b.a - a.a, b.b - a.a)) * sgn(det(b.a - a.b, b.b - a.b)) <= 0
        || sgn(det(a.a - b.a, a.b - b.a)) * sgn(det(a.a - b.b, a.b - b.b)) <= 0;
}

bool checkdiff(int delta) {
    delta %= n;
    if (delta < 0) delta += n;
    return delta != 0 && delta != 1 && delta != n - 1;
}

bool check(int k, point tobe) {
    for (int i = 0; i < n; i++) {
        if (checkdiff(k - i) && intersect(line(p[i], p[i + 1]), line(tobe, p[k + 1])))
            return false;
        if (checkdiff(k - 1 - i) && intersect(line(p[i], p[i + 1]), line(p[k - 1], tobe)))
            return false;
    }
    return true;
}

bool checkp(int k) {
    int cnt = 0;
    p1 = (p[k - 1] + p[k + 1]) / 2;
    p2 = p[k + 1];
    line l = line(p1, p1 + (p2 - p1).rotate90());
    for (int i = k, j = k; j - i <= n; i--, j++)
        if (sgn(det(p2 - p1, p[j] - p[i])) != 0 || sgn(dot((p[i] + p[j]) / 2 - p1, p2 - p1)) != 0) {
            if (cnt == 1) return false;
            checker[0] = std::make_pair(i, sym(p[j], l));
            checker[1] = std::make_pair(j, sym(p[i], l));
            cnt++;
        }
    if (cnt == 0) return true;
    for (int i : {0, 1})
        if (printf("%d (%.f %.f)\n", checker[i].first, checker[i].second.x, checker[i].second.y), check(checker[i].first, checker[i].second))
            return true;
    return false;
}

bool checkl(int k) {
    int cnt = 0;
    p1 = (p[k] + p[k + 1]) / 2;
    p2 = p[k + 1];
    line l = line(p1, p1 + (p2 - p1).rotate90());
    printf("(%f %f) (%f %f)\n", l.a.x, l.a.y, l.b.x, l.b.y);
    for (int i = k, j = k + 1; j - i <= n; i--, j++)
        if (sgn(det(p2 - p1, p[j] - p[i])) != 0 || sgn(dot((p[i] + p[j]) / 2 - p1, p2 - p1)) != 0) {
            printf("%d %d %d\n", k, i, j);
            if (cnt == 1) return false;
            checker[0] = std::make_pair(i, sym(p[j], l));
            checker[1] = std::make_pair(j, sym(p[i], l));
            cnt++;
        }
    if (cnt == 0) return true;
    for (int i : {0, 1})
        if (printf("%d (%.f %.f)\n", checker[i].first, checker[i].second.x, checker[i].second.y), check(checker[i].first, checker[i].second))
            return true;
    return false;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);

        if (n <= 4) {
            puts("Y");
            continue;
        }

        for (int i = 0; i < n; i++) p[i + 2 * n] = p[i + n] = p[i] = p[i] * 2;

        bool ok = false;
        for (int i = n; i < (n << 1) && !ok; i++)
            if (checkp(i) || checkl(i))
                ok = true;

        puts(ok ? "Y" : "N");
    }
    return 0;
}
