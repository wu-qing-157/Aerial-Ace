#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;

vector<int>c[maxn];
vector<int>G[maxn];

struct Node {
    int sum;
    int val;
    bool tag;
} T[maxn << 2];

#define ls p << 1
#define rs p << 1 | 1

void pushup(int p) {
    T[p].sum = T[ls].sum + T[rs].sum;
}
void pushdown(int p, int l, int r) {
    if (T[p].tag) {
        int mid = l + r >> 1;
        T[ls].tag = T[rs].tag = true;
        T[ls].val = T[rs].val = T[p].val;
        T[ls].sum = (mid - l + 1) * T[p].val;
        T[rs].sum = (r - mid) * T[p].val;
        T[p].tag = false;
    } 
}
void set_val(int p, int l, int r, int L, int R, int val) {
    if (l == L && r == R) {
        T[p].sum = (r - l + 1) * val;
        T[p].val = val;
        T[p].tag = true;
    } else {
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (R <= mid) set_val(ls, l, mid, L, R, val);
        else if (L > mid) set_val(rs, mid + 1, r, L, R, val);
        else set_val(ls, l, mid, L, mid, val), set_val(rs, mid + 1, r, mid + 1, R, val);
        pushup(p);
    }
}

int ask_sum(int p, int l, int r, int L, int R) {
    if (l == L && r == R) return T[p].sum;
    else {
        pushdown(p, l, r);
        int mid = l + r >> 1;
        if (R <= mid) return ask_sum(ls, l, mid, L, R);
        else if (L > mid) return ask_sum(rs, mid + 1, r, L, R);
        else return ask_sum(ls, l, mid, L, mid) + ask_sum(rs, mid + 1, r, mid + 1, R);
    }
}

int dfn[maxn], pos[maxn], dfc;
int dep[maxn], siz[maxn], fa[maxn];

void dfs(int u) {
    siz[u] = 1;
    dfn[++dfc] = u;
    pos[u] = dfc;
    for (auto v : G[u]) {
        if (v == fa[u]) continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs(v);
        siz[u] = siz[u] + siz[v];
    }
}

bool cmp(int x, int y) {
    return dep[x] > dep[y];
}

void work(int n) {
    for (int i = 1; i <= n; i++) c[i].clear();
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d", &x); c[x].push_back(i);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(dfn, 0, sizeof(dfn[0]) * (n + 1)); 
    dfc = 0;
    dfs(1);

    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        if (!c[i].size()) continue;
        long long now = 1ll * n * (n - 1) / 2;
        sort(c[i].begin(), c[i].end(), cmp);
        set_val(1, 1, n, 1, n, 1);
        for (auto u : c[i]) {
            for (auto v : G[u]) {
                if (v == fa[u]) continue;
                int cnt = ask_sum(1, 1, n, pos[v], pos[v] + siz[v] - 1);
                now -= 1ll * cnt * (cnt - 1) / 2;
            }
            set_val(1, 1, n, pos[u], pos[u] + siz[u] - 1, 0);
        }
        int cnt = ask_sum(1, 1, n, 1, n);
        now -= 1ll * cnt * (cnt - 1) / 2;
        ans += now;
    }
    
    printf("%lld\n", ans);
}

int main() {
    int n, t = 0; 
    while (scanf("%d", &n) != EOF)
        printf("Case #%d: ", ++t), work(n);
    return 0;
}
/*
6
1 2 1 3 2 1
1 2
1 3
2 4
2 5
3 6
*/