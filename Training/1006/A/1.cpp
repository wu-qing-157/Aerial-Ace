#include <cstdint>
#include <cstdio>
#include <vector>

int64_t a, b;
std::vector<std::pair<char, char>> ans;

int64_t gcd(int64_t x, int64_t y) {
    return y == 0 ? x : gcd(y, x % y);
}

void pure() {
    auto x = gcd(a, b);
    a /= x, b /= x;
}

int main() {
    scanf("%lld%lld", &a, &b);
    while (true) {
        pure();
        if (a == b) break;
        if (a % 2 == 0) {
            ans.emplace_back('B', 'B');
            a /= 2;
        } else if (b % 2 == 0) {
            ans.emplace_back('A', 'A');
            b /= 2;
        } else if (a > b) {
            ans.emplace_back('A', 'B');
            a += b;
        } else {
            ans.emplace_back('B', 'A');
            b += a;
        }
    }
    printf("%d\n", int(ans.size()));
    for (auto p : ans)
        printf("%c+=%c\n", p.first, p.second);
    return 0;
}
