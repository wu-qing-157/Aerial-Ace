#include <cassert>
#include <cstdint>
#include <cstdio>
#include <set>

struct data {
    int v, id;
    data() {}
    data(int v, int id) : v(v), id(id) {}
    friend bool operator<(const data &a, const data &b) {
        if (a.v == b.v) return a.id < b.id;
        return a.v < b.v;
    }
};

enum ENUM {c3, c4, c15, c25};
const int N = 1e5 + 10;
int n;
int64_t las;
std::pair<int, int> a[N];
std::pair<int64_t, ENUM> cur;
std::multiset<data> s0, s1, s2, s3, s4, s5;

#define sz0 s0.size()
#define sz1 s1.size()
#define sz2 s2.size()
#define sz3 s3.size()
#define sz4 s4.size()
#define sz5 s5.size()

#define v1 s1.begin()->v
#define v2 s2.begin()->v
#define v3 s3.rbegin()->v
#define v4 s4.rbegin()->v
#define v5 s5.rbegin()->v

#define in0(i) s0.emplace(a[i].first + a[i].second, i)
#define out0(i) s0.erase(s0.find(data(a[i].first + a[i].second, i)))
#define in1(i) s1.emplace(a[i].second, i)
#define out1(i) s1.erase(s1.find(data(a[i].second, i)))
#define in2(i) s2.emplace(a[i].first, i)
#define out2(i) s2.erase(s2.find(data(a[i].first, i)))
#define in3(i) s3.emplace(a[i].first, i)
#define out3(i) s3.erase(s3.find(data(a[i].first, i)))
#define in4(i) s4.emplace(a[i].second, i)
#define out4(i) s4.erase(s4.find(data(a[i].second, i)))
#define in5(i) s5.emplace(a[i].first + a[i].second, i)
#define out5(i) s5.erase(s5.find(data(a[i].first + a[i].second, i)))

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        las = 0;
        s0.clear(), s1.clear(), s2.clear(), s3.clear(), s4.clear(), s5.clear();
        scanf("%d", &n);
        for (int i = 0; i < n; i++) scanf("%d%d", &a[i].first, &a[i].second);
        for (int i = 0; i < n; i++) in3(i);
        for (int i = 0; i < n; i++) in5(i);
        for (int k = 1; k <= 2 * n; k++) {
            cur = std::make_pair(INT64_MIN, c3);
            if (sz3 >= 1) cur = std::max(cur, std::make_pair(las + v3, c3));
            if (sz4 >= 1) cur = std::max(cur, std::make_pair(las + v4, c4));
            if (sz1 >= 1 && sz5 >= 1) cur = std::max(cur, std::make_pair(las - v1 + v5, c15));
            if (sz2 >= 1 && sz5 >= 1) cur = std::max(cur, std::make_pair(las - v2 + v5, c25));
            int id, id1, id2, id5;
            switch (cur.second) {
                case c3:
                    id = s3.rbegin()->id;
                    out3(id);
                    out5(id);
                    in4(id);
                    in2(id);
                    break;
                case c4:
                    id = s4.rbegin()->id;
                    out4(id);
                    out2(id);
                    in0(id);
                    in1(id);
                    break;
                case c15:
                    id1 = s1.begin()->id;
                    id5 = s5.rbegin()->id;
                    out1(id1);
                    out0(id1);
                    in2(id1);
                    in4(id1);
                    out5(id5);
                    out3(id5);
                    in0(id5);
                    in1(id5);
                    break;
                case c25:
                    id2 = s2.begin()->id;
                    id5 = s5.rbegin()->id;
                    out2(id2);
                    out4(id2);
                    in3(id2);
                    in5(id2);
                    out5(id5);
                    out3(id5);
                    in0(id5);
                    in1(id5);
                    break;
            }
            /*
            printf("(%d) %lu %lu %lu %lu %lu %lu\n", cur.second, sz0, sz1, sz2, sz3, sz4, sz5);
            assert(sz0 == sz1);
            assert(sz2 == sz4);
            assert(sz3 == sz5);
            assert(sz3 + sz4 + sz0 == n);
            assert(sz4 + 2 * sz0 == k);
            */
            las = cur.first;
            printf("%lld%c", las, " \n"[k == 2 * n]);
        }
    }
    return 0;
}
