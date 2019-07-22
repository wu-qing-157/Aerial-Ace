#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

int a[maxn];

void work() {
	int n; scanf("%d", &n);
	int ans = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n);
	int m = unique(a + 1, a + 1 + n) - a - 1;
	ans += n - m;
	n = m;
	int tmp = n + 1, now = 0;
	for (int i = 1; i <= n; i++) {
		now += a[i] - a[i - 1] - 1;
		tmp = min(tmp, now + n - i);
	}
	printf("%d\n", tmp + ans);
}

int main() {
	freopen("task.in", "r", stdin);
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
