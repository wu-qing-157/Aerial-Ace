#include <bits/stdc++.h>

const int maxn = 1e6 + 10;

int s[maxn], ss[maxn];
int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];

long long ans;

int premax[maxn], nowsum;

inline void build(int n, int m) {
	int *x = wa, *y = wb, *t;
	memset(cnt + 1, 0, m << 2);
	for (int i = 1; i <= n; i++) cnt[x[i] = s[i]]++;
	for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
	for (int i = n; i; --i) sa[cnt[x[i]]--] = i;
	
	for (int j = 1; j < n || (j == 1 && m < n); j <<= 1, t = x, x = y, y = t) {
		memset(cnt + 1, 0, m << 2);
		int p = 0;
		for (int i = n - j + 1; i <= n; i++) y[++p] = i;
		for (int i = 1; i <= n; i++) {
			++cnt[x[i]];
			sa[i] > j ? y[++p] = sa[i] - j : 0;
		}
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (int i = n; i; --i) sa[cnt[x[y[i]]]--] = y[i];
			m = 0;
		for (int i = 1; i <= n; i++) 
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	//nowsum = 0;
	for (int i = 1, j, k = 0; i <= n; height[rank[i++]] = k) {
		if (k > 0) {
		//	nowsum -= premax[k];
			k--;
		}
		for (j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k) {
		//	premax[k + 1] = std::max(premax[k], ss[s[i + k]]);
		//	nowsum += premax[k + 1];
		}
		//ans -= nowsum;
	}
}
int st[maxn];
long long suf[maxn];
void work() {
	ans = 0;
	int n; scanf("%d", &n);
	ss[0] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &s[i]), ss[++ss[0]] = s[i];
	s[n + 1] = 0;
	std::sort(ss + 1, ss + 1 + ss[0]);
	ss[0] = std::unique(ss + 1, ss + 1 + ss[0]) - ss - 1;
	for (int i = 1; i <= n; i++) s[i] = std::lower_bound(ss + 1, ss + 1 + ss[0], s[i]) - ss;
	build(n, ss[0]);
	
	int top = 0;
	st[++top] = n + 1;
	long long sum = 0;
	for (int i = n; i >= 1; i--) {
		int v = s[i];
		while (top > 1 && s[st[top]] < v) {
			int pos = st[top--];
			int nxt = st[top];
			sum -= 1ll * (nxt - pos) * ss[s[pos]];
		}
		int nxt = st[top];
		sum += 1ll * (nxt - i) * ss[v];
		st[++top] = i;
		suf[top] = sum;
		
		
		// for (int i = 1; i <= top; ++i) printf("%d ", st[i]); puts("");
		int pp = std::upper_bound(st + 1, st + top + 1, i + height[rank[i]], std::greater<int>()) - st - 1;
		// printf("pp = %d\n", pp);
		
		ans += suf[pp] + 1ll * (st[pp] - (i + height[rank[i]])) * ss[s[st[pp + 1]]];
	}
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
/*
3
3
1 2 3
3
2 3 3
3
3 1 3
*/

