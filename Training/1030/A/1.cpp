#include <cstdio>
#include <algorithm>

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        static int n, m;
        scanf("%d%d", &n, &m);
        printf("%d\n", n + m + std::max(n, m));
    }
    return 0;
}
