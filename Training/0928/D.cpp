#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e2 + 10;

vector<pair<int, int> >swp[maxn * 2], iswp[maxn * 2];

int a[maxn], b[maxn];

int main() {
	freopen("bubble.in", "r", stdin);
	freopen("bubble.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int p = n - i;
		for (int j = 1; j <= i; j++) {
			int x = i, y = i + 1;
			int z; scanf("%d", &z);
			if (z == 1)			
				swp[p].push_back(make_pair(x, y));
			else 
				iswp[p].push_back(make_pair(x, y));
			p += 2;
		}
	}
	
	for (int i = 1; i <= n; i++) a[i] = i;
	
	for (int p = 1; p <= n * 2 - 1; p++) {
		for (auto s : swp[p]) {
			int x = s.first, y = s.second;
			swap(a[x], a[y]);
		}
	}
	
	for (int i = 1; i <= n; i++) b[a[i]] = i;
	
	bool ok = true;
	
	for (int p = 1; p <= n * 2 - 1; p++) {
		for (auto s : iswp[p]) {
			int x = s.first, y = s.second;
			if (b[x] > b[y]) ok = false;
		}
		for (auto s : swp[p]) {
			int x = s.first, y = s.second;
			if (b[x] < b[y]) ok = false;
			swap(b[x], b[y]);
		}
	}
	for (int i = 1; i <= n; i++) b[a[i]] = i;
	if (ok) {
		puts("YES");
		for (int i = 1; i <= n; i++) 	
			printf("%d%c", b[i], " \n"[i == n]);
	} else puts("NO");
	

}
