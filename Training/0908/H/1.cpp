#include <cstdio>
#include <cstdint>

const int64_t MOD = 998244353;

struct data {
    int64_t a, b;
    inline friend data operator*(const data &a, const data &b) {
        return { (a.a * b.a + 17 * a.b % MOD * b.b) % MOD, (a.a * b.b + a.b * b.a) % MOD };
    }
};

int T;
int64_t n, nn, ans, output;
data pow[4][65537], cur;

int main() {
    for (int i = 0; i < 4; i++) {
        pow[i][0] = { 1, 0 };
        if (i == 0)
            pow[i][1] = { 499122178, 499122177 };
        else
            pow[i][1] = pow[i - 1][65535] * pow[i - 1][1];
        for (int j = 2; j < 65536; j++)
            pow[i][j] = pow[i][j - 1] * pow[i][1];
    }
    scanf("%d%lld", &T, &n);
    while (T--) {
        cur = { 1, 0 };
        nn = n;
        for (int i = 0; nn; nn >>= 16, i++)
            cur = cur * pow[i][nn & 65535];
        ans = cur.b * 2 % MOD;
        output ^= ans;
        n ^= ans * ans;
    }
    printf("%lld\n", output);
    return 0;
}
