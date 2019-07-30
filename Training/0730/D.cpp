#include <bits/stdc++.h>
using namespace std;

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