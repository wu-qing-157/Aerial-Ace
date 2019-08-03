#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 1e6 + 10;

vector<ll>G[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n - 1; i++) {
			int u, v;
			ll w;
			scanf("%d%d%lld", &u, &v, &w);
			G[u].push_back(w);
			G[v].push_back(w);
		}
		for (int i = 1; i <= n; i++) 
			sort(G[i].begin(), G[i].end());
		ll ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += 1ll * G[i][0] * ((ll)(G[i].size()) - 2);
			for (auto e : G[i]) ans += e;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
