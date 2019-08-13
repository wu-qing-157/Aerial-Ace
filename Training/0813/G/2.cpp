#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

const int maxn = 1e5 + 10;

int f[maxn];

int main() {
	f[1] = 0;
	f[2] = 1;
	f[3] = 1;
	for (int i = 4; i < maxn; i++) {
		f[i] = f[i - 1] + f[i - 3];
		f[i] = f[i] >= MOD ? f[i] - MOD : f[i];
	}
	int T; scanf("%d", &T);
	while (T--)	 {
		int n, x, y;
		scanf("%d%d%d", &n, &x, &y);
		int k = y - x;
		if (x == 1) k++;
		if (y == n) k++;
		printf("%d\n", f[k]);
	}
}
