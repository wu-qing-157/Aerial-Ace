#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

vector<int>G[maxn];

int D[maxn], L[maxn];

int color[maxn];

bool check(int u, int c) {
	color[u] = c;
	for (auto v : G[u]) {
		if (!color[v]) {
			if (!check(v, 3 - c)) return false;
		}
		else {
			if (color[v] != 3 - c) return false;
		}
	} return true;
}
typedef pair<int, int> seg;

pair<seg, seg> calc(int u, int c) {
	color[u] = c;
	pair<seg, seg> now = make_pair(make_pair(D[u], D[u]), make_pair(L[u], L[u]));
	for (auto v : G[u]) {
		if (!color[v]) {
			pair<seg, seg> nxt = calc(v, 3 - c);
			now.first.first = max(now.first.first, nxt.second.first);
			now.second.first = max(now.second.first, nxt.first.first);
			now.first.second = min(now.first.second, nxt.second.second);
			now.second.second = min(now.second.second, nxt.first.second);
		}
	} return now;
}



vector<pair<seg, seg> >tmp;

seg base;

void deal(pair<seg, seg>x) {
	if (x.first < x.second) swap(x.first, x.second);
	
	if (x.first.first == x.second.first) 
		if (x.first.second > x.second.second) 
			swap(x.first.second, x.second.second);
	
	if (x.first.second <= x.second.second) {
		if (base == make_pair(-1, int(1e9 + 10))) base = x.second;
		else {
			base.first = max(base.first, x.second.first);
			base.second = min(base.second, x.second.second);
		}
	} else tmp.push_back(x);
}



int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) { 
		int n, m; scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) G[i].clear();
		for (int i = 1; i <= m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
		}
		for (int i = 1; i <= n; i++) scanf("%d%d", &D[i], &L[i]);
		for (int i = 1; i <= n; i++) color[i] = 0;
		
		bool ok = true;	
		
		for (int i = 1; i <= n && ok; i++) 
			if (!color[i]) 
				if (!check(i, 1))
					ok = false;
		
		if (!ok) {
			printf("Case %d: IMPOSSIBLE\n", t);
			continue;
		}
		
		tmp.clear(); base = make_pair(-1, 1e9 + 10);
		for (int i = 1; i <= n; i++) color[i] = 0;
		for (int i = 1; i <= n; i++) 
			if (!color[i]) 
				deal(calc(i, 1));		
		


		//printf("%d %d\n", base.first, base.second);
		
		sort(tmp.begin(), tmp.end());
		reverse(tmp.begin(), tmp.end());

		//for (auto x : tmp)
		//	printf("%d %d %d %d\n", x.first.first, x.first.second, x.second.first, x.second.second);
		
		for (int i = 0; i < (int)tmp.size(); i++) if (i != 0) {
			tmp[i].second.first = max(tmp[i].second.first, tmp[i - 1].second.first);
			tmp[i].second.second = min(tmp[i].second.second, tmp[i - 1].second.second);
		}
		
		int K = tmp.size();
		
		for (int i = tmp.size() - 1; i >= 0; i--) if (i != 0) {
			tmp[i - 1].first.first = max(tmp[i].first.first, tmp[i - 1].first.first);
			tmp[i - 1].first.second = min(tmp[i].first.second, tmp[i - 1].first.second);
		}
		
		int ans = 1e9;		
		seg now;		
		if (K) {
			now = base;
			now.first = max(now.first, tmp[0].first.first);
			now.second = min(now.second, tmp[0].first.second);
			ans = min(ans, now.first - now.second);		
			
			//cout << "ans" << now.first << ' ' << now.second << endl;
			
			now = base;
			now.first = max(now.first, tmp[K - 1].second.first);
			now.second = min(now.second, tmp[K - 1].second.second);
			
			ans = min(ans, now.first - now.second);		
		} else {
			ans = min(ans, base.first - base.second);
		}
		

		
		for (int i = 1; i < K; i++) {
			now = base;
			now.first = max(now.first, tmp[i - 1].second.first);
			now.second = min(now.second, tmp[i - 1].second.second);
			now.first = max(now.first, tmp[i].first.first);
			now.second = min(now.second, tmp[i].first.second);
			ans = min(ans, now.first - now.second);
		}
		printf("Case %d: %d\n", t, ans);
	}
}

/*
3
3 1
1 2
1 2
3 4
5 6
4 3
1 2
2 3
1 3
1 2 3 4 5 6 7 8
2 0
2 1 3 5
*/

