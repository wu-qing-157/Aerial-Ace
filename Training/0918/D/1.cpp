#include <cassert>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <string>

const unsigned mul = 20190812;

class Magic {
    public:
        Magic(unsigned state): state(state), ans(0) {}
        unsigned long long retrieve() {
            unsigned modulo = 0x7fffffff;
            state = ((unsigned long long) state * mul + ans) % modulo;
            unsigned high = state;
            state = ((unsigned long long) state * mul + ans) % modulo;
            return high * modulo + state;
        }
        int retrieve(int a, int b) {
            assert (a <= b);
            return (int) (retrieve() % (b - a + 1)) + a;
        }
        void submit(unsigned k) {
            ans = ans * mul + k;
        }
        unsigned retrieveAns() {
            return ans;
        }

    private:
        unsigned state, ans;
};

struct point {
    int64_t x, y;
    point() : x(0), y(0) {}
    point(int64_t x, int64_t y) : x(x), y(y) {}
    friend point operator-(const point &a, const point &b) {
        return point(a.x - b.x, a.y - b.y);
    }
    friend int64_t det(const point &a, const point &b) {
        return a.x * b.y - a.y * b.x;
    }
    friend int64_t dot(const point &a, const point &b) {
        return a.x * b.x + a.y * b.y;
    }
};

const int N = 1e5 + 10;

class DataStructure {
    point a[N];
    std::vector<std::pair<point, int>> v;
    int cid, __size;
    bool del[N];
    void convex(std::vector<std::pair<point, int>> &p) {
        if (p.size() <= 1) {
            v = p;
            return;
        }
        static std::vector<std::pair<point, int>> up;
        v.clear(), up.clear();
        std::sort(p.begin(), p.end(), [](const std::pair<point, int> &a, const std::pair<point, int> &b) {
            if (a.first.x != b.first.x) return a.first.x < b.first.x;
            if (a.first.y != b.first.y) return a.first.y < b.first.y;
            return a.second < b.second;
        });
        for (auto cur : p) {
            while (up.size() >= 2 && det(up.back().first - up[up.size() - 2].first, cur.first - up.back().first) <= 0)
                up.pop_back();
            up.push_back(cur);
        }
        for (auto cur : up) v.push_back(cur);
        v.pop_back();
        up.clear();
        std::reverse(p.begin(), p.end());
        for (auto cur : p) {
            while (up.size() >= 2 && det(up.back().first - up[up.size() - 2].first, cur.first - up.back().first) <= 0)
                up.pop_back();
            up.push_back(cur);
        }
        for (auto cur : up) v.push_back(cur);
        v.pop_back();
        //printf("convex "); for (auto p : v) printf("(%d:%d,%d)", p.second, p.first.x, p.first.y); puts("");
    }
    int sum[N << 2];
    void add(int id, int ll, int rr, int x, int delta) {
        sum[id] += delta;
        if (ll == rr) return;
        int mm = (ll + rr) >> 1;
        if (x <= mm) add(id << 1, ll, mm, x, delta);
        else add((id << 1) | 1, mm + 1, rr, x, delta);
    }
    int query(int id, int ll, int rr, int r) {
        int mm = (ll + rr) >> 1;
        if (r == rr) return sum[id];
        if (r <= mm) return query(id << 1, ll, mm, r);
        return sum[id << 1] + query((id << 1) | 1, mm + 1, rr, r);
    }
    int anti(int id, int ll, int rr, int r) {
        int mm = (ll + rr) >> 1;
        if (ll == rr) return ll;
        if (r <= sum[id << 1]) return anti(id << 1, ll, mm, r);
        return anti((id << 1) | 1, mm + 1, rr, r - sum[id << 1]);
    }
    int id(int r) {
        return query(1, 1, N, r);
    }
    public:
        DataStructure() : v(), cid(0), __size(0) {
            memset(sum, 0, sizeof sum);
            memset(del, 0, sizeof del);
        }
        void add(int x, int y) {
            ++__size;
            a[++cid] = point(x, y);
            std::vector<std::pair<point, int>> all(v);
            all.emplace_back(a[cid], cid);
            convex(all);
            add(1, 1, N, cid, 1);
        }
        void erase(int r) {
            --__size;
            bool flag = false;
            std::vector<std::pair<point, int>> all;
            int tar = anti(1, 1, N, r);
            del[tar] = true;
            //printf("erase %d\n", tar);
            add(1, 1, N, tar, -1);
            for (auto p : v) {
                if (p.second == tar)
                    flag = true;
            }
            if (flag) {
                for (int i = 1; i <= cid; i++)
                    if (!del[i])
                        all.emplace_back(a[i], i);
                convex(all);
            }
        }
        int size() {
            return __size;
        }
        std::pair<int, int> query() {
            int64_t ans = INT64_MAX;
            std::pair<int, int> ret;
            for (auto i : v) for (auto j : v) {
                int64_t cur = dot(i.first, j.first);
                if (cur < ans) ans = cur, ret = std::make_pair(i.second, j.second);
                else if (cur == ans) ret = std::min(ret, std::make_pair(i.second, j.second));
            }
            //printf("query %lld %lld %lld\n", ans, ret.first, ret.second);
            if (ans == INT64_MAX) return std::make_pair(0, 0);
            return ret;
        }
};

int main() {
    const int lim = 1E9;
    int q; std::cin >> q;
    for (int k = 0; k < q; ++k) {
        unsigned state;
        std::cin >> state;
        std::string s;
        std::cin >> s;
        DataStructure ds;
        Magic magic(state);
        for (char c: s) {
            if (c == 'a') {
                int x = magic.retrieve(-lim, lim);
                int y = magic.retrieve(-lim, lim);
                ds.add(x, y);
            } else if (c == 'e') {
                unsigned pos = magic.retrieve(1, ds.size());
                ds.erase(pos);
            } else if (c == 'q') {
                auto best = ds.query();
                magic.submit(best.first);
                magic.submit(best.second);
            }
            //puts("------");
        }
        std::cout << magic.retrieveAns() << std::endl;
    }
    return 0;
}
