#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

vector<pair<int, int> >G[maxn], F[maxn];

int ans[maxn];
bool vis[maxn];
int w[maxn];

int dfs1(int u) {
    int sum = 0;
    vis[u] = true;
    for (auto e : G[u]) {
        int id = e.second;
        int v = e.first;
        if (vis[v]) continue;
        int tmp = dfs1(v);
        ans[id] += tmp;
        sum += tmp;
    }

    if (w[u] > 0) sum += w[u];
    else {
        int tmp = min(sum, -w[u]);
        sum -= tmp;
        w[u] += tmp;
    }
    return sum;
}

int dfs2(int u) {
    int sum = 0;
    vis[u] = true;
    for (auto e : F[u]) {
        int id = e.second;
        int v = e.first;
        if (vis[v]) continue;
        int tmp = dfs2(v);
        ans[id] -= tmp;
        sum += tmp;
    }
    if (w[u] < 0) 
        sum -= w[u];
    return sum;
}

int main() {
    int a, b, m; cin >> a >> b >> m;
    
    for (int i = 1; i <= a; i++) cin >> w[i], w[i] = -w[i];
    for (int i = 1; i <= b; i++) cin >> w[i + a];

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u < 0) u = -u; else u += a;
        if (v < 0) v = -v; else v += a;
        G[u].push_back(make_pair(v, i));
        F[v].push_back(make_pair(u, i));
    }
    
    dfs1(1);
    memset(vis, 0, sizeof vis);
    dfs2(1);

    cout << "YES" << endl;
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
    cout << endl;

    return 0;
}
/*
2 2 6 
5 3 
4 4 
-1 1 
-2 1 
-2 2 
1 2 
2 -1 
2 -2


*/