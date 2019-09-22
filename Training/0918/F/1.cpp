#include <cstdio>

int n, m, k;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        int num = (m + 1) / (n - k + 1) + ((m + 1) % (n - k + 1) != 0);
        printf("%lld\n", m + 1 + 1ll * num * (k - 1));
    }
    return 0;
}
