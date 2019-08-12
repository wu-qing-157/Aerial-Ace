#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <utility>

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
point a[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i <= n; i++)
        scanf("%lld%lld", &a[i].x, &a[i].y);

    point x1 = a[n] - a[n - 1], xx2 = a[0] - a[1], x2 = point(-xx2.x, xx2.y);
    if (det(x1, x2) != 0) {
        puts("No");
        return 0;
    }

    if ((a[n - 1].x - a[0].x) * (a[n].y - a[n - 1].y) != (a[n].x - a[n - 1].x) * (a[n - 1].y + a[0].y)) {
        puts("No");
        return 0;
    }

    puts("Yes");
    return 0;
}
