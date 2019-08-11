#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e4 + 10;

pair<int, int> x[maxn], y[maxn];

int p[maxn];

int main() {
	int T = 5;
	cout << T << endl;
	while (T--) {
		int n = 5e4;
		cout << n << endl;
		for (int i = 1; i <= n; i++) x[i] = y[i] = make_pair(rand(), rand());
		sort(y + 1, y + 1 + n);
		for (int i = 1; i <= n; i++) p[i] = lower_bound(y + 1, y + 1 + n, x[i]) - y;
		for (int i = 1; i <= n; i++) printf("%d ", p[i]);
		
		for (int i = 1; i <= n; i++) x[i] = y[i] = make_pair(rand(), rand());
		sort(y + 1, y + 1 + n);
		for (int i = 1; i <= n; i++) p[i] = lower_bound(y + 1, y + 1 + n, x[i]) - y;		
		
		for (int i = 1; i <= n; i++) printf("%d ", p[i]);
	}
	return 0;
}
