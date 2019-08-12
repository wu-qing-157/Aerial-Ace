
 #include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>
 
const int N = 1e4 + 10;
int n, k, a[N], h[N], last;
int64_t w[N], pre[N], suf[N];
std::pair<int, int> x[N];
char op[10];
 
int64_t fibo[N];
 
int64_t c(int n, int m) {
    int64_t ret = 1;
    for (int i = 1, j = n; i <= m; i++)
        (ret *= j) /= i;
    return ret;
}
 
void init() {
    fibo[0] = 0;
    for (int i = 1; i <= 10; i++)
        fibo[i] = c(2 * i, i);
}
 
int f(int h) {
    return fibo[h];
}
 
int64_t _abs(int64_t x) {
    return x >= 0 ? x : -x;
}
 
void proceed() {
    int b = 0;
    for (int i = 1; i <= n; i++)
        x[i] = std::make_pair(a[i], h[i]), b = std::max(b, h[i]);
    std::sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++)
        w[i] = x[i].second == b ? 1 : 0;
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + w[i];
    for (int i = n; i; i--)
        suf[i] = suf[i + 1] + w[i];
    auto min = std::make_pair(INT64_MAX, 0);
    for (int i = 1; i <= n; i++)
        if (x[i].second)
            min = std::min(min, std::make_pair(int64_t(_abs(pre[i - 1] - suf[i + 1])), i));
    last = x[min.second].first;
}
 
int main() {
    init();
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        h[i] = k;
    }
    while (true) {
        proceed();
        printf("%d\n", last);
        fflush(stdout);
        scanf("%s", op);
        if (op[0] == 'E')
            break;
        for (int i = 1; i <= n; i++)
            if (h[i] && (a[i] == last || ((a[i] < last) == (op[0] == '<'))))
                h[i]--;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
    }
    return 0;
}
