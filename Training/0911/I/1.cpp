#include <cstdio>
#include <vector>
#include <unordered_map>

struct point {
    int x, y;
    point() {}
    point(int x, int y) : x(x), y(y) {}
    friend bool operator==(const point &a, const point &b) {
        return a.x == b.x && a.y == b.y;
    }
};

struct vert {
    int x, y1, y2;
    vert() {}
    vert(int x, int y1, int y2) : x(x), y1(y1), y2(y2) {}
};

struct hori {
    int y, x1, x2;
    hori() {}
    hori(int y, int x1, int x2) : y(y), x1(x1), x2(x2) {}
};

int lcnt;
bool nc;
point a1, b1, a2, b2;
std::vector<point> p;
std::vector<vert> v;
std::vector<hori> h;
std::unordered_map<int, int> cnt1, cnt2;

void insert(const point &a) {
    for (auto p1 : p)
        if (a == p1)
            return;
    p.push_back(a);
}

void check(const vert &v, const hori &h) {
    if (v.x >= h.x1 && v.x <= h.x2 && h.y >= v.y1 && h.y <= v.y2)
        nc = false, insert(point(v.x, h.y));
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        p.clear(), v.clear(), h.clear(), lcnt = 0, nc = true;
        cnt1.clear(), cnt2.clear();
        scanf("%d%d", &a1.x, &a1.y);
        scanf("%d%d", &b1.x, &b1.y);
        scanf("%d%d", &a2.x, &a2.y);
        scanf("%d%d", &b2.x, &b2.y);
        insert(a1), insert(b1), insert(point(a1.x, b1.y)), insert(point(b1.x, a1.y));
        insert(a2), insert(b2), insert(point(a2.x, b2.y)), insert(point(b2.x, a2.y));
        v.emplace_back(a1.x, a1.y, b1.y), v.emplace_back(b1.x, a1.y, b1.y);
        v.emplace_back(a2.x, a2.y, b2.y), v.emplace_back(b2.x, a2.y, b2.y);
        h.emplace_back(a1.y, a1.x, b1.x), h.emplace_back(b1.y, a1.x, b1.x);
        h.emplace_back(a2.y, a2.x, b2.x), h.emplace_back(b2.y, a2.x, b2.x);
        for (int i : {0, 1})
            for (int j : {2, 3})
                check(v[i], h[j]), check(v[j], h[i]);
        for (auto pp : p)
            cnt1[pp.x]++, cnt2[pp.y]++;
        for (auto pp : p)
            printf("(%d,%d)", pp.x, pp.y);
        for (auto pp : cnt1)
            lcnt += pp.second - 1;
        for (auto pp : cnt2)
            lcnt += pp.second - 1;
        if (nc)
            puts("3");
        else
            printf("%d\n", 2 + lcnt - int(p.size()));
    }
    return 0;
}
