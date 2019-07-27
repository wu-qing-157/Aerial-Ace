#include <bits/stdc++.h>
using namespace std;

char s[20], t[20];

int calc(int n) {
	if (n == 0) return 0;
	int ans = n;
	for (int i = n; i >= 1; i--) {
		if (n % i != 0) continue;
		int c = n / i;
		bool ok = true;
		for (int j = 0; j < i && ok; j++) {
			for (int k = 1; k < c; k++) {
				if (t[j] != t[j + k * i]) {
					ok = false;
					break;
				}
			}
		}
		if (ok) ans = min(ans, i);
	}
	return ans;
}

void work() {
	scanf("%s", s);
	int n = strlen(s);
	int ans = n;
	for (int i = 0; i < 1 << n; i++) {
		int m = 0, now = 0;
		for (int j = 0; j < n; j++) 
			if ((i >> j) & 1) 
				t[m++] = s[j];
		now += calc(m);
		m = 0;
		for (int j = 0; j < n; j++) 
			if (!((i >> j) & 1)) 
				t[m++] = s[j];
		now += calc(m);
		ans = min(ans, now);
	}
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		work();	
	}
	return 0;
}
