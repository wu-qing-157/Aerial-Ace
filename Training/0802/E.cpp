#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

vector<pair<int, int> >G[maxn];

long long ans = 0;
int n, k;

int dfs(int u, int f = -1) {
	int siz = 1;
	for (auto e : G[u]) {
		int v = e.first;
		if (v == f) continue;
		int tmp = dfs(v, u);
		siz += tmp;
		ans += 1ll * e.second * min(tmp, k);
	}
	return siz;
}

int main() {

	while (scanf("%d%d", &n, &k) != EOF) {	
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= n - 1; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			G[u].push_back(make_pair(v, w));
			G[v].push_back(make_pair(u, w));
		}
		ans = 0;
		dfs(1);
		printf("%lld\n", ans);
	}
	return 0;
}
