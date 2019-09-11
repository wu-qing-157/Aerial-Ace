#include <bits/stdc++.h>
using namespace std;


const int maxn = 6e5 + 10;

int n;

namespace SA1 {
	char s[maxn];
	int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
	int st[20][maxn], log_2[maxn];
	inline void build(int m) {
		memset(height, 0, sizeof height);
		memset(rank, 0, sizeof rank);
		memset(cnt, 0, sizeof cnt);
		memset(sa, 0, sizeof sa);
		memset(wa, 0, sizeof wa);
		memset(wb, 0, sizeof wb);
		int *x = wa, *y = wb, *t;
		for (int i = 1; i <= n; i++) cnt[x[i] = s[i] - 'a' + 1]++;
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
		for (int i = 1, j, k = 0; i <= n; height[rank[i++]] = k)
			for (k ? --k : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k);
		
		for (int i = 1; i <= n; i++) st[0][i] = height[i];
		for (int j = 1; j < 20; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		log_2[0] = -1;
		for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
	}
	int lcp(int p1, int p2) {
		if (p1 > n || p2 > n) return 0;
		p1 = rank[p1], p2 = rank[p2];
		if (p1 == p2) return n - sa[p1] + 1;
		if (p1 > p2) swap(p1, p2);
		p1++;
		int k = log_2[p2 - p1 + 1];
		return min(st[k][p1], st[k][p2 - (1 << k) + 1]);
	}
}

namespace SA2 {
	char s[maxn];
	int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
	int st[20][maxn], log_2[maxn];
	inline void build(int m) {
		memset(height, 0, sizeof height);
		memset(rank, 0, sizeof rank);
		memset(cnt, 0, sizeof cnt);
		memset(sa, 0, sizeof sa);
		memset(wa, 0, sizeof wa);
		memset(wb, 0, sizeof wb);
		int *x = wa, *y = wb, *t;
		for (int i = 1; i <= n; i++) cnt[x[i] = s[i] - 'a' + 1]++;
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
		for (int i = 1, j, k = 0; i <= n; height[rank[i++]] = k)
			for (k ? --k : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k);
		
		for (int i = 1; i <= n; i++) st[0][i] = height[i];
		for (int j = 1; j < 20; j++)
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		log_2[0] = -1;
		for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
	}
	int lcp(int p1, int p2) {
		if (p1 > n || p2 > n) return 0;
		p1 = n - p1 + 1;
		p2 = n - p2 + 1;
		p1 = rank[p1], p2 = rank[p2];
		if (p1 == p2) return n - sa[p1] + 1;
		if (p1 > p2) swap(p1, p2);
		p1++;
		int k = log_2[p2 - p1 + 1];
		return min(st[k][p1], st[k][p2 - (1 << k) + 1]);
	}
}

char s[maxn];

bool check(int l, int r, int len, int k) {
	int lcp = SA1::lcp(l, l + len);
	if (lcp + l + len - 1 < r) return false;
	return true;
}

void work() {
	int k; scanf("%d", &k);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	
	for (int i = 1; i <= n; i++) SA1::s[i] = s[i];
	for (int i = 1; i <= n; i++) SA2::s[i] = s[n - i + 1];
	
	SA1::s[n + 1] = SA2::s[n + 1] = 0;
	
	SA1::build(26);
	SA2::build(26);
	
	long long ans = 0;
	
	for (int len = 1; len <= n / k; len++) {
		for (int L = 1, R = len; L + len * k - 1 <= n; L += len, R = min(n, L + len - 1)) {	
			if (!check(R + 1, R + (k - 1) * len, len, k)) continue;
			int lcp = SA1::lcp(R + 1, R + 1 + (k - 1) * len);
			int lcs = SA2::lcp(R, R + (k - 1) * len);
			lcp = min(lcp, len - 1);
			lcs = min(lcs, len);
			ans += max(0, lcp + lcs + 1 - len);
			//cout << L << ' ' << R << ' ' << lcp << ' ' << lcs << ' ' << ans << endl;
		}
		//cout << ans << endl;
	}
	printf("%lld\n", ans);
	/*
	ans = 0;
	
	for (int L = 1; L <= n; L++)
		for (int R = L; R <= n; R++) {
			if ((R - L + 1) % k != 0) continue;
			int len = (R - L + 1) / k;
			bool ok = true;
			for (int i = 2; i <= k; i++) 
				for (int p = 1; p <= len; p++) 
					if (s[L + p - 1] != s[L + (i - 1) * len + p - 1]) ok = false;
			if (ok) ans++;
		}
	printf("%lld\n", ans);
	*/
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
