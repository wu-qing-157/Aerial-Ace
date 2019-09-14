#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 2e4 + 10;

ll p[maxn], c[maxn];

ll dp[maxn];

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) != EOF) {
		ll a = -1, b = -1;
		for (int i = 0; i < maxn; i++) dp[i] = -1;
		dp[0] = 0;
		for (int i = 1; i <= n; i++) {
			ll c, p;
			scanf("%lld%lld", &p, &c);
			for (int v = 0; v + c < maxn; v++)
				if (dp[v] != -1 && (dp[v + c] == -1 || dp[v + c] > dp[v] + p))
					dp[v + c] = dp[v] + p;
		}
		for (int i = m; i < maxn; i++) {
			if (a == dp[i]) b = i;
			if (dp[i] != -1 && (a == -1 || dp[i] < a)) a = dp[i], b = i;
		}
		printf("%lld %lld\n", a, b);
	}
}
