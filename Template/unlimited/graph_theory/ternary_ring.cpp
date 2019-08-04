#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

long long ternary_ring(int n, const vector<pair<int, int>>&E) {
    static vector<int>G[maxn];
    static int visby[maxn], deg[maxn];
    for (int i = 0; i <= n; i++) 
        visby[i] = deg[i] = 0,  G[i].clear();
    for (auto e : E) deg[e.first]++, deg[e.second]++;
    for (auto e : E) deg[e.first] > deg[e.second] ? 
        G[e.first].push_back(e.second) : G[e.second].push_back(e.first);
    long long ans = 0;
    for (int u = 0; u <= n; u++) {
        for (auto v : G[u]) visby[v] = u;
        for (auto v : G[u]) for (auto w : G[v]) 
            if (w[visby] == u) ans++; // (u, v, w) unordered
    }
    return ans;
} // O(n + m \times \sqrt(m)) 

int main() {}
