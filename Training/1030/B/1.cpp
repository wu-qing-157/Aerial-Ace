#include <cstdio>
#include <cstring>

char s[100];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int ans = 0;
        for (int i = 0; i < int(strlen(s)); i++) ans += s[i] == 'C' ? 12 : (s[i] == 'H' ? 1 : 16);
        printf("%d\n", ans);
    }
    return 0;
}
