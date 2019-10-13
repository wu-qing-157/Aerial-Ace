#include <iostream>
#include <cstdio>
#include <cstring>

const int maxn = 6e5 + 10;

char s[maxn], t[maxn];

int sa[maxn], rank[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
int st[20][maxn / 2], log_2[maxn];

int pre[maxn], nxt[maxn];

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
			++cnt[x[i]]; sa[i] > j ? y[++p] = sa[i] - j : 0;
		}
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1]; 
			m = 0;
		for (int i = n; i; --i) sa[cnt[x[y[i]]]--] = y[i];
		for (int i = 1; i <= n; i++) 
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 1, j, k = 0; i <= n; height[rank[i++]] = k) 
		for (k ? --k : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; ++k);
			
	log_2[0] = -1;
	for (int i = 1; i <= n; i++) log_2[i] = log_2[i >> 1] + 1;
	for (int i = 1; i <= n; i++) st[0][i] = height[i];
	for (int j = 1; j < 20; j++)
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
			st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}

int lcp(int x, int y) {
	if (x == y) return x;
	x = rank[x]; y = rank[y];
	if (x > y) std::swap(x, y);
	x++;
	int k = log_2[y - x + 1];
	return std::min(st[k][x], st[k][y - (1 << k) + 1]);
}

int lcp2(int x, int y) {
	if (x > y) std::swap(x, y);
	x++;
	int k = log_2[y - x + 1];
	return std::min(st[k][x], st[k][y - (1 << k) + 1]);
}

int len[maxn];

bool cmp(int x, int y) {
	int k = lcp(x, y);
	return s[x + k] > s[y + k];
}

void work() {
	int n, m = 0, f; scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", t);
		if (i == 1) f = (int)strlen(t);
		for (int j = 0; t[j]; j++)
			s[++m] = t[j];
		if (i == 1)s[++m] = '#';
		else s[++m] = '$';
	}
	s[m + 1] = 0;
	build(m, 128);
	
//	for (int i = 1; i <= m; i++, puts(""))
//		for (int j = sa[i]; s[j]; j++)
//			putchar(s[j]);
	
//	for (int i = 1; i <= m; i++) 
//		printf("sa[%d] = %d\n", i, sa[i]);
	
	int now = 0;
	for (int i = 1; i <= m; i++) {
		pre[i] = now;		
		if (sa[i] > f + 1) now = i;
	}
	now = 0;
	for (int i = m; i >= 1; i--) {
		nxt[i] = now;
		if (sa[i] > f + 1) now = i;
	}
	
//	for (int i = 1; i <= m; i++) printf("%d %d\n", pre[i], nxt[i]);
	
	for (int i = 1; i <= f; i++) {
		int pos = rank[i];
//		printf("pos = %d\n", pos);
		len[i] = 0; 
		if (pre[pos] != 0) 
			len[i] = std::max(len[i], lcp2(rank[i], pre[pos]));
		if (nxt[pos] != 0) 
			len[i] = std::max(len[i], lcp2(rank[i], nxt[pos]));
		
		//printf("len[%d] = %d\n", i, len[i]);
	}
	
	int anslen = m;
	for (int i = 1; i <= f; i++) {
		if (i + len[i] > f) continue;
		anslen = std::min(anslen, len[i]);
	}
	
	int nowans = 0;
	
	for (int i = 1; i <= f; i++) {
		if (i + len[i] > f && len[i] != anslen) continue;
		if (!nowans || cmp(nowans, i)) 
			nowans = i;
	} 
	if (!nowans) puts("Impossible");
	else {
		for (int i = 0; i <= len[nowans]; i++) 
			putchar(s[nowans + i]);
		puts("");
	}
}


int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) 
		printf("Case #%d: ", t), work();
	return 0;
}
