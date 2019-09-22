#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int>G[maxn];

using hash_t = pair<int, int>;
const hash_t P = make_pair(998244353, int(1e9 + 7));

inline void mod(hash_t &c) {
	c.first >= P.first ? c.first -= P.first : 0;
	c.second >= P.second ? c.second -= P.second : 0;
	c.first < 0 ? c.first += P.first : 0;
	c.second < 0 ? c.second += P.second : 0;	
}

bool operator == (const hash_t &a, const hash_t &b) {
	return a.first == b.first && a.second == b.second;
}
hash_t operator + (const hash_t &a, const hash_t &b) {
	hash_t c = make_pair(a.first + b.first, a.second + b.second);
	mod(c); return c;
}
hash_t operator - (const hash_t &a, const hash_t &b) {
	hash_t c = make_pair(a.first - b.first, a.second - b.second);
	mod(c); return c;
}
/*
hash_t operator * (const hash_t &a, int b) {
	return make_pair(1ll * a.first * b % P.first, 1ll * a.second * b % P.second);
}
*/
hash_t operator * (const hash_t &a, const hash_t &b) {
	return make_pair(1ll * a.first * b.first % P.first, 
					1ll * a.second * b.second % P.second);
}

int fpw(int a, int b, int p, int c = 1) {
	while (b) {
		if (b & 1)
			c = 1ll * a * c % p;
		b >>= 1; a = 1ll * a * a % p;
	} return c;
}

hash_t inv(hash_t a) {
	return make_pair(fpw(a.first, P.first - 2, P.first), 
					fpw(a.second, P.second - 2, P.second));
}

hash_t hs[maxn], hf[maxn];

const int MOD = 998244353;
int gs[maxn], gf[maxn];
int siz[maxn];
int inv_mod[maxn];
hash_t hw[maxn];

void dfss(int u, int f) {
	map<hash_t, int>cnt;
	siz[u] = 1;
	hs[u] = make_pair(1, 1);
	gs[u] = 1;
	int ID = 0;
	for (auto v : G[u])	{
		if (v == f) continue;
		dfss(v, u);
		hs[u] = hs[u] * hs[v];
		siz[u] += siz[v];
		gs[u] = 1ll * gs[u] * gs[v] % MOD;
		gs[u] = 1ll * gs[u] * ++ID % MOD;
		gs[u] = 1ll * gs[u] * inv_mod[++cnt[hs[v]]] % MOD;
	}
	hs[u] = hs[u] + hw[siz[u]];
}
int n;
void dfsf(int u, int f) {
	map<hash_t, int>cnt;
	int prod = 1;
	int ID = 0;
	hash_t now = make_pair(1, 1);
	for (auto v : G[u]) {
		prod = 1ll * prod * ++ID % MOD;
		if (v == f) {
			prod = 1ll * prod * gf[f] % MOD;
			prod = 1ll * prod * inv_mod[++cnt[hf[u]]] % MOD;
			now = now * hf[u];
		}
		else {	
			prod = 1ll * prod * gs[v] % MOD;
			prod = 1ll * prod * inv_mod[++cnt[hs[v]]] % MOD;
			now = now * hs[v];
		}
	}
	prod = 1ll * prod * inv_mod[ID--] % MOD;
	for (auto v : G[u]) {
		if (v == f) continue;
		gf[v] = 1ll * prod * (cnt[hs[v]]) % MOD * fpw(gs[v], MOD - 2, MOD) % MOD;
		hf[v] = now * inv(hs[v]) + hw[n - siz[v]];
		dfsf(v, u);
	}
}
hash_t h[maxn];
int g[maxn];
void dfs(int u, int f) {
	h[u] = (hs[u] - hw[siz[u]]) * hf[u] + hw[n];
	g[u] = 1ll * gs[u] * gf[u] % MOD;
	map<hash_t, int>cnt;
	for (auto v : G[u]) 
		if (v != f) ++cnt[hs[v]];
	for (auto v : G[u])
		if (v == f) {
			g[u] = 1ll * g[u] * G[u].size() % MOD;
			g[u] = 1ll * g[u] * inv_mod[++cnt[hf[u]]] % MOD;
		} else dfs(v, u);
}

void work() {
	scanf("%d", &n);
	memset(hs + 1, 0, sizeof(hf[0]) * (n));
	memset(hf + 1, 0, sizeof(hf[0]) * (n));
	memset(gf + 1, 0, sizeof(gf[0]) * (n));
	memset(gs + 1, 0, sizeof(gf[0]) * (n));
	for (int i = 1; i <= n; i++) G[i].clear();
	for (int i = 1; i < n; i++) {
		int u, v; scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfss(1, -1);
	gf[1] = 1;
	hf[1] = make_pair(1, 1);
	dfsf(1, -1);
	dfs(1, -1);
	set<hash_t>st;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!st.count(h[i]))
			ans = (ans + g[i]) % MOD, st.insert(h[i]);
	}
	printf("%d\n", ans);
}

int main() {
	for (int i = 1; i < maxn; i++) 
		inv_mod[i] = fpw(i, MOD - 2, MOD);
	for (int i = 1; i < maxn; i++) 
		hw[i] = make_pair(rand() % P.first, rand() % P.second);
		//hw[i] = make_pair(i, i);
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
