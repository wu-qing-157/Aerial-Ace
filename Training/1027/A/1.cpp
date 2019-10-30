#include <cstdio>

int n, k;

int main() {
    scanf("%d%d", &n, &k);
    if (k == 1) {
        puts(n & 1 ? "Adrien" : "Austin");
    } else {
        puts(n ? "Adrien" : "Austin");
    }
    return 0;
}
