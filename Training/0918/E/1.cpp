#include <cstdio>

int cnt[100];

int main() {
    for (int i = 1; i <= 30; i += 2) {
        printf("%2d", i);
        for (int j = 0; j < i; j++) cnt[j] = 0;
        for (int j = 0; j < i; j++) cnt[j * j % i]++;
        for (int j = 0; j < i; j++) printf(" %2d", cnt[j]);
        puts("");
    }
}
