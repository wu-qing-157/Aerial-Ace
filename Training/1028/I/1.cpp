#include <cstdio>

int n, ret;
char s[10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", s);
        ret ^= s[0] == 'L';
    }
    puts(ret ? "LIE" : "TRUTH");
    return 0;
}
