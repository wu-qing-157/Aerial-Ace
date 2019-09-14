#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e6;
double a[N], k;
char s[N << 1];
int n;

int main() {
    a[1] = 15. / 4;
    for (int i = 2; i < N; i++)
        a[i] = 1 / (1 / a[i - 1] + 5. / 3) + 3;
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%lf", s, &k);
        if (strlen(s) > 6)
            printf("%.10f\n", 1 / (1 / a[N - 1] + 1. / 3) * k);
        else
            sscanf(s, "%d", &n), printf("%.10f\n", 1 / (1 / a[n] + 1. / 3) * k);
    }
    return 0;
}
