#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

const int N = 1e3 + 10;
int n, sum, b[N];
bool a[N], v[N];
double ans[N];
char s[N];

int main() {
    freopen("blind.in", "r", stdin);
    freopen("blind.out", "w", stdout);
    scanf("%s", s);
    n = strlen(s);
    for (int i = 0; i < n; i++) a[i] = s[i] == '1';

    for (int i = 1; i <= 2 * n; i++) {
        int gcd = std::__gcd(i, n), lcm = i * n / gcd, num = i / gcd, sin = n / gcd;
        for (int j = 0, id = 0; j < gcd; j++) {
            int cnt = 0;
            for (int k = j; k < n; k += gcd) cnt += a[k];
            for (int c = 0; c < num; c++) b[id++] = cnt;
        }
        std::sort(b, b + i, std::greater<int>());
        //printf("%d:", i);
        //for (int j = 0; j < i; j++) printf(" %d", b[j]);
        //puts("");
        for (int q = (i + 1) / 2; q <= i && q <= n; q++) {
            sum = 0;
            for (int j = 0; j < i; j++) {
                if (j < i - q) sum += b[j];
                else if (j < q) sum += std::max(b[j], sin - b[j]);
                else sum += sin - b[j];
            }
            //printf("%d %d\n", q, sum);
            ans[q] = std::max(ans[q], 1. * sum / lcm);
        }
        //puts("");
    }
    
    for (int i = 2; i <= n; i++) ans[i] = std::max(ans[i - 1], ans[i]);
    for (int i = 1; i <= n; i++) printf("%.20f\n", ans[i]);
    return 0;
}
