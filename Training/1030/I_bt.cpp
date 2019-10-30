#include <bits.stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

vector<pair<int, int> >G[maxn];

int dep[maxn];

void dfs(int u) {
	for (auto e : G[u]) {
		int v = e.fi
	}
	
}


void work() {
	int n, p; cin >> n >> p;
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v, w; cin >> u >> v >> w;
		G[u].push_back(make_pair(v, w));
		G[v].push_back(make_pair(u, w));
	}
	dfs(1);
}

int main() {	
	int T; cin >> T;
	while (T--)	
		work();
	return 0;
}
