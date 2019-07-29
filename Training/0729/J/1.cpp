#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int N = 2e5 + 10;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
struct info {
    int id, a, b;
    info() {}
    info(int id, int a, int b) : id(id), a(a), b(b) {}
    inline bool operator < (const info &that) const {return a < that.a;}
};

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

std::vector<std::pair<point, int>> a, b;
int n, r1[N], r2[N], cnt, ccc;
std::vector<info> t;
struct Tuple {
	int a, b, c;
	inline bool operator < (const Tuple &that) const {return a < that.a || (a == that.a && (b < that.b || (b == that.b && c < that.c)));}
	Tuple() {}
	Tuple(int _a, int _b, int _c) : a(_a), b(_b), c(_c){}
} ans[N], tr[N];
Tuple query(int x)
{
	par ret = Tuple(0, 0, 0);
	for (; x; x -= x & -x) cmax(ret, tr[x]);
	return ret;
}
void modify(int x, par v)
{
	for (; x <= ccc; x += x & -x) cmax(tr[x], v);
}
std::vector<int> ansv;
void work(std::vector<info> t)
{
	std::sort(t.begin(), t.end());
	for (int i = 0, j = 0; i < t.size(); ++i)
	{
		while (j < t.size() && t[i].a == t[j].a) ++j;
		for (int k = i; k < j; ++k)
			ans[k] = query(t[k].b - 1), ++ans[k].a;
		for (int k = i; k < j; ++k)
			modify(t[k].b, Tuple(ans[k].a, ans[k].id, k));
	}
	Tuple ret = Tuple(0, 0, 0);
	for (int i = 0; i < t.size(); ++i)
	{
		Tuple 
		if (ret < Tuple())
		ret = std::make_pair(ans[i].first, t[i].id);
	}
	for (int i = 1, j = ; i <= ans[i].first; ++i)
	for (int i = 1; i <= ccc; ++i) tr[i] = std::make_pair(0, 0);
}

void solve(const point &p, const point &q, const std::vector<std::pair<point, int>> &a) {
    t.resize(a.size());
    cnt = 0; int c1, c2;
    std::sort(a.begin(), a.end(), [&](const auto &a, const auto &b) { return det(a.first - p, b.first - p) > 0; });
    for (int i = 0; i < (int) a.size(); i++) {
        if (i && det(a[i].first - p, a[i - 1].first - p) == 0) r1[a[i].second] = cnt;
        else r1[a[i].second] = ++cnt;
    } c1 = cnt;
    cnt = 0;
    std::sort(a.begin(), a.end(), [&](const auto &a, const auto &b) { return det(a.first - q, b.first - q) < 0; });
    for (int i = 0; i < (int) a.size(); i++) {
        if (i && det(a[i].first - q, a[i + 1].first - q) == 0) r2[a[i].second] = cnt;
        else r2[a[i].second] = ++cnt;
    } c2 = cnt;
    t.clear();
    for (auto p : a) t.emplace_back(p.second, r1[p.second], r2[p.second]);
    ccc = c2;
    work(t);
}

point p, q;

int main() {
    static int T;
    int Cas = 0;
    scanf("%d", &T);
    while (T--) {
    	ansv.clear();
        scanf("%lld%lld%lld%lld", &p.x, &p.y, &q.x, &q.y);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", &tmp.x, &tmp.y);
            if (det(q - p, tmp - p) > 0) a.emplace_back(tmp, i);
            else b.emplace_back(tmp, i);
        }
        solve(p, q, a);
        solve(q, p, b);
        printf("Case #%d: %d\n", ++Cas, ansv.size());
        for (auto it : ansv)
        	printf("%d\n", it);
    }
    return 0;
}
