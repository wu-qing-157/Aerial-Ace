#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int x[maxn];

int l[maxn], r[maxn];
int sum[maxn];

void work() {
	int n, m; 
	scanf("%d%d", &n, &m);
	int k = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &l[i], &r[i]);
		x[++k] = l[i];
		x[++k] = r[i] + 1;
	}
	sort(x + 1, x + 1 + k);
	k = unique(x + 1, x + 1 + k) - x - 1;
	
	for (int i = 1; i <= k; i++) sum[i] = 0;
	
	for (int i = 1; i <= m; i++) {
		l[i] = lower_bound(x + 1, x + 1 + k, l[i]) - x;
		r[i] = lower_bound(x + 1, x + 1 + k, r[i] + 1) - x;
		sum[l[i]] ^= 1; sum[r[i]] ^= 1;
	}
	
	int now = 0, ans = 0;
	
	for (int i = 1; i < k; i++) {
		now ^= sum[i];
		if (now) 
			ans += x[i + 1] - x[i];
	}
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		work();
	}
	return 0;
}
