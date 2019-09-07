#include <cstdio>
#include <unordered_set>
#include <unordered_map>

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
    point sym(const point &a) const {
        return point(x * 2 - a.x, y * 2 - a.y);
    }
    friend point mid(const point &a, const point &b) {
        return point((a.x + b.x) / 2, (a.y + b.y) / 2);
    }
    friend bool operator==(const point &a, const point &b) {
        return a.x == b.x && a.y == b.y;
    }
};

struct hash_point {
    size_t operator()(const point &a) const {
        return a.x ^ (a.y << 16) ^ (a.y >> 16);
    }
};

const int N = 1e3 + 10;
int n, ans;
point a[N];
std::unordered_set<point, hash_point> set;
std::unordered_map<point, int, hash_point> map;

int main() {
    scanf("%d", &n);
    ans = n;
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &a[i].x, &a[i].y), a[i].x *= 2, a[i].y *= 2;
    for (int i = 1; i <= n; i++)
        set.insert(a[i]);
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (!set.count(a[i].sym(a[j])))
                cnt++;
        ans = std::min(ans, cnt);
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            map[mid(a[i], a[j])]++;
    for (auto p : map)
        ans = std::min(ans, n - p.second * 2);
    printf("%d\n", ans);
    return 0;
}
