#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
const int inf = 1e9;

char s[maxn];
int sa[maxn], rnk[maxn], wa[maxn], wb[maxn], cnt[maxn], height[maxn];
int st[20][maxn], log_2[maxn];

inline void build(int n, int m) {
	
	memset(sa, 0, sizeof (sa));
	memset(cnt, 0, sizeof(cnt));
	memset(wa, 0, sizeof (wa));
	memset(wb, 0, sizeof (wb));
	
	int *x = wa, *y = wb, *t;
	for (int i = 1; i <= n; ++i) cnt[x[i] = s[i] - 'a' + 1]++;
	for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i; --i) sa[cnt[x[i]]--] = i;
	
	for (int j = 1; j < n || (j == 1 && m < n); j <<= 1, t = x, x = y, y = t) 
	{
		memset(cnt + 1, 0, m << 2);
		int p = 0;
		for (int i = n - j + 1; i <= n; ++i) y[++p] = i;
		for (int i = 1; i <= n; i++) 
		{
			++cnt[x[i]];
			sa[i] > j ? y[++p] = sa[i] - j : 0;
		}
		for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
		for (int i = n; i; --i) sa[cnt[x[y[i]]]--] = y[i];
			m = 0;
		for (int i = 1; i <= n; i++)
			y[sa[i]] = (i == 1 || x[sa[i]] != x[sa[i - 1]] || x[sa[i - 1] + j] != x[sa[i] + j]) ? ++m : m;
	}
	//for (int i = 1; i <= n; ++i) printf("%d ", sa[i]); puts("");
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

int lcp(int i, int j) {
	i = rnk[i];
	j = rnk[j];
	if (i > j) swap(i, j);
	if (i == j) return inf;
	i++;
	int k = log_2[j - i + 1];
	return min(st[k][i], st[k][j - (1 << k) + 1]);
}

int mxR[maxn];
char s1[maxn], s2[maxn];

long long sum[maxn];

void work(int t) {
	scanf("%s%s", s1 + 1, s2 + 1);
	printf("Case %d:\n", t);
	memset(s, 0, sizeof (s));
	int n = (int)strlen(s1 + 1), m = (int)strlen(s2 + 1);
	for (int i = 1; i <= n; i++) s[i] = s1[i];
	for (int i = 1; i <= m; i++) s[i + n] = s2[i];

	int npm = n + m;	
	
	build(npm, 26);
	
	int pre = -1;
	
	memset(mxR, -1, sizeof (mxR));
	memset(sum, 0, sizeof (sum));
	
	for (int i = 1; i <= npm; i++) {
		if (sa[i] <= n) {
			if (pre != -1) {
				mxR[sa[i]] = max(mxR[sa[i]], lcp(sa[i], pre));
				//cout << sa[i] << ' ' << pre << ' ' << lcp(sa[i], pre) << endl;
			}
		} else {
			pre = sa[i];
		}
	}
	
	pre = -1;
	for (int i = npm; i >= 1; i--) {
		if (sa[i] <= n) {
			if (pre != -1) {
				mxR[sa[i]] = max(mxR[sa[i]], lcp(sa[i], pre));
				//cout << sa[i] << ' ' << pre << ' ' << lcp(sa[i], pre) << endl;
			}
		} else {
			pre = sa[i];
		}
	}
	
	//for (int i = 1; i <= npm; i++) cout << sa[i] << ' '; cout << endl;
	for (int i = 1; i <= n; i++) mxR[i] = i + mxR[i] - 1/*, printf("%d ", mxR[i])*/;

	
	for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + mxR[i];
	
	int q; scanf("%d", &q);
	while (q--) {
		int L, R;
		scanf("%d%d", &L, &R);
		int P = int(upper_bound(mxR + L, mxR + n + 1, R) - mxR);
		long long ans = -1ll * (L - 1 + R - 1) * (R - L + 1) / 2;
		ans += sum[min(P - 1, R)] - sum[L - 1];
		ans += 1ll * R * max(0, R - P + 1);
		printf("%lld\n", ans);
	}
}

int main() {
	int T; 
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		work(t);
	return 0;	
}
/*
6
aaaaaaaaaaaa
aaaaaaaaaaaaaaaaaa
1
3 4
bbc
abb
4
1 3
1 2
2 3
3 3
hadafkaselalam
kas
1
1 10
aaaaaaaaaaaa
aaaaaaaaaaaaaaaaaa
1
3 4
bbc
abb
4
1 3
1 2
2 3
3 3
hadafkaselalam
kas
1
1 10
*/
