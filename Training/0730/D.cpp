#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 6e4 + 10;

#define ___ __attribute__((optimize("-O3")))
bitset<maxn / 2> A[maxn / 2];
vector<int>G[maxn];
vector<pair<int, int> >E;

int n, t;

___ ll solve0() {
	return 1ll * n * n * n;
}

___ ll solve1() {
	return 1ll * E.size() * n * 3;
}

___ ll solve2() {
	ll ans = 0;
	for (int i = 1; i <= n; i++) 
		ans += 1ll * G[i].size() * G[i].size() * 3;
	//cout << "2 : " << ans << endl;
	return ans;
}

___ ll ct(int x, int y) {
	ll ans = 0;
	if (x != y)
		ans = (A[x] & A[y]).count();
	else 
		ans = A[x].count();
	ans *= 2;
	if (n & 1 && A[x][(n + 1) / 2] == true && A[y][(n + 1) / 2] == true)
		ans--;
	return ans;
}

___ ll solve3() {
	ll ans = 0;
	for (int u = 1; u <= (n + 1) / 2; u++) {
		A[u].reset();
		for (int v : G[u]) {
			if (v > (n + 1) / 2) continue;
			A[u][v] = true;
		}
	}
	
	for (auto e : E) {
		int u = e.first, v = e.second;
		if (n & 1 && u == (n + 1) / 2 && v == (n + 1) / 2) {
			ans += ct(u, u);
			continue;
		}
		
		if (u > (n + 1) / 2) continue;
		if (v >= (n + 1) / 2) continue;
		if (v > u) continue;
		
		if (u == v || ((n & 1) && u == (n + 1) / 2)) {
			ans += ct(u, v) * 4;
			continue;
		}
		ans += ct(u, v) * 8;
	}
	return ans;
}

___ void work() {
	
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i++) G[i].clear();
	E.clear();
	for (int i = 1; i <= t; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		E.emplace_back(u, v);
		E.emplace_back(u, n - v + 1);
		E.emplace_back(n - u + 1, v);
		E.emplace_back(n - u + 1, n - v + 1);
		
		E.emplace_back(v, u);
		E.emplace_back(n - v + 1, u);
		E.emplace_back(v, n - u + 1);
		E.emplace_back(n - v + 1, n - u + 1);
	}
	sort(E.begin(), E.end());
	E.erase(unique(E.begin(), E.end()), E.end());
	for (auto e : E) 
		G[e.first].push_back(e.second);
	
	ll ans = solve0() - solve1() + solve2() - solve3();
	printf("%lld\n", ans);
}	

___ int main() {	
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}

