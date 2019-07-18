#include <bits/stdc++.h>

using number = long double;

std::vector<std::pair<number, number>> a, b, c, d;
std::vector<std::pair<std::pair<number, number>, std::pair<number, number>>> f;
const number eps = 1e-9;

int sign(number x) {
	return (x > eps) - (x < -eps);
}

int main() {
	freopen("superposition.in", "r", stdin);
	freopen("superposition.out", "w", stdout);
    {
        scanf("%d", &n), n--;
        if (n == 0) {
            double x;
            scanf("%lf", &x);
            a.emplace_back(-INF, x);
            a.emplace_back(INF, x);
        } else {
            for (int i = 1; i <= n; i++) {
                double x, y;
                scanf("%lf%lf", &x, &y);
                if (i == 1) b.emplace_back(-INF, y);
                a.emplace_back(x, y);
                if (i 
            }
        }
        scanf("%d", &m), m--;
        if (m == 0) {
            m = 1;
            number x = 0, y; scanf("%lf", &y);
            b.emplace_back(x, y);
        } else {
            for (int i = 1; i <= m; i++) {
                number x, y;
                scanf("%lf%lf", &x, &y);
                if (i == 1) b.emplace_back(-INF, y);
                b.emplace_back(x, y);
                if (i == m) b.emplace_back(INF, y);
            }
        }
    }
	
	for (auto f : a) {
		if (f.second <= b[0].first) 
			c.emplace_back(f.first, b[0].second);
		else if (f.second >= b[m - 1].first) 
			c.emplace_back(f.first, b[m - 1].second);
		else {
			for (int i = 1; i < b.size(); i++) 
				if (f.second >= b[i - 1].first) {
				/*
				double k = (b[i].second - b[i - 1].second) / (b[i].first - b[i - 1].first);
				c.emplace_back(f.first, b[i - 1].second + (f.second - b[i - 1].first) * k));
				*/
				c.emplace_back(f.first, b[i - 1].second + (f.second - b[i - 1].first) * (b[i].second - b[i - 1].second) / (b[i].first - b[i - 1].first));
				break;
			}
		}
	}
	for (auto g : b) {
		for (int i = 1; i < a.size(); i++) {
			if (g.first > max(a[i].second, a[i - 1].second)) continue;
			if (g.first < min(a[i].second, a[i - 1].second)) continue;
			/*
			double k = (a[i].second - a[i - 1].second) / (a[i].first - a[i - 1].first);
			if (k == 0) continue;
			c.emplace_back(a[i - 1].first + (g.first - a[i - 1].second) / k, g.second));
			*/
			if (sign(a[i].second - a[i - 1].second) == 0) continue;
			c.emplace_back(a[i - 1].first + (g.first - a[i - 1].second) * (a[i].first - a[i - 1].first) / (a[i].second - a[i - 1].second), g.second);
		}
	}
	
	//for (auto h : c)
	//	cout << h.first << ' ' << h.second << endl;
	
	sort(c.begin(), c.end());
	c.erase(unique(c.begin(), c.end(), [](auto a, auto b) { return sign(a.first - b.first) == 0 && sign(a.second - b.second) == 0; }), c.end());
	d.push_back(c[0]);
	for (int i = 1; i < c.size() - 1; i++) {
		number x1 = c[i - 1].first - c[i].first;
		number x2 = c[i + 1].first - c[i].first;
		number y1 = c[i - 1].second - c[i].second;
		number y2 = c[i + 1].second - c[i].second;
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
