#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

namespace PRIME {
	bool isNotPrime[maxn]; 
	bool isprime2[maxn];
	int prime[maxn];
	void build() {
		isNotPrime[1] = true;
		for (int i = 2; i < maxn; i++) {
			if (!isNotPrime[i]) prime[++prime[0]] = i;
			for (int j = 1; j <= prime[0] && i * prime[j] < maxn; j++) {
				isNotPrime[i * prime[j]] = true;
				if (i % prime[j] == 0) break;
			}
		}
		for (int i = 1; i < prime[0]; i++)
			for (int j = i + 1; j < prime[0] && 1ll * prime[i] * prime[j] < maxn; j++)
				isprime2[prime[i] * prime[j]] = true;
	}
}

namespace MFS {
	int fa[maxn];
	void init(int n) {
		for (int i = 0; i <= n; i++) fa[i] = i;
	}
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		fa[find(x)] = find(y);
	}
}

vector<pair<int, int> >G1[maxn], G2[maxn];
vector<pair<int, int> >E2;

int cmp_size[maxn];

unordered_map<int, int>cnt;

void work(int t) {
	int n; scanf("%d", &n);
	
	E2.clear();
	
	for (int i = 1; i <= n; i++) 
		G1[i].clear(), G2[i].clear();
	
	MFS::init(n);
	
	long long ans = 0;
	
	for (int i = 1; i < n; i++) {
		int u, v, w; 
		scanf("%d%d%d", &u, &v, &w);
		if (w == 1) {
			MFS::merge(u, v);
		} else if (PRIME::isprime2[w]) {
			E2.push_back(make_pair(u, v));
		} else if (PRIME::isNotPrime[w]) {
			;
		} else {
			G1[u].push_back(make_pair(v, w));
			G1[v].push_back(make_pair(u, w));			
		}
	}
	
	for (int i = 1; i <= n; i++)
		cmp_size[i] = 0;
	
	for (int i = 1; i <= n; i++) 
		cmp_size[MFS::find(i)]++;
	
	for (auto e : E2) 
		ans += 1ll * cmp_size[MFS::find(e.first)] * cmp_size[MFS::find(e.second)] * 2;
	
	for (int u = 1; u <= n; u++)
		for (auto e : G1[u]) {
			int v = e.first;
			G2[MFS::find(u)].push_back(make_pair(MFS::find(v), e.second));
		}
	
	for (int u = 1; u <= n; u++) {
		int all = 0;
		cnt.clear();
		for (auto e : G2[u]) {
			int v = e.first;
			all += cmp_size[v];
			cnt[e.second] += cmp_size[v];
		}
		for (auto that : cnt) {
			int now_cnt = that.second;
			ans += 1ll * now_cnt * (all - now_cnt);
		}
	}
	printf("Case %d: %lld\n", t, ans / 2);
}

int main() {
	freopen("evaluations.in", "r", stdin);
	PRIME::build();
	int T; 
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
		work(t);
	return 0;
}

