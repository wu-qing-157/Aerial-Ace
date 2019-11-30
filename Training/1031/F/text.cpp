#include <cstdio>

int main() {
    double a, b;
    scanf("%lf%lf", &a, &b);
    printf("%f %f   %s\n", a, b, a != b ? "true" : "false");
    return 0;
}
