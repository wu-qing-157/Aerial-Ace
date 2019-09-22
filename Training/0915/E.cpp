#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e2 + 10;
const int maxv = 5e2 + 10;
const int V = 5e2;
const int MOD = 1e9 + 7;

int f[2][maxv << 1][maxv];

void work() {
	int n; scanf("%d", &n);
	
	memset(f, 0, sizeof f);
	f[0][0 + maxv][maxv - 1] = 1;
	
	for (int i = 1; i <= n; i++) {
		int a; scanf("%d", &a);
        memset(f[i & 1], 0, sizeof f[i & 1]);
		for (int d = -V; d <= V; d++) {
			for (int minv = 0; minv < maxv; minv++) {
				if (d + a <= V) {
					int &tmp = f[i & 1][maxv + d + a][min(minv, a)];
					tmp += f[i & 1 ^ 1][maxv + d][minv];
					if (tmp >= MOD)
						tmp -= MOD;
				}
				if (d - a >= -V) {
					int &tmp = f[i & 1][maxv + d - a][minv];
					tmp += f[i & 1 ^ 1][maxv + d][minv];
					if (tmp >= MOD)
						tmp -= MOD;
				}
			}
		}
	}
	int ans = 0;
	for (int d = 0; d <= V; d++) 
		for (int minv = d; minv < maxv; minv++) {
			ans += f[n & 1][maxv + d][minv];
			if (ans >= MOD)
				ans -= MOD;
		}
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
}
