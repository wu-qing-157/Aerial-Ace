#include <bits/stdc++.h>
using namespace std;
 
vector<pair<double, double> >a, b, c, d;
const double eps = 1e-12;
 
int sign(double x) {
	return (x > eps) - (x < -eps);
}
 
int main() {
	freopen("superposition.in", "r", stdin);
	freopen("superposition.out", "w", stdout);
	int n; scanf("%d", &n); n--;
	if (n == 0) {
		n = 1;
		double x = 0, y; scanf("%lf", &y);
		a.push_back(make_pair(x, y));
	} else for (int i = 1; i <= n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		a.push_back(make_pair(x, y));
	}
	int m; scanf("%d", &m); m--;
	if (m == 0) {
		m = 1;
		double x = 0, y; scanf("%lf", &y);
		b.push_back(make_pair(x, y));
	} else for (int i = 1; i <= m; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		b.push_back(make_pair(x, y));
	}
	
	for (auto f : a) {
		if (f.second <= b[0].first) 
			c.push_back(make_pair(f.first, b[0].second));
		else if (f.second >= b[m - 1].first) 
			c.push_back(make_pair(f.first, b[m - 1].second));
		else {
			for (int i = 1; i < b.size(); i++) 
				if (f.second >= b[i - 1].first && f.second <= b[i].first) {
				double k = (b[i].second - b[i - 1].second) / (b[i].first - b[i - 1].first);
				c.push_back(make_pair(f.first, b[i - 1].second + (f.second - b[i - 1].first) * k));
				break;
			}
		}
	}
	for (auto g : b) {
		for (int i = 1; i < a.size(); i++) {
			if (g.first > max(a[i].second, a[i - 1].second)) continue;
			if (g.first < min(a[i].second, a[i - 1].second)) continue;
			double k = (a[i].second - a[i - 1].second) / (a[i].first - a[i - 1].first);
			if (k == 0) continue;
			c.push_back(make_pair(a[i - 1].first + (g.first - a[i - 1].second) / k, g.second));
		}
	}
	
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end()), c.end());
	d.push_back(c[0]);
	for (int i = 1; i < c.size() - 1; i++) {
		double x1 = c[i - 1].first - c[i].first;
		double x2 = c[i + 1].first - c[i].first;
		double y1 = c[i - 1].second - c[i].second;
		double y2 = c[i + 1].second - c[i].second;
		if (sign(x1 * y2 - x2 * y1) == 0) continue;
		else d.push_back(c[i]);
	}
	d.push_back(c[c.size() - 1]);	
	while (d.size() > 1 && sign(d[d.size() - 1].second - d[d.size() - 2].second) == 0) d.pop_back();
	reverse(d.begin(), d.end());
	while (d.size() > 1 && sign(d[d.size() - 1].second - d[d.size() - 2].second) == 0) d.pop_back();
	reverse(d.begin(), d.end());
	
	if (d.size() == 1) {
		printf("%d\n%.10f\n", (int)d.size(), d[0].second);
	} else {
		cout << d.size() + 1 << endl;
		for (auto h : d)
			printf("%.10f %.10f\n", h.first, h.second);
	}
	return 0;
}
/*
11
0 3
6 20
8 67
10 16
29 42
34 47
40 84
78 29
87 37
93 33
11
0 48
2 88
3 78
16 49
17 83
30 14
32 50
66 59
89 78
98 77
*/