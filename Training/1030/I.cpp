#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int> >G[maxn];

int dep[maxn], fa[maxn];
long long f[maxn];

// f[i] = min(f[j] + (dp[i] - dp[j]) ^ 2) + p
// f[1] = -p

// f[i] - p - dp[i] ^ 2 = min(f[j] + dp[j] ^ 2 - 2 * dp[i] * dp[j])

// val[j] = f[j] + dp[j] ^ 2 - 2 * dp[i] * dp[j]
// val[k] = f[k] + dp[k] ^ 2 - 2 * dp[i] * dp[k]

// dep[j] > dep[k]

// val[j] - val[k] = f[j] - f[k] - 2 * dp[i] * dp[j] + 2 * dp[k] * dp[i] < 0
// f[j] - f[k] < 2 * dp[i] * (dp[j] - dp[k])
// (f[j] - f[k]) / (dp[j] - dp[k]) < 2 dp[i]

int que[maxn][20];

double calc(int j, int k) {
	return (1.0 * f[j] + 1.0 * dep[j] * dep[j] - 1.0 * f[k] - 1.0 * dep[k] * dep[k]) / (2.0 * dep[j] - 2.0 * dep[k]);
}

void dfs(int u, int p) {
	for (auto e : G[u]) {
		int v = e.first, w = e.second;
		if (v == fa[u]) continue;
		fa[v] = u;
		dep[v] = dep[u] + w;
		int now = u, np;
		for (int i = 19; i >= 0; i--) {
			int j = que[now][i], k = que[j][1];
			//cout << j << ' ' << f[j] + (dep[j] - dep[v]) * (dep[j] - dep[v]) + p << endl;
			// cout << k << ' ' << f[k] + (dep[k] - dep[v]) * (dep[k] - dep[v]) + p << endl;
			//cout << f[j] + 1ll * dep[j] * dep[j] - f[k] - 1ll * dep[k] * dep[k] << endl;
			//cout << 2ll * dep[v] * (dep[k] - dep[j]) << endl;
			if (f[j] + 1ll * dep[j] * dep[j] - f[k] - 1ll * dep[k] * dep[k] > 2ll * dep[v] * (dep[j] - dep[k])) 
				now = que[now][i];
		}
		np = que[now][1];
		// printf("calc %d %d\ncalc %d %d\n", np, f[np] + (long long)(dep[np] - dep[v]) * (long long)(dep[np] - dep[v]) + p, now, f[now] + (long long)(dep[now] - dep[v]) * (long long)(dep[now] - dep[v]) + p);
		f[v] = std::min(f[now] + (long long)(dep[now] - dep[v]) * (long long)(dep[now] - dep[v]) + p,
						f[np] + (long long)(dep[np] - dep[v]) * (long long)(dep[np] - dep[v]) + p);
		now = u;
		// printf("v = %d trs = %d f[%d] = %d\n", v, now, v, f[v]);
		for (int i = 19; i >= 0; i--) {
			int j = que[now][i], k = que[j][1];
			if (calc(v, j) < calc(j, k)) 
				now = que[now][i];
		}
		que[v][0] = v;
		que[v][1] = now;
		for (int i = 2; i < 20; i++)
			que[v][i] = que[que[v][i - 1]][i - 1];
		dfs(v, p);
	}
}



void work() {
	int n, p; scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v, w; scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	
	memset(fa, 0, sizeof (fa));
	memset(f, 0, sizeof (f));
	memset(que, 0, sizeof (que));
	f[1] = -p;
	for (int i = 0; i < 19; i++)
		que[1][i] = 1;
	dfs(1, p);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, f[i]);
	printf("%lld\n", ans);
}

int main()
{
	int T; scanf("%d", &T);
	while (T--)	
		work();
	return 0;
}
