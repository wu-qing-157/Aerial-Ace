#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int64_t INF = 1e9;

int sgn(int64_t x) {
    return (x > 0) - (x < 0);
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
    friend bool operator==(const point &a, const point &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend bool operator!=(const point &a, const point &b) {
        return a.x != b.x || a.y != b.y;
    }
};

struct line {
    point a, b;
    line(const point &a, const point &b) : a(a), b(b) {}
};

std::vector<point> bl, wh;
std::vector<point> up, down;

bool intersect(const line &a, const line &b) {
    return sgn(det(b.a - a.a, a.b - a.a)) * sgn(det(b.b - a.a, a.b - a.a)) <= 0
        && sgn(det(a.a - b.a, b.b - b.a)) * sgn(det(a.b - b.a, b.b - b.a)) <= 0;
}

void convex(std::vector<point> &a) {
    up.clear();
    down.clear();
    std::sort(a.begin(), a.end(), [](const point &a, const point &b) {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
    });
    a.erase(std::unique(a.begin(), a.end()), a.end());
    for (auto p : a) {
        while (up.size() >= 2 && det(p - up[up.size() - 2], up.back() - up[up.size() - 2]) > 0)
            up.pop_back();
        up.push_back(p);
    }
    std::reverse(a.begin(), a.end());
    for (auto p : a) {
        while (down.size() >= 2 && det(p - down[down.size() - 2], down.back() - down[down.size() - 2]) > 0)
            down.pop_back();
        down.push_back(p);
    }
    a.clear();
    up.pop_back();
    down.pop_back();
    for (auto p : up) a.push_back(p);
    for (auto p : down) a.push_back(p);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        bl.clear();
        wh.clear();

        {
            static int n, tx, ty, co;
            scanf("%d", &n);
            for (int i = 1; i <= n; i++) {
                scanf("%d%d%d", &tx, &ty, &co);
                (co > 0 ? bl : wh).emplace_back(tx, ty);
            }
        }

        if (bl.empty() || wh.empty()) {
            puts("Successful!");
            continue;
        }

        convex(bl);
        convex(wh);

        bool flag = true;
        if (wh.size() == 1) bl.swap(wh);

        if (wh.size() == 1) {
            if (bl.front() != wh.front())
                puts("Successful!");
            else
                puts("Infinite loop!");
            continue;
        }

        if (bl.size() != 1 && wh.size() != 1) {
            bl.push_back(bl.front());
            wh.push_back(wh.front());
            for (int i = 1; i < (int) bl.size() && flag; i++)
                for (int j = 1; j < (int) wh.size() && flag; j++)
                    if (intersect(line(bl[i - 1], bl[i]), line(wh[j - 1], wh[j])))
                        flag = false;
        }

        if (flag) {
            bool left = false, right = false;
            for (int j = 1; j < (int) wh.size() && !left; j++) {
                if (intersect(line(bl.front(), point(-INF, bl.front().y)), line(wh[j - 1], wh[j])))
                    left = true;
                if (intersect(line(bl.front(), point(INF, bl.front().y)), line(wh[j - 1], wh[j])))
                    right = true;
            }
            if (left && right) flag = false;
        }

        if (flag)
            puts("Successful!");
        else
            puts("Infinite loop!");
    }
    return 0;
}
