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
std::stack<int>stk;

void work() {
	ans = 0;
	int n; scanf("%d", &n); 
	ss[0] = 0;
	for (int i = 1; i <= n; i++) scanf("%d", &s[i]), ss[++ss[0]] = s[i];
	std::sort(ss + 1, ss + 1 + ss[0]);
	ss[0] = std::unique(ss + 1, ss + 1 + ss[0]) - ss - 1;
	for (int i = 1; i <= n; i++) s[i] = std::lower_bound(ss + 1, ss + 1 + ss[0], s[i]) - ss;
	build(n, ss[0]);
	
	//std::cout << ans << std::endl;
	
	while (stk.size()) stk.pop();
	long long sum = 0;
	for (int i = n; i >= 1; i--) {
		int v = ss[s[i]];
		while (stk.size() && ss[s[stk.top()]] < v) {
			int pos = stk.top(); stk.pop();
			int nxt = stk.size() ? stk.top() : n + 1;
			sum -= 1ll * (nxt - pos) * ss[s[pos]];
		} 
		int nxt = stk.size() ? stk.top() : n + 1;
		sum += 1ll * (nxt - i) * v; stk.push(i);
		ans += sum;
	}
	
	int k = 0;
	long long nowsum = 0;
	for (int i = 2; i <= n; i++) {
		int p = sa[i];
		while (height[i] < k) {
			nowsum -= premax[k];
			k--;
		}
		while (height[i] > k) {
			k++;
			premax[k] = std::max(premax[k - 1], ss[s[p + k - 1]]);
			nowsum += premax[k];
		}
		ans -= nowsum;
	}
	printf("%lld\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}

