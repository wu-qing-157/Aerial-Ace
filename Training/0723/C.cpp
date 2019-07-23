#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e4 + 10;

const double eps = 1e-7;

bool onpath[maxn], ap[maxn];
pair<double, pair<int, int> > edge[maxn];
int S, T;
vector<int>path;

vector<pair<double, int> > G[maxn];

int sign(double x) {	
	return (x > eps) - (x < -eps);
}

priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;

double dis[maxn];
bool vis[maxn];

void dijk() {
	for (int i = 0; i < maxn; i++) dis[i] = 1e9;
	memset(vis, false, sizeof vis);
	dis[S] = 0;
	pq.push(make_pair(dis[S], S));
	while (pq.size()) {
		int u = pq.top().second; pq.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (auto e : G[u]) {
			int v = e.second;
			double w = e.first;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push(make_pair(dis[v], v));
			}
		}
	}
}

bool check(double v, int n, int m, int k) {
	for (int i = 1; i <= n; i++) G[i].clear();
	
	double len = 0;
	
	for (int i = 1; i <= m; i++) {
		double w = max(1.0, onpath[i] ? edge[i].first - v : edge[i].first + v);
		int u = edge[i].second.first, v = edge[i].second.second;
		G[u].push_back(make_pair(w, v)); G[v].push_back(make_pair(w, u));
		if (onpath[i]) len += w; 
	}
	
	dijk();
	
	return sign(len - dis[T]) == 0;
}

int main() {
	freopen("lateagain.in", "r", stdin);
	freopen("lateagain.out", "w", stdout);
	int n, m; scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) 
		scanf("%d%d%lf", &edge[i].second.first, &edge[i].second.second, &edge[i].first);
	int k; scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		int x; scanf("%d", &x);
		path.push_back(x);
		onpath[x] = true;
		ap[edge[x].second.first] ^= 1;
		ap[edge[x].second.second] ^= 1;
	}
	for (int i = 1; i <= n; i++)
		if (S && ap[i]) T = i;
		else if (ap[i]) S = i;
	double l = 0, r = 1e4;
	for (int T = 0; T <= 100; T++) {
		double mid = (l + r) / 2;
		if (check(mid, n, m, k))
			r = mid;
		else 
			l = mid;
	}
	printf("%.8f\n", l);
	for (int i = 1; i <= m; i++) {
		printf("%.8f%c", max(1.0, onpath[i] ? edge[i].first - l : edge[i].first + l), i == m ? '\n' : ' ');
	}
}
/*
4 4 
1 2 1
2 4 2
1 3 1
3 4 3
2 
3 4
*/
