#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 64;

ll w[maxn], v[maxn];

vector<pair<ll, pair<ll, int> > >s1, s2;

multiset<pair<ll, int> >st;

int main() {
	freopen("dowry.in", "r", stdin);
	freopen("dowry.out", "w", stdout);
	int n; cin >> n;
	ll L, R; cin >> L >> R;
	for (int i = 0; i < n; i++) 
		cin >> w[i] >> v[i];		
	int m = n / 2;
	
	for (int i = 0; i < 1 << m; i++) {
		ll W = 0, V = 0;
		for (int j = 0; j < m; j++) {
			if ((i >> j) & 1) 
				W += w[j], V += v[j];
		}
		s1.push_back(make_pair(W, make_pair(V, i)));
	}
	
	int t = n - m;
	
	for (int i = 0; i < 1 << t; i++) {
		ll W = 0, V = 0;
		for (int j = m; j < n; j++) {
			if ((i >> (j - m)) & 1) 
				W += w[j], V += v[j];
		}
		s2.push_back(make_pair(W, make_pair(V, i)));
	}
	
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	int p1 = (int)s2.size() - 1, p2 = (int)s2.size() - 1;
	
	ll ans = -1; int how;
	
	for (auto s : s1) {
		ll W = s.first, V = s.second.first;
		int S = s.second.second;
		ll _L = L - W, _R = R - W;
		while (p1 >= 0 && _L <= s2[p1].first) {
			st.insert(s2[p1--].second);
		}
		while (p2 >= 0 && _R < s2[p2].first) {
			st.erase(st.find(s2[p2--].second));
		}
		if (st.size() && ans < V + st.rbegin()->first) {
			ans = V + st.rbegin()->first;
			how = S + (st.rbegin()->second << m);
		}
	}
	
	if (ans == -1) {
		cout << 0 << endl;
	} else {
		int cnt = 0;
		for (int i = 0; i < n; i++)	
			if ((how >> i) & 1) cnt++;
		cout << cnt << endl;
		for (int i = 0; i < n; i++)	
			if ((how >> i) & 1) cout << (i + 1) << ' ';
		cout << endl;
	}
	return 0;	
}
