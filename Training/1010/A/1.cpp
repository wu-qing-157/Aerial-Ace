#include <cstdio>
#include <algorithm>
#include <unordered_map>

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    point pure() const {
        int gcd = std::__gcd(x, y);
        return point(x / gcd, y / gcd);
    }
    point rotate90() const {
        return point(-y, x);
    }
    point rotate270() const {
        return point(y, -x);
    }
    friend bool operator==(const point &a, const point &b) {
        return a.x == b.x && a.y == b.y;
    }
};

struct hash_point {
    size_t operator()(const point &a) const {
        return (a.x << 16) ^ (a.x >> 16) ^ a.y;
    }
};

const int N = 2e3 + 10;
int n, p;
int64_t ans[N];
point an[N], ap[N];
std::unordered_map<point, int, hash_point> map;

int main() {
    while (scanf("%d%d", &n, &p) != EOF) {
        for (int i = 1; i <= n; i++) scanf("%d%d", &an[i].x, &an[i].y);
        for (int i = 1; i <= p; i++) scanf("%d%d", &ap[i].x, &ap[i].y);
        for (int i = 1; i <= p; i++) ans[i] = 0;
        for (int i = 1; i <= p; i++) {
            map.clear();
            for (int j = 1; j <= n; j++)
                map[(an[j] - ap[i]).pure()]++;
            for (int j = 1; j <= n; j++)
                ans[i] += map[(an[j] - ap[i]).pure().rotate90()];
        }
        for (int i = 1; i <= n; i++) {
            map.clear();
            for (int j = 1; j <= n; j++) if (i != j)
                map[(an[j] - an[i]).pure()]++;
            for (int j = 1; j <= p; j++) {
                ans[j] += map[(ap[j] - an[i]).pure().rotate90()];
                ans[j] += map[(ap[j] - an[i]).pure().rotate270()];
            }
        }
        for (int i = 1; i <= p; i++)
            printf("%lld\n", ans[i]);
    }
    return 0;
}
