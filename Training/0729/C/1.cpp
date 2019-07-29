#include <cstdio>

const int N = 110;

int n, m, delta;
char a[N], b[N], c[N];

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%d%d%s%s%s", &n, &m, a, b, c);
        delta = (a[0] - b[0] + 26) % 26;
        for (int i = 0; i < m; i++) c[i] = (c[i] - 'A' + delta) % 26 + 'A';
        printf("Case #%d: %s\n", cas, c);
    }
    return 0;
}
