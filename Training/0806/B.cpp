#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10;

namespace SEG1 {
	int val[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lm ((l + r) >> 1)
#define rm (lm + 1)
	void build(int p, int l, int r) {
		val[p] = 0;
		if (l == r) return;
		else 
			build(ls, l, lm),
			build(rs, rm, r);
	}
	void pushup(int p) {
		val[p] = max(val[ls], val[rs]);
	}
	void update(int p, int l, int r, int x, int v) {
		if (l == r) 
			val[p] = max(val[p], v);
		else {
			if (x <= lm) update(ls, l, lm, x, v);
			else update(rs, rm, r, x, v);
			pushup(p);
		}
	}
	int ask(int p, int l, int r, int L, int R) {
		if (l == L && r == R) return val[p];
		else {
			if (R <= lm) return ask(ls, l, lm, L, R);
			else if (L > lm) return ask(rs, rm, r, L, R);
			else return max(
				ask(ls, l, lm, L, lm),
				ask(rs, rm, r, rm, R)
			);
		}
	}
}

namespace SEG2 {
	int val[maxn << 2];
#define ls p << 1
#define rs p << 1 | 1
#define lm ((l + r) >> 1)
#define rm (lm + 1)
	void build(int p, int l, int r) {
		val[p] = 0;
		if (l == r) return;
		else 
			build(ls, l, lm),
			build(rs, rm, r);
	}
	void pushup(int p) {
		val[p] = max(val[ls], val[rs]);
	}
	void update(int p, int l, int r, int x, int v) {
		if (l == r) 
			val[p] = max(val[p], v);
		else {
			if (x <= lm) update(ls, l, lm, x, v);
			else update(rs, rm, r, x, v);
			pushup(p);
		}
	}
	int ask(int p, int l, int r, int L, int R) {
		if (l == L && r == R) return val[p];
		else {
			if (R <= lm) return ask(ls, l, lm, L, R);
			else if (L > lm) return ask(rs, rm, r, L, R);
			else return max(
				ask(ls, l, lm, L, lm),
				ask(rs, rm, r, rm, R)
			);
		}
	}
}

int a[maxn], v[maxn];

int f[2][maxn];
vector<pair<bool, int> > rf[maxn];

void work(int n) {
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), v[i] = a[i];
	sort(v + 1, v + 1 + n);
	int m = unique(v + 1, v + 1 + n) - v - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(v + 1, v + 1 + m, a[i]) - v;
	
	SEG1::build(1, 0, m + 1);
	SEG2::build(1, 0, m + 1);
	
	reverse(a + 1, a + 1 + n);
	for (int i = 1; i <= n; i++) {
		f[0][i] = SEG1::ask(1, 0, m + 1, 0, a[i] - 1) + 1;
		f[1][i] = SEG2::ask(1, 0, m + 1, a[i] + 1, m + 1) + 1;
		f[1][i] = max(f[0][i], f[1][i]);
		SEG1::update(1, 0, m + 1, a[i], f[0][i]);
		SEG2::update(1, 0, m + 1, a[i], f[1][i]);
	}
	
	
	reverse(f[0] + 1, f[0] + 1 + n);
	reverse(f[1] + 1, f[1] + 1 + n);
	reverse(a + 1, a + 1 + n);
	/*
	for (int i = 1; i <= n; i++) {
		printf("f[%d][%d] = %d\n", 0, i, f[0][i]);
		printf("f[%d][%d] = %d\n", 1, i, f[1][i]);
	}
	*/
	
	int ans = 0;
	
	for (int i = 1; i <= n; i++) 
		ans = max(ans, f[1][i]);
	
	for (int i = 1; i <= ans; i++) rf[i].clear();
	for (int i = 1; i <= n; i++) 
		rf[f[0][i]].push_back(make_pair(0, i)),
		rf[f[1][i]].push_back(make_pair(1, i));
	
	pair<bool, int> sta = make_pair(1, 0);
	
	for (int len = ans; len > 0; len--) {
		pair<bool, int> nxt(0, 0);
		for (auto tmp : rf[len]) {
			if (!tmp.first && !sta.first && (a[tmp.second] >= a[sta.second])) continue;
			if (!tmp.first &&  sta.first && (a[tmp.second] >= a[sta.second])) continue;
			if ( tmp.first && !sta.first) continue;
			if ( tmp.first &&  sta.first && (a[tmp.second] <= a[sta.second])) continue;
			
			if (tmp.first > sta.first) continue;
			if (tmp.second <= sta.second) continue;
			if (nxt.second == 0) nxt = tmp;
			else if (tmp.second < nxt.second) 
				nxt = tmp;
			else if (tmp.second == nxt.second)
				nxt.first = max(nxt.first, tmp.first);
		}
		printf("%d%c", nxt.second, " \n"[len == 1]);
		sta = nxt;
	}
	
	sta = make_pair(1, 0);
	
	for (int len = ans; len > 0; len--) {
		pair<bool, int> nxt(0, 0);
		for (auto tmp : rf[len]) {
			if (!tmp.first && !sta.first && (a[tmp.second] >= a[sta.second])) continue;
			if (!tmp.first &&  sta.first && (a[tmp.second] >= a[sta.second])) continue;
			if ( tmp.first && !sta.first) continue;
			if ( tmp.first &&  sta.first && (a[tmp.second] <= a[sta.second])) continue;
			
			if (tmp.first > sta.first) continue;
			if (tmp.second <= sta.second) continue;
			if (nxt.second == 0) nxt = tmp;
			else if (tmp.second > nxt.second) 
				nxt = tmp;
			else if (tmp.second == nxt.second)
				nxt.first = max(nxt.first, tmp.first);
		}
		printf("%d%c", nxt.second, " \n"[len == 1]);
		sta = nxt;
	}
}

int main() {
	int n; 
	while (scanf("%d", &n) != EOF) 
		work(n);
	return 0;
}
