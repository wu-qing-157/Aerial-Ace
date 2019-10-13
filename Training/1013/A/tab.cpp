#include <cstdio>
#include <cstdint>

const int64_t MOD = 1e9 + 7;

int64_t pow(int64_t a, int exp) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ret;
}

int64_t sum;

int main() {
    FILE *table = fopen("table", "w");
    for (int64_t i = 1; i <= 1000000000; i++) {
        (sum += 2 * i % MOD * pow((i + 1) * (i + 2) % MOD, MOD - 2)) %= MOD;
        if (i % 1000000 == 0) {
            printf("%ld %ld\n", i, sum);
            fprintf(table, "f[%ld] = %ld\n", i, sum);
        }
    }
    return 0;
}
