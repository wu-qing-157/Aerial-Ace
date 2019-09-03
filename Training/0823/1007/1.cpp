#include <cstdio>

int n;
bool s[2010][2010], t[2010][2010];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        s[0][0] = false;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < (1 << (i - 1)); j++)
                for (int k = 0; k < (1 << (i - 1)); k++) {
                    t[j * 2][k * 2] = t[j * 2][k * 2 + 1] = t[j * 2 + 1][k * 2 + 1] = s[j][k];
                    t[j * 2 + 1][k * 2] = !s[j][k];
                }
            for (int j = 0; j < (1 << i); j++)
                for (int k = 0; k < (1 << i); k++)
                    s[j][k] = t[j][k];
        }
        for (int i = 0; i < (1 << n); i++, puts(""))
            for (int j = 0; j < (1 << n); j++)
                putchar(s[i][j] ? 'P' : 'C');
    }
    return 0;
}
