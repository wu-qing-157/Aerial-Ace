#include <bits/stdc++.h>
using namespace std;

namespace geo {
    using float80 = long double;
    const float80 eps = 1e-10;
    const float80 inf = 1e100;
    struct num {
        long double val;
        num() {}
        num(float80 val) : val(val) {}
        num add(num that) {
            return num(val + that.val);
        }
        num sub(num that) {
            return num(val - that.val);
        }
        num mul(num that) {
            return num(val * that.val);
        }
        num div(num that) {
            return num(val / that.val);
        }
        num sqrt() {
            return num(std::sqrt(max(float80(0), val)));
        }
        num sin() {
            return num(std::sin(val));
        }
        num cos() {
            return num(std::cos(val));
        }
        num pow(num that) {
            return num(std::pow(val, that.val));
        }
        num negtive() {
            return num(-val);
        }
        int sign() {
            return (val > eps) - (val < -eps);
        }
        bool greater_than(num that) {
            return this->sub(that).sign() > 0;
        }
        bool less_than(num that) {
            return this->sub(that).sign() < 0;
        }
        bool not_greater_that(num that) {
            return this->sub(that).sign() >= 0;
        }
        bool not_less_than(num that) {
            return this->sub(that).sign() <= 0;
        }
        bool equal_to(num that) {
            return this->sub(that).sign() == 0;
        }
    };

    struct point {
        num x, y;
        point() {}
        point(num x, num y) : x(x), y(y) {}
        void read() {
            double _x, _y;
            scanf("%lf%lf", &_x, &_y);
            x = num(_x); y = num(_y);
        }
        void print() {
            printf("%.8f %.8f", (double)x.val, (double)y.val);
        }
        point add(point that) {
            return point(x.add(that.x), y.add(that.y));
        }
        point sub(point that) {
            return point(x.sub(that.x), y.sub(that.y));
        }
        point mul(num that) {
            return point(x.mul(that), y.mul(that));
        }
        point div(num that) {
            return point(x.div(that), y.div(that));
        }
        num dot(point that) {
            return x.mul(that.x).add(y.mul(that.y));
        }
        num det(point that) {
            return x.mul(that.y).sub(y.mul(that.x));
        }
        num len2() {
            return x.mul(x).add(y.mul(y));
        }
        num len() {
            return len2().sqrt();
        }
        point unit() {
            return point(x.div(len()), y.div(len()));
        }
        point rotate90() {
            return point(y.negtive(), x);
        }
        bool equal_to(point that) {
            return x.equal_to(that.x) && y.equal_to(that.y);
        }
        bool on_line(struct line l);
        bool on_ray(struct line l);
        bool on_seg(struct line l);
        point symmetry_point(point o) {
            return o.add(o).sub(*this);
        }
    };
    
    
    struct line {
        point a, b;
        line() {}
        line(point a, point b) : a(a), b(b) {}
        point value() {
            return b.sub(a);
        }
        bool intersected_by(line that) {
            return a.sub(that.a).det(that.value()).sign() * b.sub(that.a).det(that.value()).sign() <= 0
                && that.a.sub(a).det(value()).sign() * that.b.sub(a).det(value()).sign() <= 0; 
        }
        point intersect(line that) {
            num s1 = value().det(that.a.sub(a));
            num s2 = value().det(that.b.sub(a));
            return that.a.mul(s2).sub(that.b.mul(s1)).div(s2.sub(s1));
        } 
        point projection(point p) {
            return a.add(value().mul(p.sub(a).dot(value())).div(value().len2()));
        }
        point reflection(point p) {
            return p.symmetry_point(this->projection(p));
        }
    };

    bool point::on_line(struct line l) {
        return sub(l.a).det(sub(l.b)).sign() == 0;
    }
    bool point::on_ray(struct line l) {
        return sub(l.a).det(sub(l.b)).sign() == 0 &&
            sub(l.a).dot(l.value()).sign() >= 0;
    }
    bool point::on_seg(struct line l) {
        return sub(l.a).det(sub(l.b)).sign() == 0 &&
            sub(l.a).dot(l.value()).sign() >= 0 &&
            sub(l.b).dot(l.value()).sign() <= 0;
    }
} using namespace geo;

const int maxn = 5e4 + 10;

point p[maxn], s, t, m;

void work() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i++) p[i].read();
    int q; scanf("%d", &q);
    while (q--) {
        s.read();
        t.read();
        num ans = inf;
        for (int i = 1; i <= n; i++) {
            if (s.sub(p[i]).len().add(t.sub(p[i]).len()).less_than(ans)) {
                ans = s.sub(p[i]).len().add(t.sub(p[i]).len());
                m = p[i];
            }
        }
        for (int i = 1; i <= n; i++) {
            int j = i + 1;
            if (j > n) j = 1;
            point _t = line(p[i], p[j]).reflection(t);
            if (line(s, _t).intersected_by(line(p[i], p[j]))) {
                if (line(s, _t).value().len().less_than(ans)) {
                    ans = line(s, _t).value().len();
                    m = line(s, _t).intersect(line(p[i], p[j]));
                }
            }
        }
        printf("%.8f ", (double)ans.val);
        m.print();
        putchar('\n');
    }
}

int main() {
    freopen("flags.in", "r", stdin);
    int T; scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        printf("Case %d:\n", t);
        work();
    }    
    return 0;
}
/*
1 
5 
0 5 
3 -2 
12 0 
12 10 
3 12 
1 
10 9 11 3


 */