#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 10;

char s[maxn], t[maxn];

vector<int>w[26];

char mx[maxn << 2];

void build(int p, int l, int r) {
	if (l == r) mx[p] = s[l];
	else {
		int mid = l + r >> 1;
		build(p << 1, l, mid);
		build(p << 1 | 1, mid + 1, r);
		mx[p] = max(mx[p << 1], mx[p << 1 | 1]);
	}
}

int ask(int p, int l, int r, int x, char c) {
	if (x <= l && mx[p] <= c) return -1;
	if (l == r) return s[l] > c ? l : -1;
	else {
		int mid = l + r >> 1;
		if (mid < x) return ask(p << 1 | 1, mid + 1, r, x, c);
		else {
			int tmp = ask(p << 1, l, mid, x, c);
			if (tmp != -1) return tmp;
			return ask(p << 1 | 1, mid + 1, r, x, c);
		}
	}
}

int main() {
	int n, m; scanf("%d%d", &n, &m);
	scanf("%s", s + 1);
	scanf("%s", t + 1);
	int ans = -1;
	
	for (int i = 1; i <= n; i++) 
		w[s[i] - 'a'].push_back(i);
	
	for (int i = 0; i < 26; i++) w[i].push_back(n * 2);
	
	build(1, 1, n);
	int l = 1;
	for (int i = 1; i <= m; i++) {
		int tmp = ask(1, 1, n, l, t[i]);
		if (tmp != -1)
			ans = max(ans, i - 1 + n - tmp + 1);
		l = *lower_bound(w[t[i] - 'a'].begin(), w[t[i] - 'a'].end(), l) + 1;
		if (l > n) break;
	}
	
	if (l <= n) {
		int tmp = ask(1, 1, n, l, t[m + 1]);
		if (tmp != -1)
			ans = max(ans, m + n - tmp + 1);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
