#include <cstdio>
#include <utility>
#include <vector>

const int N = 30, M = 300;
int n, m, k, id[N][N], a[M];
char s[N][N];
std::pair<int, int> wh[M];
std::vector<int> to[M];

void link(int u, int v) {
    to[u].push_back(v);
    to[v].push_back(u);
}

void stepU() {
    putchar('U');
    for (int i = 1; i <= k; i++) {
        int x = wh[a[i]].first, y = wh[a[i]].second;
        a[i] = x && s[x - 1][y] == '1' ? id[x - 1][y] : id[x][y];
    }
}
void stepD() {
    putchar('D');
    for (int i = 1; i <= k; i++) {
        int x = wh[a[i]].first, y = wh[a[i]].second;
        a[i] = x + 1 < n && s[x + 1][y] == '1' ? id[x + 1][y] : id[x][y];
    }
}
void stepL() {
    putchar('L');
    for (int i = 1; i <= k; i++) {
        int x = wh[a[i]].first, y = wh[a[i]].second;
        a[i] = y && s[x][y - 1] == '1' ? id[x][y - 1] : id[x][y];
    }
}
void stepR() {
    putchar('R');
    for (int i = 1; i <= k; i++) {
        int x = wh[a[i]].first, y = wh[a[i]].second;
        a[i] = y + 1 < m && s[x][y + 1] == '1' ? id[x][y + 1] : id[x][y];
    }
}

bool find(int cur, int fa, int tar) {
    if (cur == tar) return true;
    for (int nxt : to[cur]) if (nxt != fa && find(nxt, cur, tar)) return true;
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", s[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == '1') {
                ++k;
                a[k] = k;
                id[i][j] = k;
                wh[k] = std::make_pair(i, j);
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == '1') {
                if (i && s[i - 1][j] == '1') link(id[i][j], id[i - 1][j]);
                if (j && s[i][j - 1] == '1') link(id[i][j], id[i][j - 1]);
            }
    for (int i = 1; i < k; i++)
        while (a[i] != a[i + 1]) {
            int x = wh[a[i]].first, y = wh[a[i]].second;
            if (x && s[x - 1][y] == '1' && find(id[x - 1][y], id[x][y], a[i + 1])) stepU();
            else if (x + 1 < n && s[x + 1][y] == '1' && find(id[x + 1][y], id[x][y], a[i + 1])) stepD();
            else if (y && s[x][y - 1] == '1' && find(id[x][y - 1], id[x][y], a[i + 1])) stepL();
            else if (y + 1 < m && s[x][y + 1] == '1' && find(id[x][y + 1], id[x][y], a[i + 1])) stepR();
        }
    return 0;
}
