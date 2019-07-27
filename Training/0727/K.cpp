#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;
const int maxn = 2010;
int T[maxn], C[maxn], n, k;
int fac[maxn], ifac[maxn];

int fpw(int x, int y) {
	int ans = 1;
	while (y) {	
		if (y & 1) ans = 1ll * ans * x % P;
		x = 1ll * x * x % P;
		y >>= 1;
	} return ans;
}

int c(int n, int m) {
	if (m > n) return 0;
	return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;
}

void init() {
	scanf("%d%d", &n, &k);
	fac[0] = 1;
	for (int i = 1; i < maxn; i++) 
		fac[i] = fac[i - 1] * 1ll * i % P;
	ifac[maxn - 1] = fpw(fac[maxn - 1], P - 2);
	for (int i = maxn - 1; i >= 1; i--) 
		ifac[i - 1] = 1ll * ifac[i] * i % P;
	
	for (int i = 0; i < maxn; i++)
		T[i] = fpw(k - 1, i);
	C[0] = 1; C[1] = k;
	for (int i = 2; i < maxn; i++) 
		C[i] = (1ll * k * fpw(k - 1, i - 1) % P - C[i - 1] + P) % P;
}

vector<int>G[maxn];

bool vis[maxn];
bool ins[maxn];
bool inc[maxn];
vector<int>stk;

vector<int>c_set, t_set;

void dfs1(int u, int fa) {
	vis[u] = ins[u] = true;
	stk.push_back(u);
	for (auto v : G[u]) {
		if (ins[v] && v != fa) {
			int i = stk.size() - 1;
			while (stk[i] != v) 
				inc[stk[i]] = true, i--;
			inc[v] = true;
		}
		else if (!vis[v]) dfs1(v, u);
	}
	stk.pop_back();
	ins[u] = false;
}

int dp[maxn][2];

void DP() {
	dp[1][0] = k;
	dp[1][1] = 0;
	for (int i = 2; i <= n; i++) { 
		dp[i][0] = dp[i - 1][1];
		dp[i][1] = (
					1ll * dp[i - 1][0] * (k - 1) % P
					 + 1ll * dp[i - 1][1] * (k - 2) % P
					)%P;
	}
}

void work() {
	memset(vis, 0, sizeof (vis));
	memset(inc, 0, sizeof (ins));
	memset(ins, 0, sizeof (ins));
	c_set.clear(); t_set.clear();
	for (int i = 0; i < n; i++) G[i].clear();
	for (int i = 0; i < n; i++) {
		int x; scanf("%d", &x);
		G[i].push_back(x);
		G[x].push_back(i);
	}
	int cnt = 0, ccnt = 0;
	for (int i = 0; i < n; i++) 
		if (!vis[i]) {
			dfs1(i, -1);
			int now = 0;
			for (int i = 0; i < n; i++) 
				now += (inc[i] == true);
			if (cnt - now == 0)
			{
				c_set.push_back(2);
				ccnt += 2;
			}
			else 
				c_set.push_back(now - cnt);
			cnt = now;
		}
	
	int ret = 1;
	for (int c : c_set)
	{
		ret = 1ll * ret * dp[c][1] % P;
		//printf("c %d\n", c);
	}
	ret = 1ll * ret * fpw(k - 1, n - cnt - ccnt) % P;
	printf("%d\n", ret);
	
	//for (int i = 1; i <= 5; ++i) printf("%d ", dp[i][1]); puts("");
	
}

int main() {
	int T; scanf("%d", &T);
	while (T--)
		init(), DP(), work();
	return 0;
}
/*
3
3 3
1 2 0
4 3
1 2 0 0
3 2
1 2 0

1
12 10
1 2 0 0 0 1 1 2 2 10 11 9
*/
