#include <cstdio>
#include <cstring>
#include <unordered_map>

const int N = 1e5 + 10;
const int64_t MOD = 1e9 + 7;
int n, m, a[N], b[N];
int64_t ans;
std::unordered_map<int, int> mapa, mapb;
bool v[N];

int64_t pow(int64_t a, int64_t exp) {
    int64_t ans = 1;
    while (exp) {
        if (exp & 1) (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int main() {
    for (int cas = 1; scanf("%d%d", &n, &m) != EOF; cas++) {
        mapa.clear(), mapb.clear();
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < m; i++) scanf("%d", b + i);
        memset(v, 0, n * sizeof v[0]);
        for (int i = 0; i < n; i++) if (!v[i]) {
            int tar = i, cur = a[i], cnt = 1;
            v[tar] = v[cur] = true;
            while (tar != cur) {
                cnt++;
                cur = a[cur];
                v[cur] = true;
            }
            mapa[cnt]++;
        }
        memset(v, 0, m * sizeof v[0]);
        for (int i = 0; i < m; i++) if (!v[i]) {
            int tar = i, cur = b[i], cnt = 1;
            v[tar] = v[cur] = true;
            while (tar != cur) {
                cnt++;
                cur = b[cur];
                v[cur] = true;
            }
            mapb[cnt] += cnt;
        }
        ans = 1;
        for (auto pa : mapa) {
            int64_t cur = 0;
            for (auto pb : mapb) if (pa.first % pb.first == 0)
                cur += pb.second;
            (ans *= pow(cur, pa.second)) %= MOD;
        }
        printf("Case #%d: %lld\n", cas, ans);
    }
    return 0;
}
