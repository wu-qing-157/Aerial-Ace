#include <cstdio>

int n, d, cnt0, cnt1;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &d);
        cnt0 = cnt1 = 0;
        for (int i = 1; i <= n; i++) {
            static int cur;
            scanf("%d", &cur);
            cnt0 += cur == 1;
            cnt1 += cur > 1;
        }
        if (d == 1) {
            puts(cnt1 == 0 && cnt0 % 3 == 0 ? "No" : "Yes");
        } else {
            puts((cnt0 % 3 == 2 && cnt1 == 1) || (cnt0 % 3 == 0 && cnt1 == 1) || (cnt0 % 3 == 1 && cnt1 == 0) ? "No" : "Yes");
        }
    }
    return 0;
}
