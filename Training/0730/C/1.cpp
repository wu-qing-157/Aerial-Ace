#include <cstdio>
#include <cstdint>

const int64_t MOD = 998244353;

const int N = 1e3 + 10;
int64_t pow2[N];

int n, m;
char a[N][N];
int64_t ans;

void test1() {
    int cnt = 0;
    for (int j = 0; j < m; j++) {
        int cur = 2;
        for (int i = 0; i < n; i++) if (a[i][j] != '?') {
            int cha = (a[i][j] == 'R') ^ (i & 1);
            if (cur == !cha) return;
            cur = cha;
        }
        if (cur == 2) cnt++;
    }
    ans += pow2[cnt];
}

void test2() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int cur = 2;
        for (int j = 0; j < m; j++) if (a[i][j] != '?') {
            int cha = (a[i][j] == 'R') ^ (j & 1);
            if (cur == !cha) return;
            cur = cha;
        }
        if (cur == 2) cnt++;
    }
    ans += pow2[cnt];
}

void test3(int tar) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j] != '?')
                if ((a[i][j] == 'R') ^ (j & 1) ^ (i & 1) ^ tar)
                    return;
    ans--;
}

int main() {
    pow2[0] = 1;
    for (int i = 1; i < N; i++) pow2[i] = (pow2[i - 1] << 1) % MOD;
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) scanf("%s", a[i]);
        test1();
        test2();
        test3(0);
        test3(1);
        (ans += MOD) %= MOD;
        printf("%lld\n", ans);
    }
    return 0;
}
