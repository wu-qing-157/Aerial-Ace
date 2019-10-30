#include <bits/stdc++.h>
using namespace std;

unordered_set<int>ap;
const int maxn = 5e3 + 10;

int a[maxn];

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]), ap.insert(a[i]);
	sort(a + 1, a + 1 + n);
	int ans = 2;
	for (int i = 1; i <= n; i++) 
		for (int j = i + 1; j <= n; j++) {
			int d = a[j] - a[i], now = 2, val = a[j];
			while (ap.find(val + d) != ap.end()) 
				now++, val += d;
			ans = max(ans, now);
		}
	printf("%d\n", ans);
}
