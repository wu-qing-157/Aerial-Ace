#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1e3 + 10;
int n, m, a[N], d[N][N];
std::vector<int> ans;

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", a + j);
            if (a[j] == 0) a[j] = int(1e8);
        }
        for (int j = 1; j <= m; j++)
            for (int k = 1; k <= m; k++)
                if (a[j] < a[k])
                    d[j][k]++;
    }
    for (int i = 1; i <= m; i++) {
        d[i][i] = int(1e8);
        for (int j = i + 1; j <= m; j++) {
            if (d[i][j] < d[j][i]) d[i][j] = 0;
            else if (d[i][j] > d[j][i]) d[j][i] = 0;
            else d[i][j] = d[j][i] = 0;
        }
    }
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= m; i++)
            for (int k = 1; k <= m; k++)
                d[i][k] = std::max(d[i][k], std::min(d[i][j], d[j][k]));
    for (int i = 1; i <= m; i++) {
        bool flag = true;
        for (int j = 1; j <= m && flag; j++)
            flag &= d[i][j] >= d[j][i];
        if (flag) ans.push_back(i);
    }
    for (int i = 0; i < int(ans.size()); i++)
        printf("%d%c", ans[i], " \n"[i + 1 == int(ans.size())]);
    return 0;
}
