#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int N = 25010;

int n, m, k;
int dfn[N], low[N], timer, st[N], top, col[N], colcnt, shun[N];
std::pair<int, int> a[N];
std::vector<int> to[N];
void tarjan(int x, int fa) {
    dfn[x] = low[x] = ++timer; st[++top] = x;
    for (int too : to[x])
        if (too != fa) {
            if (!dfn[too]) {
                tarjan(too, x);
                low[x] = std::min(low[x], low[too]);
            } else {
                if (!col[too]) low[x] = std::min(low[x], dfn[too]);
            }
        }
    if (dfn[x] == low[x]) {
        ++colcnt;
        while (true) {
            int now = st[top--];
            col[now] = colcnt;
            if (now == x) break;
        }
    }
}

struct data {
    int id, c0, idto;
    data() {}
    data(int id, int c0, int idto) : id(id), c0(c0), idto(idto) {}
} vert[N];
int start[N], sz[N];
int64_t mat[N][27][27], ans = 1;

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        to[a].push_back(b);
        to[b].push_back(a);
    }
    tarjan(1, 0);

    for (int i = 1; i <= n; i++) printf("%d ", col[i]); puts("");

    for (int i = 1; i <= n; i++) a[i] = std::make_pair(col[i], i);
    std::sort(a + 1, a + n + 1);
    for (int i = 1, j = 1; i <= n; i++)
        if (a[i].first == j)
            start[j++] = i;
    start[colcnt + 1] = n + 1;
    for (int i = 1; i <= colcnt; i++) sz[i] = start[i + 1] - start[i];
    start[colcnt + 1] = n + 1;
    for (int i = 1; i <= n; i++) shun[a[i].second] = i;
    for (int i = 1; i <= n; i++) {
        for (int too : to[a[i].second]) {
            int color = col[too];
            int idto = shun[too] - start[color] + 1;
            if (color == a[i].first) {
                mat[color][i - start[a[i].first] + 1][idto]++;
            } else if (color > a[i].first) {
                vert[a[i].first] = {i - start[a[i].first] + 1, color, idto};
            }
        }
    }

    for (int i = 1; i <= colcnt; i++) {
        for (int j = 1; j <= sz[i]; j++, puts(""))
            for (int k = 1; k <= sz[i]; k++)
                printf("%ld ", mat[i][j][k]);
        puts("");
    }
    for (int i = 1; i <= colcnt; i++)
        printf("%d %d -> %d %d\n", i, vert[i].id, vert[i].c0, vert[i].idto);

    for (int i = 1; i <= colcnt; i++) {
        int n = sz[i], m = sz[i] + 1;
        int64_t **a = mat[i];
        a[vert[i].id][m] = 1;
        a[m][vert[i].id] = 1;
        for (int j = 1; j <= n; j++) {
            if (!a[j][j]) {
                for (int l = 1; l <= n; l++)
                    if (a[l][j]) {
                        for (int ll = 1; ll <= m; ll++)
                            a[j][ll] = (a[j][ll] + a[l][ll]) % MOD;
                        break;
                    }
            }
            if (!a[j][j]) continue;
            for (int k = 1; k <= n; k++)
                if (a[j][k]) {
                    for (int l = 1; l <= m; l++)
                         a[j][l] = (a[j][l] + MOD - a[j][k] * a[k][l] % MOD) % MOD;
                }
        }
        for (int j = n; j; j--)
            for (int k = j + 1; k <= n; k++)
                if (a[j][k]) {
                    a[j][m] = (a[j][m] + MOD - a[j][k] * a[k][m] % MOD) % MOD;
                    a[j][k] = 0;
                }
        int cid = 0;
        for (int j = 1; j <= m; i++)
            if (a[m][j]) {
                cid = j;
                break;
            }
        if (a[cid][cid]) {
            int64_t &tar = mat[vert[i].c0][vert[i].idto][vert[i].idto];
            tar = (tar + MOD - a[cid][m]) % MOD;
        } else {
        }
    }
    return 0;
}
