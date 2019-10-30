#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
vector<pair<int, int> >G[maxn];

bool inq[maxn];

struct Ans { int u, v, w; };

vector<Ans>ans; 
queue<int>q;

int fa[maxn], dep[maxn];

pair<int, int>edge[maxn];
bool tag[maxn];

vector<int>dV[maxn];

void bfs(int x) {
	while (q.size()) q.pop();
	q.push(x); inq[x] = true;
	int maxdep = 0;
	while (q.size()) {
		int u = q.front(); q.pop(); 
		dV[dep[u]].push_back(u);
		for (auto e : G[u]) {
			int v = e.first;
			if (!inq[v]) {
				q.push(v); 
				inq[v] = true;
				fa[v] = u;
				dep[v] = dep[u] + 1;
				maxdep = max(maxdep, dep[v]);
			} 
		}
	}
	for (int d = maxdep; d >= 0; d--) {
		for (auto u : dV[d]) {
			int last = 0, f = 0;
			for (auto e : G[u]) {
				int v = e.first;
				if (fa[u] == v) f = e.second;
				if (tag[e.second] || fa[u] == v) continue;
				if (!last) last = e.second;
				else {
					ans.push_back((Ans) {edge[last].first ^ edge[last].second ^ u, u, v} );
					tag[last] = tag[e.second] = true;
					last = 0;
				}
			}
			if (last != 0 && f != 0) {
				ans.push_back((Ans) {edge[last].first ^ edge[last].second ^ u, u, fa[u]} );
				tag[last] = tag[f] = true;
			}
		}
	}
		
	for (int i = 0; i <= maxdep; i++) dV[i].clear();
}

int main() {
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(make_pair(v, i));
		G[v].push_back(make_pair(u, i));
		if (u > v) swap(u, v);
		edge[i] = make_pair(u, v);
	}
	for (int i = 1; i <= n; i++)
		if (!inq[i]) bfs(i);
	printf("%d\n", int(ans.size()));
	for (auto e : ans) 
		printf("%d %d %d\n", e.u, e.v, e.w);
	return 0;	
}
