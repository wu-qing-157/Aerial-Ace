#include <cstdio>
#include <cstring>

int n, c0, c1;
char s[10010];

int main() {
    scanf("%s", s);
    n = int(strlen(s));
    for (int i = 0; i < n; i++)
        (s[i] == '0' ? c0 : c1)++;
    if (c0 < c1) {
        for (int i = 0; i < n; i++) putchar('0');
    } else if (c0 > c1) {
        for (int i = 0; i < n; i++) putchar('1');
    } else if (s[0] == '0') {
        putchar('1');
        for (int i = 1; i < n; i++) putchar('0');
    } else if (s[0] == '1') {
        putchar('0');
        for (int i = 1; i < n; i++) putchar('1');
    }
    puts("");
    return 0;
}
