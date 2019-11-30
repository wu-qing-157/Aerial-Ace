#include <bits/stdc++.h>
using namespace std;

int c[20];
long double p[20];

void work() {
	int n; cin >> n; 
	for (int i = 1; i <= n; i++) 
		cin >> c[i] >> p[i];
	if (n == 1) return void(printf("1.000000\n"));
	for (int i = 1; i <= n; i++) {
		long double ans = 0;
		for (int k = 1; k <= 1000; k++) {
			long double pi = 1 - pow(1 - pow(p[i], k), c[i]);
			long double pj1 = 1, pj2 = 1;
			for (int j = 1; j <= n; j++) if (i != j) 
				pj1 *= pow(1 - pow(p[j], k), c[j]),
				pj2 *= pow(1 - pow(p[j], k - 1), c[j]);
			ans += pi * (pj1 - pj2);
		}
		printf("%.6lf%c", (double)ans, " \n"[i == n]);
	}
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
