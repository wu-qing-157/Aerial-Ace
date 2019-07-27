#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e3 + 10;

vector<pair<int, pair<int, int> > >edge;

struct MFS {
	int fa[maxn];
	void init(int n) {	
		for (int i = 0; i < n; i++) fa[i] = i;
	}
	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}
	void link(int x, int y) {
		fa[find(x)] = find(y);
	}
} mfs;

void work() {
	int n, m, s, t;
	scanf("%d%d", &n, &m);
	edge.clear();
	scanf("%d%d", &s, &t);
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edge.emplace_back(w, make_pair(u, v));
	}
	sort(edge.begin(), edge.end());
	int ans = -1;
	for (int i = 0; i < m; i++)	 {
		mfs.init(n);
		int now = edge[i].first;
		for (int j = i; j >= 0; j--) {
			int u = edge[j].second.first, v = edge[j].second.second;
			if (mfs.find(u) != mfs.find(v)) mfs.link(u, v);
			if (mfs.find(s) == mfs.find(t)) {
				ans = (ans == -1 || ans > now - edge[j].first) ? 
						now - edge[j].first : ans;
				break;
			}
		}
	}
	if (ans == -1) printf("NO PATH\n");
	else printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}

/*
3
3 2
0 2
0 1 1000
1 2 5000
2 1
0 1
0 1
1000
2 0
0 1

*/
