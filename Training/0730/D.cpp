#include <bits/stdc++.h>
using namespace std;

<<<<<<< HEAD
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

=======
const int maxn = 6e4 + 10;

vector<int>G[maxn];
vector<pair<int, int> >E;
int D[maxn];
int n, m;

typedef long long ll;
ll solve_0() { return 1ll * n * n * n; }
ll solve_1() { 
    ll ans = 0;
    for (auto e : E) {
        int u = e.first, v = e.second;
        if (v * 2 == n + 1 && u * 2 == n + 1) 
            ans += 1 * 3 * n;
        else if (u == v || v * 2 == n + 1) 
            ans += 4 * 3 * n;
        else 
            ans += 8 * 3 * n;
    }
    return ans;
}

ll solve_2() {
    for (int i = 1; i <= n; i++) D[i] = 0;
    for (auto e : E) {
        int u = e.first, v = e.second;
        set<pair<int, int> >tmp;
        tmp.emplace(u, v);
        tmp.emplace(u, n - v + 1);
        tmp.emplace(n - u + 1, v);
        tmp.emplace(n - u + 1, n - v + 1);

        tmp.emplace(v, u);
        tmp.emplace(v, n - u + 1);
        tmp.emplace(n - v + 1, u);
        tmp.emplace(n - v + 1, n - u + 1);

        for (auto f : tmp) D[f.first]++;
    } 
    ll ans = 0;
    for (int i = 1; i <= n; i++) 
        ans += 1ll * D[i] * D[i] * 3;
    return ans;
}

ll _calc(int x) {
    if (x == 0) return 1;
    if (x == 2) return 3;
    if (x == 3) return 6;
}

ll calc(int x, int y, int z, int _x, int _y, int _z) {
    ll tmp = 1ll << ((x != _x) + (y != _y) + (z != _z));
    //cout << _calc((x != y) + (x != z) + (y != z)) << endl;
    return tmp * _calc((x != y) + (x != z) + (y != z));
}

ll solve_3() {
    static int visby[maxn];
    for (int i = 1; i <= n; i++) visby[i] = 0;
    for (int i = 1; i <= n; i++) G[i].clear();
    for (auto e : E) {
        int u = e.first, v = e.second;
        if (D[u] > D[v]) 
            G[u].push_back(v);
        else
            G[v].push_back(u);
    }
    ll ans = 0;
    for (int u = 1; u * 2 <= n + 1; u++) {
        for (auto v : G[u]) visby[v] = u;
        for (auto v : G[u]) 
        for (auto w : G[v]) 
        if (w[visby] == u) {
            int ru = n - u + 1;
            int rv = n - v + 1;
            int rw = n - w + 1;

            ans += calc(u, v, w, ru, rv, rw);
        }
    }
    return ans;
}

void work() {
    E.clear();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        if (u > v) swap(u, v);
        E.emplace_back(u, v);
    }
    sort(E.begin(), E.end());
    E.erase(unique(E.begin(), E.end()), E.end());
    printf("%lld\n",  solve_0() - solve_1() + solve_2() - solve_3());
}

int main() {
    int T; scanf("%d", &T);
    while (T--) work();
    return 0;
}
>>>>>>> b8ccbfe3bbd072759716e3f6ddba590493dc92df
