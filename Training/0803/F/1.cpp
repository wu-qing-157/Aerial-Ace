#include <cstdio>
#include <vector>
#include <queue>

const int N = 1e5 + 10;
int n, m, deg[N][6], dp[N][6], who[6], fake[6];
std::vector<int> to[N], fr[N];
std::queue<std::pair<int, int>> queue;
bool v[N][6];
char ab[10], zo[10];

void update(int i, int j, bool win) {
    v[i][j] = true;
    dp[i][j] = win ? 1 : 2;
    int last = (j + 5) % 6;
    if (win && fake[j] == fake[last])
        for (int f : fr[i])
            if (!v[f][last])
                update(f, last, true);
    if (!win && fake[j] != fake[last])
        for (int f : fr[i])
            if (!v[f][last])
                update(f, last, true);
    for (int f : fr[i]) {
        deg[f][last]--;
        if (deg[f][last] == 0 && !v[f][last])
            update(f, last, false);
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 6; j++)
                dp[i][j] = deg[i][j] = v[i][j] = 0;
            to[i].clear();
            fr[i].clear();
        }
        for (int i = 1; i <= m; i++) {
            static int u, v;
            scanf("%d%d", &u, &v);
            to[u].push_back(v);
            fr[v].push_back(u);
            for (int j = 0; j < 6; j++)
                deg[u][j]++;
        }
        scanf("%s%s", ab, zo);
        for (int i = 0; i < 6; i++) {
            who[i] = ab[i] == 'B';
            fake[i] = who[i] ^ (zo[i] == '1');
        }
        for (int i = 1; i <= n; i++)
            if (to[i].empty())
                for (int j = 0; j < 6; j++)
                    update(i, j, who[j] != fake[j]);
        for (int i = 1; i <= n; i++) {
            if (dp[i][0] == 0) putchar('D');
            else if (dp[i][0] == 1) {
                if (fake[0]) putchar('B');
                else putchar('A');
            } else {
                if (fake[0]) putchar('A');
                else putchar('B');
            }
        }
        puts("");
    }
    return 0;
}
