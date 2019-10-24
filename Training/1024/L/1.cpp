#include <cstdio>
#include <queue>
#include <vector>
#include <utility>

const int N = 1e5 + 10;
int n, m, x[N], y[N];
bool v[N];
std::vector<std::pair<int, std::pair<int, int>>> to[N];
std::queue<int> queue;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        static int s, t, x, y;
        scanf("%d%d%d%d", &s, &t, &x, &y);
        to[s].emplace_back(t, std::make_pair(x, y));
        to[t].emplace_back(s, std::make_pair(-x, -y));
    }
    for (int i = 1; i <= n; i++) if (!v[i]) {
        queue.push(i);
        x[i] = y[i] = 0;
        v[i] = true;
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            for (auto p : to[u])
                if (!v[p.first]) {
                    x[p.first] = x[u] + p.second.first;
                    y[p.first] = y[u] + p.second.second;
                    v[p.first] = true;
                    queue.push(p.first);
                }
        }
    }
    for (int i = 1; i <= n; i++) printf("%d %d\n", x[i], y[i]);
    return 0;
}
