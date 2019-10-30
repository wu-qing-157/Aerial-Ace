int To[maxm];
bool vis[maxm];
vector<int>G[maxn];
int deg[maxn];
int cur[maxn];
stack<int>stk;

void dfs(int u) {
	for (cur[u]; cur[u] < G[u].size(); cur[u]++) {
		int i = cur[u];
		if (vis[abs(G[u][i])]) continue;
		int v = To[abs(G[u][i])] ^ u;
		vis[abs(G[u][i])] = true;
		dfs(v);
		stk.push(G[u][i]);
	}
}

void solve1(int n, int m) {
	int s = 1;
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		To[i] = u ^ v; s = u;
		G[u].pb(i); G[v].pb(-i);
	}
	for (int i = 1; i <= n; i++) if (G[i].size() & 1) { print("NO\n"); return; }
	dfs(s);
	if (stk.size() != m) { print("NO\n"); return; }
	print("YES\n");
	while (stk.size()) print(stk.top()), print(' '), stk.pop();
}


void solve2(int n, int m) {
	int s = 1;
	for (int i = 1; i <= m; i++) {
		int u = read(), v = read();
		To[i] = u ^ v; s = u;
		G[u].pb(i); deg[v]++;
	}
	for (int i = 1; i <= n; i++) if (G[i].size() != deg[i]) { print("NO\n"); return; }
	dfs(s);
	if (stk.size() != m) { print("NO\n"); return; }
	print("YES\n");
	while (stk.size()) print(stk.top()), print(' '), stk.pop();
}