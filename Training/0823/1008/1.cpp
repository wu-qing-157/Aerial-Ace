#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>

const int N = 1e5 + 10;
int n, k, a[N], cnt;
int64_t ans;
std::vector<int> vec;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        ans = k, cnt = n - 1;
        vec.clear();
        for (int i = 0; i < n; i++) scanf("%d", a + i);
        for (int i = 0; i < n; i++) {
            cnt -= a[i] / k;
            vec.push_back(k - a[i] % k);
            ans += a[i];
        }
        std::sort(vec.begin(), vec.end());
        for (int i = 0; i < cnt; i++) ans += vec[i];
        printf("%lld\n", ans);
    }
    return 0;
}
