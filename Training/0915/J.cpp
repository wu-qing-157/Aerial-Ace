#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e2 + 10;
const int maxv = 5e2 + 10;
const int D = maxn * maxv;
const int V = 5e2;
const int MOD = 1e9 + 7;

int f[2][maxv * maxn * 2];
int a[maxn], s[maxn];

void work() {
	int n; scanf("%d", &n);
	
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	reverse(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
	int ans = 0;
	memset(f[0], 0, sizeof f[0]);
	f[0][0 + D] = 1;
	for (int i = 1; i <= n; i++) {
		memset(f[i & 1], 0, sizeof f[i & 1]);
		for (int d = -s[i - 1]; d <= s[i - 1]; d++) 
			if (d - (s[n] - s[i]) <= 0 && a[i] + d - (s[n] - s[i]) >= 0) {
				ans += f[i & 1 ^ 1][d + D];
				if (ans >= MOD)
					ans -= MOD;
			}
		for (int d = -s[i - 1]; d <= s[i - 1]; d++) {
			f[i & 1][d + a[i] + D] += f[i & 1 ^ 1][d + D];
			if (f[i & 1][d + a[i] + D] >= MOD)
				f[i & 1][d + a[i] + D] -= MOD;
			f[i & 1][d - a[i] + D] += f[i & 1 ^ 1][d + D];
			if (f[i & 1][d - a[i] + D] >= MOD)
				f[i & 1][d - a[i] + D] -= MOD;
		}
	}
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
