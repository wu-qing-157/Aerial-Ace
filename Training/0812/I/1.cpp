#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>

const int N = 1e4 + 10;
int n, k, a[N], h[N], last;
int64_t w[N], pre[N], suf[N];
std::pair<int, int> x[N];
char op[10];

int f(int h) {
    if (h == 0) return 0;
    else return 1 << h;
}

int64_t _abs(int64_t x) {
    return x >= 0 ? x : -x;
}

void proceed() {
    for (int i = 1; i <= n; i++)
        x[i] = std::make_pair(a[i], h[i]);
    std::sort(x + 1, x + n + 1);
    for (int i = 1; i <= n; i++)
        w[i] = f(x[i].second);
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
