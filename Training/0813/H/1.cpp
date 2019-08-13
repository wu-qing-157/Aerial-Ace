#include <cstdio>
#include <cstdint>

int sgn(int64_t x) {
    return (x > 0) - (x < 0);
}

struct point {
    int64_t x, y;
    point() {}
    point(int64_t x, int64_t y) : x(x), y(y) {}
    friend point operator+(const point &a, const point &b) {
        return point(a.x + b.x, a.y + b.y);
    }
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend point operator*(const point &a, int64_t b) {
        return point(a.x * b, a.y * b);
    }
    friend point operator/(const point &a, int64_t b) {
        return point(a.x / b, a.y / b);
    }
    friend int64_t dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

struct line {
    point a, b;
    line() {}
    line(const point &a, const point &b) : a(a), b(b) {}
};

bool intersect(const line &a, const line &b) {
    return sgn(det(b.a - a.a, b.b - a.a)) * sgn(det(b.a - a.b, b.b - a.b)) <= 0
        || sgn(det(a.a - b.a, a.b - b.a)) * sgn(det(a.a - b.b, a.b - b.b)) <= 0;
}

const int N = 3e3 + 10;
int n;
point p[N], p1, p2;

bool checkp(int k) {
    p1 = (p[k - 1] + p[k + 1]) / 2;
    p2 = p[k + 1];
    int cnt = 0;
    bool f1 = true, f2 = true;
    for (int i = k, j = k; j - i <= n; i--, j++) {
        if (det(p2 - p1, p[j] - p[i]) != 0 || dot((p[i] + p[j]) / 2 - p1, p2 - p1) != 0) {
            if (cnt == 1) return false;
            else cnt = 1;
            if (j - i == n - 1) {
                if (dot(p2 - p1, p[i] - p1) >= 0) f1 = false;
                if (dot(p2 - p1, p[j] - p1) <= 0) f2 = false;
                if (det(p[i + 1] - p[i], p2 - p1) == 0) f1 = false;
                if (det(p[j] - p[j - 1], p2 - p1) == 0) f2 = false;
                for (int ii = i + 1; ii < k && f1; ii++)
                    if (intersect(line(p[ii], p[ii + 1]), line(p[i], p[i] + (p2 - p1) * 100000)))
                        f1 = false;
                for (int jj = k; jj + 1 < j && f2; jj++)
                    if (intersect(line(p[jj], p[jj + 1]), line(p[j], p[j] - (p2 - p1) * 100000)))
                        f2 = false;
            }
        }
        if (j - i == 0 || j - i == n) {
            if (dot(p2 - p1, p[i] - p1) < 0) f1 = false;
            if (dot(p2 - p1, p[j] - p1) > 0) f2 = false;
        } else {
            if (dot(p2 - p1, p[i] - p1) >= 0) f1 = false;
            if (dot(p2 - p1, p[j] - p1) <= 0) f2 = false;
        }
    }
    return f1 || f2;
}

bool checkl(int k) {
    p1 = (p[k] + p[k + 1]) / 2;
    p2 = p[k + 1];
    int cnt = 0;
    bool f1 = true, f2 = true;
    for (int i = k, j = k + 1; j - i <= n; i--, j++) {
        if (det(p2 - p1, p[j] - p[i]) != 0 || dot((p[i] + p[j]) / 2 - p1, p2 - p1) != 0) {
            if (cnt == 1) return false;
            else cnt = 1;
            if (j - i == n - 1) {
                if (dot(p2 - p1, p[i] - p1) >= 0) f1 = false;
                if (dot(p2 - p1, p[j] - p1) <= 0) f2 = false;
                if (det(p[i + 1] - p[i], p2 - p1) == 0) f1 = false;
                if (det(p[j] - p[j - 1], p2 - p1) == 0) f2 = false;
                for (int ii = i + 1; ii < k && f1; ii++)
                    if (intersect(line(p[ii], p[ii + 1]), line(p[i], p[i] + (p2 - p1) * 100000)))
                        f1 = false;
                for (int jj = k; jj + 1 < j && f2; jj++)
                    if (intersect(line(p[jj], p[jj + 1]), line(p[j], p[j] - (p2 - p1) * 100000)))
                        f2 = false;
            }
        }
        if (j - i == 0 || j - i == n) {
            if (dot(p2 - p1, p[i] - p1) < 0) f1 = false;
            if (dot(p2 - p1, p[j] - p1) > 0) f2 = false;
        } else {
            if (dot(p2 - p1, p[i] - p1) >= 0) f1 = false;
            if (dot(p2 - p1, p[j] - p1) <= 0) f2 = false;
        }
    }
    return f1 || f2;
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lld%lld", &p[i].x, &p[i].y);

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
