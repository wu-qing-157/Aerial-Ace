#include <cmath>
#include <cstdio>

double a, b, r, d;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lf%lf%lf%lf", &a, &b, &r, &d);
        a += r;
        d *= acos(-1) / 180;
        if (d < acos(-1) / 2 - 1e-8 && b > a * tan(d))
            printf("%.15f\n", (a * cos(d) + b * sin(d)) / (cos(d) * (cos(d) + sin(d) * tan(d))) - r);
        else
            printf("%.15f\n", sqrt(a * a + b * b) - r);
    }
    return 0;
}
