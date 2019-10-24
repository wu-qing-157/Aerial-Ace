#include <cstdio>
#include <cstring>

const int N = 4e6 + 10;
int n, dp[N], q, l, to[N][26], ncnt = 1;
char s[N];

void add(int cur, int i) {
    if (i == l) return;
    if (to[cur][s[i] - 'a'] == 0) {
        to[cur][s[i] - 'a'] = ++ncnt;
    } else {
        dp[cur] ^= dp[to[cur][s[i] - 'a']] + 1;
    }
    add(to[cur][s[i] - 'a'], i + 1);
    dp[cur] ^= dp[to[cur][s[i] - 'a']] + 1;
}

void add() {
    scanf("%s", s); l = int(strlen(s));
    add(1, 0);
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        printf("Case %d:\n", cas);
        memset(dp, 0, sizeof dp);
        memset(to, 0, sizeof to);
        ncnt = 1;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) add();
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) add(), puts(dp[1] ? "1" : "2");
    }
    return 0;
}
