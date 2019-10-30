#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn], id[maxn];

bool cmp(int x, int y) {
	return a[x] < a[y];
}

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

int L[maxn], R[maxn];

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]), id[i] = i;
	sort(id + 1, id + 1 + n, cmp);
	
	bit.clear();
	for (int i = 1; i <= n; i++) 
		bit.add(a[i], 1), L[i] = bit.ask(a[i] + 1);

	bit.clear();
	for (int i = n; i >= 1; i--)
		bit.add(a[i], 1), R[i] = bit.ask(a[i] + 1);
	
	long long ans = 0;
	for (int i = 1; i <= n; i++)
		ans += min(L[i], R[i]);
	
	printf("%lld\n", ans);
	return 0;
}
