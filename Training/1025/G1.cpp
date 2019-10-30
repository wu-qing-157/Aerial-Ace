#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];

struct BIT {
	int s[maxn];
	void add(int p, int v) {
		while (p)
			s[p] += v, p -= p & -p;
	}
	int ask(int p, int v = 0) {	
		while (p < maxn)
			v += s[p], p += p & -p;
		return v;
	}
	void clear() { memset(s, 0, sizeof s); }
} bit;

long long L[maxn], R[maxn];

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	int p = 1;
	for (int i = 2; i <= n; i++) 
		if (a[i] > a[p]) p = i;
	bit.clear();
	for (int i = 1; i <= n; i++) {
		L[i] = 0;
		if (i != p) {
			bit.add(a[i], 1);
			L[i] = bit.ask(a[i] + 1);
		}
		L[i] += L[i - 1];
	}
	bit.clear();
	for (int i = n; i >= 1; i--) {
		R[i] = 0;
		if (i != p) {
			bit.add(a[i], 1);
			R[i] = bit.ask(a[i] + 1);
		}
		R[i] += R[i + 1];
	}
	long long ans = n * n;	
	for (int q = 1; q <= n; q++) {	
		if (p == q) 
			ans = min(ans, L[q - 1] + R[q + 1]);
		else if (q < p) 
			ans = min(ans, L[q - 1] + R[q] + p - q);
		else if (q > p)
			ans = min(ans, L[q] + R[q + 1] + q - p);
	}
	printf("%lld\n", ans);
}
