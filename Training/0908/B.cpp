#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

priority_queue<pii, vector<pii>, greater<pii> >pq;

const int maxn = 1e3 + 10;

int dis[maxn];
bool vis[maxn];

vector<pii>G[maxn];

void dijk() {
	memset(vis, 0, sizeof vis);
	while (pq.size()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) continue; 
		vis[u] = true;
		for (auto e : G[u]) {
			int v = e.second, w = e.first;
			if (dis[v] == -1 || dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(make_pair(dis[v], v));
			}
		}
	}
}

void work() {
	int V, E, S, K, C;
	scanf("%d%d%d%d%d", &V, &E, &S, &K, &C);
	
	for (int i = 1; i <= V; i++) G[i].clear();
	
	memset(dis, -1, sizeof dis);
	for (int i = 1; i <= K; i++) {
		int x; scanf("%d", &x);
		pq.push(make_pair(0, x));
		dis[x] = 0;
	}
	for (int i = 1; i <= E; i++) {
		int u, v, w; 
		scanf("%d%d%d", &u, &v, &w);
		G[u].push_back(make_pair(w, v));
		G[v].push_back(make_pair(w, u));
	}
	
	dijk();
	int dis1 = -1;
	for (int i = 1; i <= V; i++)
		if (dis1 == -1 || dis[i] > dis1)
			dis1 = dis[i];
	
	pq.push(make_pair(0, S));
	memset(dis, -1, sizeof dis);
	dis[S] = 0;
	dijk();
		
	int dis2 = -1;
	for (int i = 1; i <= V; i++)	
		if (dis2 == -1 || dis[i] > dis2)
			dis2 = dis[i];
	
	if (dis1 * C < dis2)
		printf("%d\n", dis1);
	else
		printf("%d\n", dis2);
		
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
