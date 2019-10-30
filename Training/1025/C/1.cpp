#include <cstdio>
#include <algorithm>

const int N = 1e7 + 10;
int r, s, p, a[N];

int main() {
    scanf("%d%d%d", &r, &s, &p);
    for (int i = 1; i <= p; i++) {
        static int x, y;
        scanf("%d%d", &x, &y);
        a[i] = r - x + 1 + (y <= s ? s - y + 1 : y - s);
    }
    std::sort(a + 1, a + p + 1);
    for (int i = 2; i <= p; i++)
        if (a[i] <= a[i - 1])
            a[i] = a[i - 1] + 1;
    printf("%d\n", a[p]);
    return 0;
}
