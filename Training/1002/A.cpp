#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int> >p;

int main() {
	int n, m, t = 0; 
	scanf("%d", &t); t = 0;
	while( scanf("%d%d", &n, &m) != EOF) {
		p.clear();
		for (int i = 0; i < n; i++) {
			int d; scanf("%d", &d);
			p.push_back(make_pair(d, 0));
		}
		for (int i = 0; i < n; i++)
			scanf("%d", &p[i].second);
		sort(p.begin(), p.end());
		int ans = 0;
		while (true) {
			if (ans < n && m >= p[ans].second)
				m -= p[ans].second, ans++;
			else break;
		}
		printf("Case %d: %d\n", ++t, ans);
	}
	return 0;
}
/*
13 300
52 55 82 11 62 79 38 8 58 28 1 70 32
27 62 45 77 22 69 34 43 21 43 85 22 36
*/
