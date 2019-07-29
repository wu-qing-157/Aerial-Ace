#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int maxk = 1e2 + 10;
typedef long long ll;
const ll inf = ll(1e18);
ll f[maxn][maxk];
int n, k;

vector<pair<int, int> >G[maxn];

int dp(int u, int fa) {
	int s1 = 0;
	for (int i = 0; i <= k; i++) f[u][i] = inf;
	f[u][0] = 0;
	if (G[u].size() == 1u) {
		s1 = 1;
		f[u][1] = 0;
	}
	for (auto e : G[u]) {
		int v = e.first;
		int w = e.second;
		if (v == fa) continue;
		int s2 = dp(v, u);
		for (int i = s1; i >= 0; i--)
			for (int j = s2; j >= 1; j--) {
				if (i + j > k) continue;
				f[u][i + j] = min(f[u][i + j], f[u][i] + f[v][j] + 1ll * j * (k - j) * w);
			}
		s1 = min(k, s1 + s2);
	}
	return s1;
}

void init() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v, w; 
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	
}

void work() {
	int root = -1;
	for (int i = 1; i <= n; i++)
		if (G[i].size() != 1u) root = i;
	
	if (n == 1) {
		puts("0");
	} else if (n == 2) {
		if (k == 1) puts("0");
		else if (k == 2)
			printf("%d\n", G[1][0].second);
		else {
			
		}
	} else {
		dp(root, -1);
		ll ans = inf;
		for (int i = 1; i <= n; i++) 
			ans = min(ans, f[i][k]);
		printf("%lld\n", ans);
	}
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("Case #%d: ", t); 	
		init(), work();
	}
	return 0;
}
/*

2
4 2
1 2 2
1 3 3
1 4 4
4 3
1 2 2
1 3 3
1 4 4
*/
