#include <cstdio>
#include <iostream>

using std::cout;
using std::endl;

#define maxn 100010
typedef long long ll;

const int MOD = 1e9 + 7;

inline bool cmin(ll &a, ll b) {
	return a > b ? a = b, 1 : 0;
}
int tpow[maxn], tval[maxn];
ll dp[maxn][23];
int nxt[maxn];

int hash[maxn], hpow[maxn];

int geth(int l, int r) {
	return (hash[r] - 1ll * hash[l - 1] * hpow[r - l + 1] % MOD + MOD) % MOD;
}

char s[maxn];

int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, q; scanf("%d%d%d", &n, &m, &q);
		tpow[0] = 1;
		for (int i = 1; i <= n; ++i) tpow[i] = tpow[i - 1] * 10 % m;
		scanf("%s", s + 1);
		s[0] = '0';
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j < m; ++j) dp[i][j] = 0;
		dp[n + 1][0] = 1;


		
		for (int i = n; i >= 0; --i) {
			for (int j = 0; j < m; j++) {
				if (s[i] == '?') {
					for (int k = 0; k < 10; k++) {
						dp[i][(j + tpow[n - i] * k) % m] += dp[i + 1][j];
 						cmin(dp[i][(j + tpow[n - i] * k) % m], ll(2e18));
					}
				} else {
					dp[i][(j + tpow[n - i] * (s[i] - '0') % m)] += dp[i + 1][j];
					cmin(dp[i][m - (j + tpow[n - i] * (s[i] - '0')) % m], ll(2e18));
				}
			}
		}
		
		int pos = 0;
		tval[0] = 0;
		for (int i = 1; i <= n; i++) {
			tval[i] = (tval[i - 1] * 10 + (s[i] == '?' ? 0 : s[i] - '0')) % m;
			if (dp[i][(1ll * tval[i] * tpow[n - i]) % m] > ll(1e18)) pos = i;
		}
		
		nxt[n + 1] = n + 1;
		for (int i = n; i >= 1; i--) 
			nxt[i] = s[i] == '?' ? i : nxt[i + 1];
		
		hash[0] = 0;
		hpow[0] = 1;
		for (int i = 1; i <= n; i++) 
			hash[i] = (1ll * hash[i - 1] * 10 + (s[i] == '?' ? 0 : s[i] - '0')) % MOD;
		for (int i = 1; i <= n; i++)
			hpow[i] = (1ll * hpow[i - 1] * 10) % MOD;
		
		while (q--) {
			ll k; scanf("%lld", &k);
			int now = pos;
			int r1 = tval[now], r2 = hash[now];
			if (dp[now + 1][r1 * tpow[n - now] % m] < k) 
				puts("-1");
			else {
				while (true) {
					cout << now << endl;
					int now2 = nxt[now + 1];
					r1 = r1 * tpow[now2 - now - 1] % m;
					r2 = r2 * hpow[now2 - now - 1] % MOD;
					if (now2 > n) break;
					now = now2;
					ll tmp = 0;
					for (int i = 0; i < 10; i++) {
						int r = (r1 * 10 + i) % m;
						if (tmp + dp[now + 1][r1 * tpow[n - now]] >= k) {
							k -= tmp;
							r1 = (1ll * r1 * 10 + i) % m;
							r2 = (1ll * r2 * 10 + i) % MOD;	
						} 
					}

				}
			}
			printf("%d\n", r2);
		}
		
	}
	return 0;
}
