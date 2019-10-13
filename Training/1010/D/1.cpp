#include <cstdio>

int main() {
    static int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        while (n % 2 == 0) n /= 2;
        while (n % 5 == 0) n /= 5;
        puts(n == 1 ? "No" : "Yes");
    }
    return 0;
}
