#include <cstdio>
#include <cstdint>
#include <algorithm>

__int128_t n, k, ans;

void solve(int d, __int128_t lc, __int128_t lv, __int128_t mv, __int128_t rc, __int128_t rv) {
    if (lc & 1) ans ^= lv;
    if (rc & 1) ans ^= rv;
    ans ^= mv;
    if (d == 1) return;
    solve(d - 1, lc / k, lv * k + 1, lc % k * lv + rc % k * rv + mv + 1, rc / k, rv * k + 1);
}

void solve2() {
	__int128_t tmp = 0;
	for (__int128_t i = 0; i < 62; i++) {
		__int128_t a = (n + 1) % (1ll << (i + 1));
		__int128_t b = (n + 1) / (1ll << (i + 1));
		__int128_t c = b * (1ll << i) + std::max<__int128_t>(0, a - (1ll << i));
		tmp |= (c & 1) << i;
	}
	printf("%lld\n", (int64_t) tmp);
}

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        ans = 0;
        int64_t tn, tk;
        scanf("%lld%lld", &tn, &tk), n = tn, k = tk;
        if (k == 1) {
            solve2();
            continue;
        }
        int dep = 1;
        __int128_t cnt = 1;
        while (true) {
            if (n <= cnt) {
                solve(dep, n - 1, 1, 1, cnt - n, 0);
                break;
            }
            dep++;
            n -= cnt;
            cnt *= k;
        }
        printf("%lld\n", (int64_t) ans);
    }
    return 0;
}
