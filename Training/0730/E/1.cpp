#include <cstdio>

int n;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("%d\n", (n + 3) / 2);
    }
    return 0;
}
