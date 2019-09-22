#include <bits/stdc++.h>
using namespace std;

void calc(int x) {
	vector<int>lis;
	for (int i = 2; i * i <= x; i++) if (x % i == 0) {
		while (x % i == 0) {
			x /= i;
			lis.push_back(i);
		}
	}
	if (x != 1) lis.push(x);
	for (auto e : lis) {
		if ()
	}
}

void work() {
	int a, b, c;
	scanf("%d%d%d", &a, &b, &c);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
