#include <cstdint>

const int tcs = 7;
const int tc[tcs] = {2, 3, 5, 7, 11, 13, 17};

int64_t mul(int64_t x, int64_t y, int64_t p) {
    int64_t t = (x * y - (int64_t) ((long double) x / p * y + 1e-3) * p) % p;
    return t < 0 ? t + p : t;
}

int64_t add(int64_t x, int64_t y, int64_t p) {
    return (0ll + x + y) % p;
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

#include <cassert>
#include <cstdio>
#include <vector>

int64_t n;
std::vector<int64_t> ans;

int64_t solve1(int64_t x) {
    for (; true; x--) {
        assert(x >= 2);
        if (mr(x)) {
            ans.push_back(x);
            return x;
        }
    }
}

void solve5(int64_t x) {
    ans.push_back(2);
    ans.push_back(2);
    ans.push_back(2 + (x & 1));
    x -= 6 + (x & 1);
    for (int64_t i = 2, j = x - 2; j >= 2; i++, j--)
        if (mr(i) && mr(j)) {
            ans.push_back(i);
            ans.push_back(j);
            return;
        }
    assert(false);
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        ans.clear();
        scanf("%lld", &n);
        if (n < 12) {
            printf("Case %d: IMPOSSIBLE\n", cas);
            continue;
        }
        n -= n >= 2000 ? solve1(n - 1000) : solve1(n - 10);
        solve5(n);
        printf("Case %d:", cas);
        for (auto i : ans) printf(" %lld", i);
        puts("");
    }
    return 0;
}
