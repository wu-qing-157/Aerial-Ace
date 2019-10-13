#include <cstdint>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 10;
int n, a[N], b[N], ll, rr, l, r, st, dl, dr;
int64_t k;
bool cl, cr;

int64_t calc(int lc, int rc, bool neg, int which) {
    //printf("%d %d %s %d : ", lc, rc, neg ? "true" : "false", which);
    bool nl = cl, nr = cr;
    if (neg) (which ? nl : nr) = false;
    if (nl && nr) {
        if (lc >= 60 || rc >= 60) return INT64_MAX;
        else return (1ll << lc) + (1ll << rc) - 1;
    } else if (nl) {
        if (rc >= 60) return INT64_MAX;
        else return 1ll << rc;
    } else if (nr) {
        if (lc >= 60) return INT64_MAX;
        else return 1ll << lc;
    } else {
        return 0;
    }
}

bool check(int i, int which) {
    return a[i + (which ? dl : dr)] == 1;
}

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        memset(a, 0, sizeof a);
        memset(b, 0, sizeof b);

        scanf("%d%lld", &n, &k);
        if (n % 4 == 0)
            ll = rr = n / 2, l = r = rr / 2, st = 0, dr = 1, dl = -1;
        else if (n % 4 == 1)
            rr = n / 2, ll = rr + 1, l = r = rr / 2, st = 0, dl = dr = 1;
        else if (n % 4 == 2)
            rr = n / 2 - 1, ll = n / 2 + 1, l = r = rr / 2, st = 0, dr = 3, dl = 1;
        else
            rr = n / 2, ll = rr + 1, r = rr / 2, l = r + 1, st = 1, dl = dr = 1;

        int64_t pre = l >= 60 ? 0 : (k - 1) / ((1ll << l) + (1ll << r) - 1);
        if (ll <= 60 && pre >= (1ll << ll)) {
            printf("Case #%d: NOT FOUND!\n", cas);
            continue;
        }
        if (l < 60) k = (k - 1) % ((1ll << l) + (1ll << r) - 1) + 1;
        for (int i = 0; pre; i++) {
            a[i] = pre & 1;
            pre >>= 1;
        }

        cl = cr = true;
        for (int i = 0, which = st; i < rr; (which ? l : r)--, i++, which ^= 1) {
            //printf("%d : ", i);
            int64_t delta = calc(l - (which == 1), r - (which == 0), check(i, which), which);
            //printf("%lld\n", delta);
            if (k > delta) {
                b[i] = 1, k -= delta;
                if (!check(i, which)) (which ? cl : cr) = false;
            } else {
                if (check(i, which)) (which ? cl : cr) = false;
            }
        }

        printf("Case #%d: ", cas);
        for (int i = ll - 1; i >= 0; i--) putchar(a[i] + '0');
        for (int i = 0; i < rr; i++) putchar(b[i] + '0');
        puts("");
    }
    return 0;
}
