#include <cstdio>
#include <unordered_set>
#include <queue>

const int N = 1e5 + 10;

int n, ans[N];
std::unordered_set<int> to[N], from[N];
std::queue<std::pair<int, int>> que;

void addedge(int u, int v) {
    if (u == v) {
        que.emplace(u, 0);
        que.emplace(u, 1);
    } else if (u != 0 || v != 1) {
        to[u].insert(v);
        from[v].insert(u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        addedge(i, (i + i) % n);
        addedge(i, (i + i + 1) % n);
    }
    while (!que.empty()) {
        auto f = que.front();
        int v, u;
        que.pop();
        printf("test %d %d\n", f.first, f.second);
        if (f.second) {
            v = f.first;
            if (from[v].empty()) continue;
            u = *(from[v].begin());
        } else {
            u = f.first;
            if (to[u].empty()) continue;
            v = *(to[u].begin());
        }
        printf("%d %d\n", u, v);
        for (auto i : to[u]) from[i].erase(u);
        to[u].clear();
        for (auto j : from[v]) to[j].erase(v);
        from[v].clear();
        ans[u] = v;
        if (to[u].size() == 1) que.emplace(u, 0);
        if (from[v].size() == 1) que.emplace(v, 1);
    }
    return 0;
}
