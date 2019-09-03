#include <cstdio>
#include <vector>
#include <queue>

const int N = 1e5 + 10;
int n, m;
std::vector<int> to[N];
int ind[N];
double p0[N], p1[N], p2[N];
std::queue<int> queue;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) to[i].clear(), ind[i] = p0[i] = p1[i] = p2[i] = 0;
        for (int i = 1; i <= m; i++) {
            static int s, t;
            scanf("%d%d", &s, &t);
            to[s].push_back(t);
            ind[t]++;
        }
        queue.push(1);
        p0[1] = 1;
        while (!queue.empty()) {
            int u = queue.front();
            queue.pop();
            if (to[u].size() == 0) break;
            double x = 1. / (1 + to[u].size());
            for (auto v : to[u]) {
                if (--ind[v] == 0) queue.push(v);
                p0[v] += p0[u] * x / (1 - x);
                p1[v] += p0[u] * x / ((1 - x) * (1 - x));
                p1[v] += p1[u] * x / (1 - x);
                p2[v] += p0[u] * x * (x + 1) / ((1 - x) * (1 - x) * (1 - x));
                p2[v] += 2 * p1[u] * x / ((1 - x) * (1 - x));
                p2[v] += p2[u] * x / (1 - x);
            }
        }
        printf("%.2f\n", (p2[n] + p1[n]) / 2);
    }
    return 0;
}
