#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

struct data {
    int64_t u, v;
    int id;
    data(int64_t u, int64_t v, int id) : u(u), v(v), id(id) {}
    friend bool operator<(const data &a, const data &b) {
        return a.u * b.v > a.v * b.u;
    }
};
struct return_t {
    int64_t sum, left;
    int id;
    return_t(int64_t left, int id) : sum(0), left(left), id(id) {}
    return_t &operator+=(int64_t v) {
        sum += v;
        return *this;
    }
};

const int N = 3e5 + 10;
int n, id[N];
int64_t a[N][2], sum[2], x[2][N], y[2][N];
std::vector<data> d;

int64_t llgcd(int64_t a, int64_t b) {
    return b == 0 ? a : llgcd(b, a % b);
}

void output(int64_t base, int64_t up, int64_t down) {
    if (up == 0) down = 1;
    int64_t gcd = llgcd(up, down);
    up /= gcd, down /= gcd;
    printf("%lld/%lld\n", base * down - up, down);
}

struct seg {
    int64_t sum[N << 2][2];
#define lc id << 1
#define rc (id << 1) | 1
#define m ((l + r) >> 1)
    void build(int id, int l, int r) {
        sum[id][0] = sum[id][1] = 0;
        if (l == r) return;
        build(lc, l, m);
        build(rc, m + 1, r);
    }
    void add(int id, int l, int r, int tar, int64_t v0, int64_t v1) {
        sum[id][0] += v0;
        sum[id][1] += v1;
        if (l == r) return;
        if (tar <= m) add(lc, l, m, tar, v0, v1);
        else add(rc, m + 1, r, tar, v0, v1);
    }
    return_t ceil(int id, int l, int r, int64_t tar) {
        if (l == r) return return_t(tar, l);
        if (tar < sum[lc][0]) return ceil(lc, l, m, tar);
        else return ceil(rc, m + 1, r, tar - sum[lc][0]) += sum[lc][1];
    }
} s[2];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%lld%lld", a[i], a[i] + 1);
        s[0].build(1, 1, n);
        s[1].build(1, 1, n);
        sum[0] = sum[1] = 0;

        d.clear();
        for (int i = 0; i < n; i++) if (a[i][0] <= a[i][1]) d.emplace_back(a[i][0], a[i][1], i);
        std::sort(d.begin(), d.end());
        for (int i = 0; i < (int) d.size(); i++) id[d[i].id] = i + 1;
        d.clear();
        for (int i = 0; i < n; i++) if (a[i][0] > a[i][1]) d.emplace_back(a[i][1], a[i][0], i);
        std::sort(d.begin(), d.end());
        for (int i = 0; i < (int) d.size(); i++) id[d[i].id] = i + 1;

        for (int i = 0; i < n; i++) {
            if (a[i][0] <= a[i][1]) {
                sum[0] += a[i][0];
                s[0].add(1, 1, n, id[i], a[i][0] + a[i][1], a[i][0]);
                x[0][id[i]] = a[i][0] + a[i][1];
                y[0][id[i]] = a[i][0];
            } else {
                sum[1] += a[i][1];
                s[1].add(1, 1, n, id[i], a[i][0] + a[i][1], a[i][1]);
                x[1][id[i]] = a[i][0] + a[i][1];
                y[1][id[i]] = a[i][1];
            }
            if (sum[0] > sum[1]) {
                auto p = s[0].ceil(1, 1, n, sum[0] - sum[1]);
                output(sum[0] - p.sum, p.left * y[0][p.id], x[0][p.id]);
            } else {
                auto p = s[1].ceil(1, 1, n, sum[1] - sum[0]);
                output(sum[1] - p.sum, p.left * y[1][p.id], x[1][p.id]);
            }
        }
    }
    return 0;
}
