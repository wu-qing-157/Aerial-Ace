#include <cmath>
#include <cstdio>

int n;
double a, b;

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%lf%lf", &a, &b);
        if (a <= b) puts("0.000000");
        else printf("%.6f\n", std::log(a / b) + 1);
    }
    return 0;
}
