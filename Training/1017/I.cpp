#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e2 + 10;
const int maxm = 1e4 + 10;
const int inf = 1e9 + 7;

int c[maxn], p[maxn];
bool vis[maxn];

int x[maxn], deg[maxn];
vector<pair<int, int> > y[maxn];

vector<int>G[maxn];

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int dp[maxm];

void init(int M, int N, int K) {
	for (int i = 1; i <= N; i++) G[i].clear();
	for (int i = 1; i <= K; i++) y[i].clear();
	memset(x, 0, sizeof (x[0]) * (K + 1));
	memset(deg, 0, sizeof (deg[0]) * (K + 1));
	memset(vis, 0, sizeof (vis[0]) * (N + 1));
	memset(dp, -1, sizeof (dp[0]) * (M + 1));
	dp[0] = 0;
	while (pq.size()) pq.pop();
}



void work() {
	int M, N, K; scanf("%d%d%d", &M, &N, &K);
	
	init(M, N, K);
	
	for (int i = 1; i <= N; i++) {
		int a; scanf("%d", &a);
		if (a == 0) {
			c[i] = inf; scanf("%d", &p[i]);
		} else scanf("%d%d", &c[i], &p[i]);
	}
	for (int i = 1; i <= K; i++) {
		int Y; scanf("%d%d", &x[i], &Y);
		for (int j = 1; j <= Y; j++) {
			int u, v; scanf("%d%d", &u, &v);
			y[i].push_back(make_pair(u, v));
			G[u].push_back(i);
		}
		deg[i] = Y;
	}
	
	for (int i = 1; i <= N; i++) pq.push(make_pair(c[i], i));
	
	while (pq.size()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) continue; 
		vis[u] = true;
		for (auto e : G[u]) 
			if (--deg[e] == 0) {
				int v = x[e];
				long long w = 0;
				for (auto nd : y[e]) 
					w += 1ll * c[nd.first] * nd.second;
				w = min(w, (long long)inf);
				if (w < c[v]) {
					c[v] = (int)w;
					pq.push(make_pair(c[v], v));
				}
			}
	}
	
	for (int i = 1; i <= N; i++)
		for (int j = c[i]; j <= M; j++) 
			if (dp[j - c[i]] != -1)  
				dp[j] = max(dp[j], dp[j - c[i]] + p[i]);
	int ans = 0;
	for (int i = 1; i <= M; i++) 
		ans = max(ans, dp[i]);
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) 
		printf("Case #%d: ", t), work();
	return 0;
}
/*
2
100 3 2
0 20
1 15 10
1 2 1
1 2 2 1 3 1
2 1 3 2
100 3 2
1 3 1
1 4 1
0 10
3 1 1 3
3 1 2 2 
*/
