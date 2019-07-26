#include <cstdio>
#include <algorithm>

int a, b, c;

int main() {
    while (scanf("%d%d%d", &a, &b, &c), a && b && c) {
        int ans = a + b + c - 2;
        ans -= std::__gcd(a, b) - 1;
        ans -= std::__gcd(b, c) - 1;
        ans -= std::__gcd(c, a) - 1;
        ans += std::__gcd(a, std::__gcd(b, c)) - 1;
        printf("%d\n", ans);
    }
    return 0;
}
