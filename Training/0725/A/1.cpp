#include <cstdio>
#include <cmath>

const long double ln2 = std::log((long double) 2), ln10 = std::log((long double) 10);
int n;

int main() {
    for (int cas = 1; true; cas++) {
        if (scanf("%d", &n) == EOF) break;
        printf("Case #%d: %d\n", cas, (int) (n * ln2 / ln10 + 1e-12));
    }
}
