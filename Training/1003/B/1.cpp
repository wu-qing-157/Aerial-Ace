#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

bool test(int64_t ll, int64_t rr, int64_t i, int64_t k) {
    if (i > k) return ll <= 0 && rr >= 0;
    if (rr < 0) return false;
    int64_t l = 0, r = k - i + 1;
    while (l < r) {
        int64_t m = (l + r + 1) >> 1;
        if (m * i + m * (m - 1) / 2 <= rr)
            l = m;
        else
            r = m - 1;
    }
    return l * k - l * (l - 1) / 2 >= ll;
}

int64_t h1, h2, a1, a2, i, j, k;
std::string s1, s2;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld%lld%lld%lld", &h1, &h2, &a1, &a2);
        for (i = 1; i * (i + 1) / 2 < h1 + h2; i++) continue;
        for (j = 1; j * (j + 1) / 2 < h1; j++) continue;
        for (k = 1; k * (k + 1) / 2 < h2; k++) continue;
        if (j * a1 + i * a2 == k * a2 + i * a1) {
            s1 = s2 = "";
            printf("%lld ", k * a2 + i * a1);
            int64_t hh1 = i * (i + 1) / 2 - h1, hh2 = h2;
            for (int64_t ii = 1; ii <= k; ii++) {
                if (test(hh2, hh1, ii + 1, k)) s1 += 'A';
                else s1 += 'B', hh1 -= ii, hh2 -= ii;
            }
            for (int64_t ii = k + 1; ii <= i; ii++) s1 += 'A';
            hh2 = i * (i + 1) / 2 - h2, hh1 = h1;
            for (int64_t ii = 1; ii <= j; ii++) {
                if (test(hh1 - ii, hh2 - ii, ii + 1, j)) s2 += 'A', hh1 -= ii, hh2 -= ii;
                else s2 += 'B';
            }
            for (int64_t ii = j + 1; ii <= i; ii++) s2 += 'B';
            std::cout << std::min(s1, s2) << std::endl;
        } else if (j * a1 + i * a2 > k * a2 + i * a1) {
            printf("%lld ", k * a2 + i * a1);
            h1 = i * (i + 1) / 2 - h1;
            for (int64_t ii = 1; ii <= k; ii++) {
                if (test(h2, h1, ii + 1, k)) putchar('A');
                else putchar('B'), h1 -= ii, h2 -= ii;
            }
            for (int64_t ii = k + 1; ii <= i; ii++) putchar('A');
            puts("");
        } else {
            printf("%lld ", j * a1 + i * a2);
            h2 = i * (i + 1) / 2 - h2;
            for (int64_t ii = 1; ii <= j; ii++) {
                if (test(h1 - ii, h2 - ii, ii + 1, j)) putchar('A'), h1 -= ii, h2 -= ii;
                else putchar('B');
            }
            for (int64_t ii = j + 1; ii <= i; ii++) putchar('B');
            puts("");
        }
    }
    return 0;
}
