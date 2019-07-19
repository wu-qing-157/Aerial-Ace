#include <cstdio>
#include <cmath>
#include <algorithm>

using number = double;
const number eps = 1e-8;

number _sqrt(number x) {
	return std::sqrt(std::max(x, (number) 0));
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
	friend point operator + (const point &a, const point &b)
	{
		return point(a.x + b.x, a.y + b.y);
	}
	friend point operator - (const point &a, const point &b)
	{
		return point(a.x - b.x, a.y - b.y);
	}
	friend point operator * (const point &a, number b) {
		return point(a.x * b, a.y * b);
	}
	friend point operator / (const point &a, number b) {
		return point(a.x / b, a.y / b);
	}
	friend number dot(const point &a, const point &b) {
		return a.x * b.x + a.y * b.y;
	}
	friend number det(const point &a, const point &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend bool operator == (const point &a, const point &b) {
		return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0;
	}
};

number dis2(const point &a, const point &b) {
	return (a - b).len2();
}
number dis(const point &a, const point &b) {
	return (a - b).len();
}

struct line {
	point a, b;
	line() {}
	line(point a, point b) : a(a), b(b) {}
	point value() const {return b - a;}
};
bool has_intersection(const line &a, const line &b) {
    return sgn(det(a.a - b.a, b.b - b.a)) * sgn(det(a.b - b.a, b.b - b.a)) <= 0
        && sgn(det(b.a - a.a, a.b - a.a)) * sgn(det(b.b - a.a, a.b - a.b)) <= 0;
}
point intersect(const line &a, const line &b) {
	number s1 = det(a.b - a.a, b.a - a.a);
	number s2 = det(a.b - a.a, b.b - a.a);
	return (b.a * s2 - b.b * s1) / (s2 - s1);
}
point projection(const point &p, const line &l) {
	return l.a + (l.b - l.a) * dot(p - l.a, l.b - l.a) / (l.b - l.a).len2();
}
point symmetry_point(const point &a, const point &o) {
	return o + o - a;
}
point reflection(const point &p, const line &l) {
	return symmetry_point(p, projection(p, l));
}

const int N = 1e5 + 10;
int n;
double ans;
point p[N], sym, a, b, pp;
line l[N];

int main() {
    freopen("flags.in", "r", stdin);
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        printf("Case %d:\n", cas);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lf%lf", &p[i].x, &p[i].y);
        p[n + 1] = p[1];
        for (int i = 1; i <= n; i++) l[i] = line(p[i], p[i + 1]);
        static int q;
        scanf("%d", &q);
        while (q--) {
            scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
            ans = 1e50;
            for (int i = 1; i <= n; i++) if (ans > dis(a, p[i]) + dis(p[i], b)) {
                ans = dis(a, p[i]) + dis(p[i], b);
                pp = p[i];
            }
            for (int i = 1; i <= n; i++) {
                sym = reflection(a, l[i]);
                if (has_intersection(line(sym, b), l[i]) && ans > dis(sym, b)) {
                    ans = dis(sym, b);
                    pp = intersect(line(sym, b), l[i]);
                }
            }
            printf("%.7f %.7f %.7f\n", ans, pp.x, pp.y);
        }
    }
}
