#include <bits/stdc++.h>
using namespace std;

void work() {
	int n, m; cin >> n >> m;
	int x, y; cin >> x >> y;
	int ans = n * (x + y) - m;
	if (ans <= 0) {
		puts("0");
	}
	else if (y == 0) {
		 puts("-1");
	} else {
		cout << ans << endl;
	}
}

int main() {
	freopen("mosalah.in", "r", stdin);
	int T; cin >> T;
	for (int t = 1; t <= T; t++) {
		work();
	}
	return 0;
}
