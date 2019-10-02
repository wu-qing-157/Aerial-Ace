#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <random>
#include <vector>

const int tcs = 7;
const int tc[tcs] = {2, 3, 5, 7, 11, 13, 17};

int64_t mul(int64_t x, int64_t y, int64_t p) {
    int64_t t = (x * y - (int64_t) ((long double) x / p * y + 1e-3) * p) % p;
    return t < 0 ? t + p : t;
}

int64_t add(int64_t x, int64_t y, int64_t p) {
    return (uint64_t(x) + uint64_t(y)) % p;
}

int64_t pow(int64_t x, int64_t exp, int64_t p) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) ans = mul(ans, x, p);
        x = mul(x, x, p);
        exp >>= 1;
    }
    return ans;
}

bool mr_check(int64_t prime, int64_t base) {
    int64_t number = prime - 1;
    for (; ~number & 1; number >>= 1) continue;
    int64_t result = pow(base, number, prime);
    for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
        result = mul(result, result, prime);
    return result == prime - 1 || (number & 1) == 1;
}

bool mr(int64_t number) {
    if (number < 2) return false;
    if (number < 4) return true;
    if (~number & 1) return false;
    for (int i = 0; i < tcs && tc[i] < number; i++)
        if (!mr_check(number, tc[i]))
            return false;
    return true;
}

int64_t abs_(int64_t x) {
    return x > 0 ? x : -x;
}

int64_t gcd(int64_t x, int64_t y) {
    return y == 0 ? x : gcd(y, x % y);
}

std::mt19937 rando;
int64_t pr_test(int64_t number, int64_t seed) {
    int64_t x = rando() % (number - 1) + 1, y = x;
    int head = 1, tail = 2;
    while (true) {
        x = mul(x, x, number);
        x = add(x, seed, number);
        if (x == y) return number;
        int64_t ans = gcd(abs_(x - y), number);
        if (ans > 1 && ans < number) return ans;
        if (++head == tail) {
            y = x;
            tail <<= 1;
        }
    }
}

void fact(int64_t number, std::vector<int64_t> &divisor) {
    if (number > 1) {
        if (mr(number)) {
            divisor.push_back(number);
        } else {
            int64_t factor = number;
            while (factor >= number) factor = pr_test(number, rando() % (number - 1) + 1);
            fact(number / factor, divisor);
            fact(factor, divisor);
        }
    }
}

int64_t n, c;

int64_t solve(int64_t p1, int64_t p2) {
    std::vector<int64_t> div;
    fact(p1 - 1, div);
    fact(p2 - 1, div);
    int64_t phi = n;
    std::sort(div.begin(), div.end());
    div.erase(std::unique(div.begin(), div.end()), div.end());
    for (auto p : div) (phi /= p) *= p - 1;
    return pow(c, pow((1 << 30) + 3, phi - 1, (p1 - 1) * (p2 - 1)), n);
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        scanf("%lld%lld", &n, &c);
        for (int64_t p = int64_t(std::sqrt(n)) | 1; p; p -= 2)
            if (n % p == 0) {
                printf("Case %d: %lld\n", cas, solve(p, n / p));
                break;
            }
    }
    return 0;
}
