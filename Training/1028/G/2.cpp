#include <cstdio>
#include <utility>

const int N = 510;
int n, m, d[N], cnt, k = 1000;
bool v[N][N];

void lk(int i, int j) {
    d[i]++, d[j]++, v[i][j] = v[j][i] = true, cnt--;
}

void link(int i, int j) {
    if (i > j) std::swap(i, j);
    lk(i, j);
    for (int s = 1; s <= n; s++) {
        if (s == i || s == j) continue;
        if (!v[i][s] && d[i] + d[s] >= k) link(i, s);
        if (!v[j][s] && d[j] + d[s] >= k) link(j, s);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    cnt = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++) {
        static int u, v;
        scanf("%d%d", &u, &v);
        lk(u, v);
    }
    while (cnt) {
        k--;
        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                if (!v[i][j] && d[i] + d[j] >= k)
                    link(i, j);
    }
    printf("%d\n", k);
    return 0;
}
