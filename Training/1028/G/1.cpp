#include <cstdint>
#include <cstdio>
#include <queue>
#include <vector>


const int N = 510;
int n, m, d[N], k = INT32_MAX;

struct data {
    int i, j, v;
    data(int _i, int _j) : i(std::min(_i, _j)), j(std::max(_i, _j)), v(d[i] + d[j]) {}
    friend bool operator<(const data &a, const data &b) {
        return a.v < b.v;
    }
};

std::priority_queue<data> queue;
std::vector<std::pair<int, int>> vec;
bool link[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        static int u, v;
        scanf("%d%d", &u, &v);
        link[u][v] = link[v][u] = true;
        d[u]++;
        d[v]++;
    }
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (!link[i][j])
                queue.emplace(i, j);
    while (!queue.empty()) {
        auto u = queue.top();
        queue.pop();
        if (link[u.i][u.j]) continue;
        k = std::min(k, u.v);
        d[u.i]++, d[u.j]++, link[u.i][u.j] = link[u.j][u.i] = true;
        for (int i = 1; i <= n; i++) {
            if (i != u.i && !link[i][u.i]) queue.emplace(i, u.i);
            if (i != u.j && !link[i][u.j]) queue.emplace(i, u.j);
        }
    }
    printf("%d\n", k);
    return 0;
}
