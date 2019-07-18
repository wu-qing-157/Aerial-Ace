#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

const double eps = 1e-9, INF = 1e12;

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

int cmp(double x, double y) {
    return sgn(x - y);
}

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend double det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
};

std::vector<point> a, b, ans, ret;
std::vector<std::pair<point, point>> va, vb;

void process_input(std::vector<point> &a, std::vector<std::pair<point, point>> &va) {
    static int l;
    scanf("%d", &l);
    if (l == 1) {
        static double y;
        scanf("%lf", &y);
        a.emplace_back(-INF, y);
        a.emplace_back(INF, y);
        va.emplace_back(point(-INF, y), point(INF, y));
    } else {
        for (int i = 1; i < l; i++) {
            static double x, y;
            scanf("%lf%lf", &x, &y);
            if (i == 1) a.emplace_back(-INF, y);
            va.emplace_back(a.back(), point(x, y));
            a.emplace_back(x, y);
            if (i == l - 1) {
                va.emplace_back(a.back(), point(INF, y));
                a.emplace_back(INF, y);
            }
        }
    }
}

int main() {
    freopen("superposition.in", "r", stdin);
    freopen("superposition.out", "w", stdout);
    process_input(a, va);
    process_input(b, vb);
    for (auto i : a) for (auto j : vb)
        if (cmp(j.first.x, i.y) <= 0 && cmp(i.y, j.second.x) <= 0)
            ans.emplace_back(i.x, (j.first.y * (j.second.x - i.y) + j.second.y * (i.y - j.first.x)) / (j.second.x - j.first.x));
    for (auto i : b) for (auto tj : va) if (cmp(tj.first.y, tj.second.y) != 0) {
        auto j = std::minmax(tj.first, tj.second, [](auto a, auto b) { return a.y < b.y; });
        if (cmp(j.first.y, i.x) <= 0 && cmp(i.x, j.second.y) <= 0)
            ans.emplace_back((j.first.x * (j.second.y - i.x) + j.second.x * (i.x - j.first.y)) / (j.second.y - j.first.y), i.y);
    }
    std::sort(ans.begin(), ans.end(), [](auto a, auto b) { return cmp(a.x, b.x) == 0 ? a.y < b.y : a.x < b.x; });
    ans.erase(std::unique(ans.begin(), ans.end(), [](auto a, auto b) { return cmp(a.x, b.x) == 0 && cmp(a.y, b.y) == 0; }), ans.end());
    for (auto it = ans.begin() + 1; it != ans.end() - 1; it++)
        if (sgn(det(*(it + 1) - *it, *it - *(it - 1))) != 0)
            ret.push_back(*it);
    printf("%d\n", (int) ret.size() + 1);
    if (ret.empty()) printf("%.10f\n", ans.back().y);
    else for (auto i : ret) printf("%.10f %.10f\n", i.x, i.y);
    return 0;
}
