#include <cstdio>
#include <unordered_map>

const int64_t MOD = 998244353;
const int64_t inv2 = 499122177, inv3 = 332748118;

int log2(int64_t x) {
    return 63 - __builtin_clzll(x);
}

int64_t g(int64_t n) {
    int k = log2(n);
    return ((k + 3) * (n % MOD) + MOD - (1ll << (k + 1)) % MOD) % MOD;
}

std::unordered_map<int64_t, int64_t> gsummap;
int64_t gsum(int64_t n) {
    auto it = gsummap.find(n);
    if (it != gsummap.end()) return it->second;
    int64_t ret = 0;
    for (int k = 0; true; k++) {
        int64_t l = 1ll << k, r = std::min<int64_t>((1ll << (k + 1)) - 1, n);
        if (l > r) break;
        l--;
        //printf("part1 %lld %lld %lld\n", inv3 * 3 % MOD, r, inv3 * (k + 3) % MOD * (r % MOD) % MOD * (r % MOD + 1) % MOD * (2 * r % MOD + 1) % MOD);
        //printf("part2 %lld\n", inv2 * (k + 3 - (1ll << (k + 2))) % MOD * (r % MOD) * (r % MOD + 1) % MOD + MOD);
        int64_t ansr = inv3 * (k + 3) % MOD * (r % MOD) % MOD * (r % MOD + 1) % MOD * (2 * r % MOD + 1) % MOD
            + inv2 * ((k + 3 - (1ll << (k + 2))) % MOD) % MOD * (r % MOD) % MOD * (r % MOD + 1) % MOD - (1ll << (k + 1)) % MOD * (r % MOD) % MOD;
        int64_t ansl = inv3 * (k + 3) % MOD * (l % MOD) % MOD * (l % MOD + 1) % MOD * (2 * l % MOD + 1) % MOD
            + inv2 * ((k + 3 - (1ll << (k + 2))) % MOD) % MOD * (l % MOD) % MOD * (l % MOD + 1) % MOD - (1ll << (k + 1)) % MOD * (l % MOD) % MOD;
        if (ansl < 0) ansl += MOD;
        if (ansr < 0) ansr += MOD;
        //printf("%d %d %d %lld %lld\n", k, l, r, ansl, ansr);
        int64_t ans = (ansr - ansl) % MOD;
        ret = (ret + ans + MOD) % MOD;
    }
    return gsummap[n] = ret;
}

std::unordered_map<int64_t, int64_t> fsummap;
int64_t fsum(int64_t a) {
    auto it = fsummap.find(a);
    if (it != fsummap.end()) return it->second;
    if (a == 0) return fsummap[a] = 0;
    if (a == 1) return fsummap[a] = 1;
    if (a & 1) {
        int64_t n = a / 2, ans = (fsum(n) * 3 + fsum(n + 1)) % MOD;
        (ans += gsum(n)) %= MOD;
        (ans += (inv3 * 2 * (n % MOD) % MOD + 1) % MOD * (n % MOD + 1) % MOD * (2 * n % MOD + 1) % MOD) %= MOD;
        if (ans == 0) ans = MOD;
        return fsummap[a] = ans - 1;
    } else {
        int64_t n = a / 2, ans = (fsum(n - 1) + fsum(n) * 3) % MOD;
        (ans += gsum(n - 1)) %= MOD;
        (ans += n % MOD * g(n)) %= MOD;
        (ans += inv3 * 2 * (n % MOD) % MOD * (n % MOD + 1) % MOD * (2 * n % MOD + 1) % MOD) %= MOD;
        if (ans == 0) ans = MOD;
        return fsummap[a] = ans - 1;
    }
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        int64_t l, r;
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", (fsum(r) + MOD - fsum(l - 1)) % MOD);
        printf("%lu\n", fsummap.size());
    }
    return 0;
}
