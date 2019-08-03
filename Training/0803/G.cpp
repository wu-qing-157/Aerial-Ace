#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

typedef long long ll;

int a[maxn], b[maxn], c[maxn], d[maxn];


int p[maxn], n, m;
typedef pair<int, int> pii;
pii tmp[maxn];
vector<pii> R_pos[maxn * 2];
priority_queue<pii, vector<pii>, greater<pii> >pq;

ll calc() {
	m = 0;
	for (int i = 1; i <= n; i++) 
		p[++m] = tmp[i].first, p[++m] = tmp[i].second;
	
	sort(p + 1, p + 1 + m);
	m = int(unique(p + 1, p + 1 + m) - p - 1);
	//cout << "m = " << m << endl;
	for (int i = 1; i <= m; i++) R_pos[i].clear();
	
	for (int i = 1; i <= n; i++) {
		int x = int(lower_bound(p + 1, p + 1 + m, tmp[i].first) - p);
		int y = int(lower_bound(p + 1, p + 1 + m, tmp[i].second) - p);
		R_pos[x].emplace_back(y, i);
	}
	
	ll ans = -1;
	int cntL = 0, cntR = n;		
	ll sumL = 0, sumR = 0;
	for (int i = 1; i <= n; i++) 
		sumR += tmp[i].first;
	
	while (pq.size()) pq.pop();
	
	for (int i = 1; i <= m; i++) {
		while (pq.size() && pq.top().first < i) 
			cntL++, sumL += tmp[pq.top().second].second, pq.pop();
		for (auto R : R_pos[i]) 
			pq.push(R), cntR--, sumR -= tmp[R.second].first;
		ll now = (1ll * p[i] * cntL - sumL) 
				+ (sumR - 1ll * p[i] * cntR);
		//cout << "now = " << now << endl;
		ans = (ans == -1 || ans > now) ? now : ans;
	}
	return ans;
}

void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
	for (int i = 1; i <= n; i++)
		tmp[i] = make_pair(a[i], c[i]);
	ll ans = calc();
	//cout << ans << endl;
	for (int i = 1; i <= n; i++)
		tmp[i] = make_pair(b[i], d[i]);
	ans += calc();
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
/*
1
2
2 2 3 3 
4 4 5 5
*/
