#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10;
const long long INF = ~0ULL >> 1;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)

struct point {
    int64_t x, y, v;
    point() {}
    point(int64_t x, int64_t y) : x(x), y(y) {}

    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    int sgn() const {
        if (y == 0) return x >= 0 ? 1 : -1;
        return y > 0 ? 1 : -1;
    }
};

bool point_cmp(const point &a, const point &b) {
    if (a.sgn() != b.sgn()) return a.sgn() > 0;
    return det(a, b) > 0;
}

std::vector<int64_t> a;
int nn;
int64_t b[N], pre[N], suf[N];
int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        a.clear();
        static int n;
        static point p[N];
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lld%lld%lld", &p[i].v, &p[i].x, &p[i].y);
        std::sort(p, p + n, point_cmp);
        for (int i = 0; i < n; i++) {
            if (a.empty() || !(p[i - 1].sgn() == p[i].sgn() && det(p[i - 1], p[i]) == 0))
                a.push_back(p[i].v);
            else
                a.back() += p[i].v;
        }
        nn = 0;
        for (auto it : a)
        	b[++nn] = it;
        int64_t sum = 0; pre[0] = 0;
        for (int i = 1; i <= nn; ++i)
        {
        	sum += b[i];
        	pre[i] = std::max(pre[i - 1], sum);
        }
        sum = 0; suf[nn + 1] = 0;
        for (int i = nn; i; --i)
        {
        	sum += b[i];
        	suf[i] = std::max(suf[i + 1], sum);
        }
        int64_t ans = 0;
        pre[0] = suf[nn + 1] = 0;
        for (int i = 1; i <= nn + 1; ++i)
        	cmax(ans, pre[i - 1] + suf[i]);
        long long tmp = 0;
        for (int i = 1; i <= nn; ++i)
        {
        	tmp += b[i];
        	tmp < 0 ? tmp = 0 : 0;
        	cmax(ans, tmp);
        }
        printf("%lld\n", ans);
        
        
    }
    return 0;
}
/*
4
2
-100 28335 972
200 16646 1307
3
7265 341 160
-100 17646 24060
2735 26741 7225
4
-8609 7286 1522
9243 30219 184
7255 19082 16933
5317 6845 0

6
1 1 1
-2 2 2
3 3 3
-3 -1 1
2 -2 2
-1 -3 3
*/
