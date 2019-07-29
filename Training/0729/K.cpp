#include <bits/stdc++.h>
using namespace std;

int n, m, mod, s1, s2;

typedef long long ll;
ll G[36];
int W[36];
int val[1 << 20];
int Sval[1 << 20];
bool ap[1 << 20];

void divid(int n) {
	ll ans = -1;
	for (int i = n; i >= 0; i--) {
		ll now = (1ll << i) + ll(pow(3, (n - i)));
		if (ans == -1 || ans > now) 
			s1 = i, s2 = n - i, ans = now;
		else break;
	}
}
int ans = 0;

void init() {
	ans = 0;
	scanf("%d%d%d", &n, &m, &mod);
	divid(n);
	
	for (int i = 0; i < 1 << s2; i++) ap[i] = false;
	for (int i = 0; i < 1 << s2; i++) Sval[i] = 0;
	
	for (int i = 0; i < n; i++) G[i] = 0ll;
	for (int i = 0; i < n; i++) scanf("%d", &W[i]);
	for (int i = 0; i < m; i++) {
	
		int u, v;
		scanf("%d%d", &u, &v);
		u--; v--;
		G[u] |= 1ll << v;
		G[v] |= 1ll << u;
	}
}	

void dfs1(int S, int now_val, int u, ll mS) {
	if (u == s1) {
		if ( (S | (mS & ((1 << s1) - 1))) == S) {
			int rS = (mS >> s1);
			if (ap[rS]) 
				ans = (ans + 1ll * now_val * Sval[rS] % mod) % mod;
			else {
				for (int i = rS; i < 1 << s2; i = (i + 1) | rS) {
					Sval[rS] = Sval[rS] + val[i];
					if (Sval[rS] >= mod)
						Sval[rS] -= mod;
				}
				ap[rS] = true;
				ans = (ans + 1ll * now_val * Sval[rS] % mod) % mod;
			}
		}
	} else {
		dfs1(S, now_val, u + 1, mS | G[u]);
		dfs1(S | (1 << u), 1ll * now_val * W[u] % mod, u + 1, mS);
	}
}

void dfs2(int S, int now_val, int u, int mS) {
	if (u == n) {
		if ((S & mS) == mS) val[S] = now_val;
		else val[S] = 0;
	} else {
		dfs2(S, now_val, u + 1, mS | (G[u] >> s1));
		dfs2(S | 1 << (u - s1), 1ll * now_val * W[u] % mod, u + 1, mS);		
	}
}

void work() {
	//cout << s1 << ' ' << s2 << endl;
	dfs2(0, 1, s1, 0);
	dfs1(0, 1, 0, 0);
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		init(), work();
	}
	return 0;
}

/*
2
4 3
998244353
1 1 1 1
1 2
2 3
3 4
4 6 998244353
1 1 1 1
1 2
1 3
1 4
2 3
2 4
3 4
1 0 998344353
1

*/
