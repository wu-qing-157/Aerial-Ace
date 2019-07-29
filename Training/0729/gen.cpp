#include <cstdio>
#include <algorithm>

int a[100000];

int main() {
    for (int i = 1; i <= 5000; i++) a[i] = i;
    std::random_shuffle(a + 1, a + 5001);
    for (int i = 1; i <= 5000; i++)
        printf("%d\n", a[i]);
    return 0;
}
