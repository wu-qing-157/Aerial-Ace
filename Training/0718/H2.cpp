#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

char s[maxn];
int sa[maxn], rnk[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
int st[20][maxn], log_2[maxn];
inline void build1(int n, int m) {
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
		for (int i = 1; i <= n; ++i) 
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	for (int i = 1; i <= n; i++) rnk[sa[i]] = i;
	for (int i = 1, j, k = 0; i <= n; height[rnk[i++]] = k)
		for (k ? --k : 0, j = sa[rnk[i] - 1]; s[i + k] == s[j + k]; ++k);
	
	for (int i = 1; i <= n; i++) st[0][i] = height[i];
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << (j - 1)) <= n; i++)
			st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	
	log_2[0] = -1;
	for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
}
int n;

int lcp(int x, int y) {
	if (x > y) swap(x, y);
	if (x == y) return n - sa[x] + 1;
	else {
		x++;  int k = log_2[y - x + 1];
		return min(st[k][x], st[k][y - (1 << k) + 1]);
	}
}

int st1[20][maxn], st2[20][maxn];

void build2() {
	for (int i = 1; i <= n; i++) 
		st1[0][i] = st2[0][i] = sa[i];
	
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << (j - 1)) <= n; i++) {
			st1[j][i] = min(st1[j - 1][i], st1[j - 1][i + (1 << (j - 1))]);
			st2[j][i] = max(st1[j - 1][i], st2[j - 1][i + (1 << (j - 1))]);
		}
}

int getmin(int l, int r) {
	int k = log_2[(r - l + 1)];
	return min(st1[k][l], st1[k][r - (1 << k) + 1]);
}

int getmax(int l, int r) {
	int k = log_2[(r - l + 1)];
	return max(st2[k][l], st2[k][r - (1 << k) + 1]);
}

bool check1(int i, int len) {
	int l = i, r = n;
	while (l < r) {
		int mid = ((l + r) >> 1) + 1;
		if (lcp(i, mid) >= len) 
			l = mid;
		else 
			r = mid - 1;
	}
	//cout << i << ' ' << l << ' ' << len << endl;
	
	if (l == i) return false;
	//cout << "#" << getmin(i + 1, l) << ' ' << getmax(i + 1, l) << endl;
	if (getmin(i + 1, l) + len - 1 < sa[i]) return true;
	if (getmax(i + 1, l) > sa[i] + len - 1) return true;
	return false;
}



int main() {
	freopen("seti.in", "r", stdin);
	freopen("seti.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	build1(n, 26);	
	build2();
	//cout << "GG" << endl;
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		int p = sa[i];
		int l = height[i], r = n - sa[i] + 1;
		while (l < r) {
			int mid = ((l + r) >> 1) + 1;
			if (check1(i, mid)) 
				l = mid;
			else 
				r = mid - 1;
		}
		//cout << "l = " << l << endl;
		//cout << l - height[i] << endl;
		ans += l - height[i];
	}
	cout << ans << endl;
	return 0;
}

/*
abacabacaba
fdsfdhasgfdsfsfhjasdjhfgfdsfdhasgfdsfsfhjasdjhfgabacabacabafasdfdfhgfasgfsdfdsfdhasgfdsfsfhjasdjhfg
*/
