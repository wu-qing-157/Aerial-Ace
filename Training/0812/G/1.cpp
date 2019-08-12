#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <utility>

using number = long double;
#define double number
const double eps = 1e-10;
int sgn(double x) {
    return (x > eps) - (x < -eps);
}

struct point {
    int64_t x, y;
    point() {}
    point(int64_t x, int64_t y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

const int N = 1e5 + 10;
int n;
double ans;
point a[N];
std::vector<std::pair<int, double>> vec;

double xie(const point &a) {
    return double(a.y) / a.x;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        scanf("%lld%lld", &a[i].x, &a[i].y);

    point x1 = a[n] - a[n - 1], xx2 = a[0] - a[1], x2 = point(-xx2.x, xx2.y);
    if (det(x1, x2) != 0) {
        puts("No");
        return 0;
    }

    for (int i = 1; i < n; i++)
        vec.emplace_back(a[i].x, (xie(a[i + 1] - a[i]) - xie(a[i] - a[i - 1])) / 2);

    for (auto p : vec)
        ans += p.second * (p.first - a[0].x);
    if (sgn(ans - a[0].y) != 0) {
        puts("No");
        return 0;
    }

    puts("Yes");
    return 0;
}
