#include <cstdio>
#include <algorithm>

const int N = 1e5 + 10;
int n, a[N], b[N], l[N], r[N], L, R, k;

int main() {
    scanf("%d%d%d%d", &n, &L, &R, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1])
            l[i] = 1, r[i] = k;
        else if (a[i] == a[i - 1])
            l[i] = r[i] = 0;
        else
            l[i] = -k, r[i] = -1;
    }
    b[0] = L;
    for (int i = 1; i < n; i++) b[i] = std::max(L, b[i - 1] + l[i]);
    for (int i = n - 1; i; i--) b[i - 1] = std::max(b[i - 1], b[i] - r[i]);
    for (int i = 0; i < n; i++)
        if (b[i] < L || b[i] > R) {
            puts("-1");
            return 0;
        }
    for (int i = 1; i < n; i++)
        if (std::abs(b[i] - b[i - 1]) > k) {
            puts("-1");
            return 0;
        }
    for (int i = 0; i < n; i++) printf("%d%c", b[i], " \n"[i == n - 1]);
    return 0;
}
