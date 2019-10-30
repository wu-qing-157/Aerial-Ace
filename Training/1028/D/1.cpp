#include <cstdio>

const int N = 510;
int n, m;
char s[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
    if (n == 1) {
        int ans = 0;
        for (int j = 2; j < m; j++) if (s[1][j] == '.') ans++;
        printf("%d\n", ans);
    } else if (m == 1) {
        int ans = 0;
        for (int i = 2; i < n; i++) if (s[i][1] == '.') ans++;
        printf("%d\n", ans);
    } else if (n == 2) {
        int ans = 0;
        for (int j = 2; j < m; j++)
            if (s[1][j] == '.' && s[2][j] == '.')
                ans++;
        printf("%d\n", ans);
    } else if (m == 2) {
        int ans = 0;
        for (int i = 2; i < n; i++)
            if (s[i][1] == '.' && s[i][2] == '.')
                ans++;
        printf("%d\n", ans);
    } else {
        int ans1 = 0, ans2 = 1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if ((i == 1 || i == n) && (j == 1 || j == m)) {
                    continue;
                } else if (i == 1 || i == n || j == 1 || j == m) {
                    if (s[i][j] == '#') ans2 = 0;
                } else {
                    if (s[i][j] == '.') ans1++;
                }
            }
        printf("%d\n", ans1 + ans2);
    }
    return 0;
}
