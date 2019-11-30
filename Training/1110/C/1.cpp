#include <cstdio>
#include <utility>

const int N = 1e5 + 10;
int n, q, a[N], b[N], sa[N], sb[N];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i] &= 1, sa[i] = sa[i - 1] + a[i];
    for (int i = 1; i <= n; i++) scanf("%d", b + i), b[i] &= 1, sb[i] = sb[i - 1] + b[i];
    while (q--) {
        static int a1, b1, a2, b2;
        scanf("%d%d%d%d", &a1, &b1, &a2, &b2);
        if (a1 > a2) std::swap(a1, a2);
        if (b1 > b2) std::swap(b1, b2);
        puts(a[a1] == b[b1] &&
                (sa[a2] - sa[a1 - 1] == 0 || sa[a2] - sa[a1 - 1] == a2 - a1 + 1) &&
                (sb[b2] - sb[b1 - 1] == 0 || sb[b2] - sb[b1 - 1] == b2 - b1 + 1) ?
                "YES" : "NO");
    }
    return 0;
}
