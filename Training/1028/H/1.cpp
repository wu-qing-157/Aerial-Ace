#include <cstdio>
#include <queue>
#include <set>

struct event {
    int time, op, v, r;
    event(int time, int op, int v, int r = 0) : time(time), op(op), v(v), r(r) {}
    friend bool operator<(const event &a, const event &b) {
        if (a.time != b.time) return a.time > b.time;
        return a.op > b.op;
    }
};

const int N = 1e5 + 10;

int n, k, a[N], c0[N], pre;
std::priority_queue<event> queue;
std::multiset<int> set;
bool b[N];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (!a[i]) b[i] = true;
        c0[i] = c0[i - 1] + (a[i] == -1);
    }
    for (int i = 1; i <= k; i++) {
        int l, r, c, v;
        scanf("%d%d%d", &l, &r, &c);
        v = r - l + 1 - c - c0[r] + c0[l - 1];
        if (v < 0) {
            puts("impossible");
            return 0;
        }
        queue.emplace(l, 0, v, r);
    }
    for (int i = 1; i <= n; i++) {
        while (!queue.empty()) {
            auto u = queue.top();
            if (u.time != i || u.op != 0) break;
            queue.pop();
            set.insert(pre + u.v);
            queue.emplace(u.r, 1, pre + u.v);
        }
        if (b[i]) {
            if (set.empty() || *set.begin() > pre) a[i] = -1, pre++;
            else a[i] = 1;
        }
        while (!queue.empty()) {
            auto u = queue.top();
            if (u.time != i || u.op != 1) break;
            queue.pop();
            set.erase(set.find(u.v));
        }
    }
    for (int i = 1; i <= n; i++) printf("%d%c", a[i], " \n"[i == n]);
    return 0;
}
