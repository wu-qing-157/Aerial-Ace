#include <cstdio>
#include <algorithm>
#include <functional>
#include <utility>

const int N = 10;
int n;
std::pair<int, int> a[N];

void add(int delta) {
    for (int i = 1; i <= n; i++) a[i].first += delta;
}

void mod(int delta) {
    for (int i = 1; i <= n; i++) a[i].first %= delta;
}

int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].first, &a[i].second);
        std::sort(a + 1, a + n + 1, std::greater<std::pair<int, int>>());
        puts("NUM 10000");
        puts("ADD");
        add(10000);
        for (int i = 1; i <= n; i++) {
            printf("NUM %d\n", a[i].second);
            puts("SUB");
            add(-a[i].second);
            printf("NUM %d\n", a[i].first);
            puts("MOD");
            mod(a[i].first);
            printf("NUM %d\n", a[i].second);
            puts("ADD");
            add(a[i].second);
        }
        puts("END");
        puts("");
    }
    return 0;
}
