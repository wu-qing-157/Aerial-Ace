#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <vector>

struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    int64_t len2() const {
        return 1ll * x * x + 1ll * y * y;
    }
    friend bool operator<(const point &a, const point &b) {
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }
};

std::unordered_map<int, int> map;

int a, b, c;
std::vector<point> va, vb;
std::vector<std::pair<point, point>> ans;

int main() {
    for (int i = 0; i * i <= 1e9 + 10; i++) map[i * i] = i;
    static int T;
    scanf("%d", &T);
    while (T--) {
        va.clear(), vb.clear(), ans.clear();
        scanf("%d%d%d", &a, &b, &c);
        for (int x = 0; x * x <= a; x++) {
            auto it = map.find(a - x * x);
            if (it != map.end()) {
                int y = it->second;
                va.emplace_back(x, y);
                va.emplace_back(-x, y);
                va.emplace_back(x, -y);
                va.emplace_back(-x, -y);
            }
        }
        for (int x = 0; x * x <= b; x++) {
            auto it = map.find(b - x * x);
            if (it != map.end()) {
                int y = it->second;
                vb.emplace_back(x, y);
                vb.emplace_back(-x, y);
                vb.emplace_back(x, -y);
                vb.emplace_back(-x, -y);
            }
        }
        for (auto p1 : va) for (auto p2 : vb)
            if ((p1 - p2).len2() == c)
                ans.emplace_back(p1, p2);
        std::sort(ans.begin(), ans.end());
        printf("%d\n", int(ans.size()));
        for (auto p : ans)
            printf("%d %d %d %d\n", p.first.x, p.first.y, p.second.x, p.second.y);
    }
    return 0;
}
