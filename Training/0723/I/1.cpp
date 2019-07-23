#include <cstdio>
#include <cstdint>

int64_t d, b, t, p;
int64_t times, ans;

int main() {
    freopen("video.in", "r", stdin);
    freopen("video.out", "w", stdout);
    scanf("%lld%lld%lld%lld", &d, &b, &t, &p);
    times = (t * (b - d) + d * p - 1) / (d * p);
    ans = (t * (b - d) + times - 1) / times;
    printf("%lld\n", ans);
    return 0;
}
