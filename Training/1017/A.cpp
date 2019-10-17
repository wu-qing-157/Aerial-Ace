#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int p[maxn];

void work() {
	int n; scanf("%d", &n);
	long long ans = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &p[i]), ans += p[i];
	std::sort(p + 1, p + 1 + n);
	for (int i = n - 2; i >= 1; i -= 3) 
		ans -= p[i];
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		printf("Case #%d: ", t), work();
	return 0;
}
