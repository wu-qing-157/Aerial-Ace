#include <cstdint>
#include <cstdio>

const int N = 3e5 + 10;
int n, k, g[N], from[N];
int64_t a[N], ans;
long double dp[N];

int64_t calc(int i, int j) {
    return a[i] + a[j] - a[(i + j) / 2] - a[(i + j + 1) / 2];
}

int q[N];

int process(long double m) {
	int head = 0, tail = 0;
    for (int i = 1, j = 0; i <= n; i++) {
    	while (head < tail && dp[q[tail]] + calc(i, q[tail]) >= dp[i - 1] + calc(i, i - 1)) --tail;
    	q[++tail] = i - 1;
    	while (head < tail - 1 && dp[q[head + 1]] + calc(i, q[head + 1]) >= dp[q[head + 2]] + calc(i, q[head + 2])) ++head;
        dp[i] = dp[q[head + 1]] + calc(i, q[head + 1]) + m;
        from[i] = q[head + 1];
        g[i] = g[q[head + 1]] + 1;
    }
    return g[n];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i), a[i] += a[i - 1];
    long double l = 0, r = 2e14;
    for (int i = 1; i <= 300; i++) {
        long double m = (l + r) / 2;
        int result = process(m);
        if (result == k) {
            break;
        } else if (result > k) {
            l = m;
        } else {
            r = m;
        }
    }
    for (int i = n; i; i = from[i])
        ans += calc(i, from[i]);
    printf("%lld\n", ans);
    return 0;
}
