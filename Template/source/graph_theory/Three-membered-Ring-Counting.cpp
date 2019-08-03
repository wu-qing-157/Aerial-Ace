#include <bits/stdc++.h>
using namespace std;
int n, m; // vertex & edge 
vector<pair<int, int> >E[maxn]; // input

#define fi first
#define se second
#define pb push_back
long long Three() {
    static vector<int>G[maxn];
    static int visby[maxn], deg[maxn];
    for (int i = 0; i <= n; i++) 
        visby[i] = deg[i] = 0,  G[i].clear();
    for (auto e : E) deg[e.fi]++, deg[e.se]++;
    for (auto e : E) deg[e.fi] > deg[e.se] ? 
        G[e.fi].pb(e.se) : G[e.se].pb(fi);
    long long ans = 0;
    for (int u = 0; u <= n; u++) {
        for (auto v : G[u]) visby[v] = u;
        for (auto v : G[u]) for (auto w : G[v]) 
            if (w[visby] == u) ans++;
    }
    return ans;
}
int main() {}
