#include <cstdio>

int n, a;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);
        printf("%d%c", n + 1 - a, " \n"[i == n]);
    }
    return 0;
}
