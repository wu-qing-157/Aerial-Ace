#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 100010
const int mod = 1e9 + 7;
struct info {
    int sumf, sumy, ret1, ret2;
    inline info operator + (const info &that) const
    {
        return (info) {(sumf + that.sumf) % mod,
                       (sumy + that.sumy) % mod,
                       int((ret1 + that.ret1 + 1ll * sumy * that.sumf) % mod),
                       int((ret2 + that.ret2 + 1ll * sumf * that.sumy) % mod)};
    }
} tr[maxn << 2], ans;
struct Edge {
    Edge *next;
    int to;
} *last[maxn], e[maxn << 1], *ecnt = e;
inline void link(int a, int b)
{
    *++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
    *++ecnt = (Edge) {last[b], a}; last[b] = ecnt;
}
bool vis[maxn];
int dfn[maxn], son[maxn], top[maxn], size[maxn], dep[maxn], fa[maxn], timer, pos[maxn];
int f[maxn], y[maxn];
void dfs1(int x)
{
    vis[x] = 1; size[x] = 1; dep[x] = dep[fa[x]] + 1;
    for (Edge *iter = last[x]; iter; iter = iter -> next)
        if (!vis[iter -> to])
        {
            fa[iter -> to] = x;
            dfs1(iter -> to);
            size[x] += size[iter -> to];
            size[son[x]] < size[iter -> to] ? son[x] = iter -> to : 0;
        }
}
void dfs2(int x)
{
    vis[x] = 0; top[x] = son[fa[x]] == x ? top[fa[x]] : x;
    dfn[x] = ++timer; pos[timer] = x;
    if (son[x]) dfs2(son[x]);
    for (Edge *iter = last[x]; iter; iter = iter -> next)
        if (vis[iter -> to]) dfs2(iter -> to);
}
inline int getlca(int a, int b)
{
    while (top[a] != top[b])
        dep[top[a]] < dep[top[b]]
            ? b = fa[top[b]]
            : a = fa[top[a]];
    return dep[a] < dep[b] ? a : b;
}
void update(int o)
{
    tr[o] = tr[o << 1] + tr[o << 1 | 1];
}
void build(int o, int l, int r)
{
    if (l == r)
    {
        tr[o] = (info) {f[pos[l]], y[pos[l]], 0, 0};
        return ;
    }
    int mid = l + r >> 1;
    build(o << 1, l, mid);
    build(o << 1 | 1, mid + 1, r);
    update(o);
}
int ql, qr, qv;
void modify(int o, int l, int r)
{
    if (l == r)
    {
        tr[o] = (info) {qv, y[pos[l]], 0, 0};
        return ;
    }
    int mid = l + r >> 1;
    if (ql <= mid) modify(o << 1, l, mid);
    else modify(o << 1 | 1, mid + 1, r);
    update(o);
}
void query(int o, int l, int r)
{
    if (ql <= l && r <= qr)
    {
        ans = ans + tr[o];
        return ;
    }
    int mid = l + r >> 1;
    if (ql <= mid) query(o << 1, l, mid);
    if (mid < qr) query(o << 1 | 1, mid + 1, r);
}
int n;
void tr_query(int x, int f, int lim, info &ret)
{
	ret = (info) {0, 0, 0, 0};
	while (top[x] != top[f])
    {
	    ans = (info) {0, 0, 0, 0};
        ql = dfn[top[x]]; qr = dfn[x];
        query(1, 1, n);
        x = fa[top[x]];
        ret = ans + ret;
    }
    ans = (info) {0, 0, 0, 0};
    ql = dfn[f] + lim; qr = dfn[x];
    if (ql <= qr) query(1, 1, n);
    ret = ans + ret;
}
int main()
{
    int T; scanf("%d", &T);
    for (; T; --T)
    {
        scanf("%d", &n);
        memset(last, 0, sizeof last); ecnt = e; timer = 0;
        memset(son, 0, sizeof (son));
        for (int i = 1; i <= n; ++i) scanf("%d", f + i), f[i] %= mod;
        for (int i = 1; i <= n; ++i) scanf("%d", y + i), y[i] %= mod;
        for (int i = 1; i < n; ++i)
        {
            int a, b; scanf("%d%d", &a, &b);
            link(a, b);
        }
        dfs1(1); dfs2(1);
        int m; scanf("%d", &m);
        build(1, 1, n);
        for (; m; --m)
        {
            int opt; scanf("%d", &opt);
            if (opt == 1)
            {
                int u, v, x; scanf("%d%d%d", &u, &v, &x);
                int lca = getlca(u, v);
                info ans1, ans2;
                tr_query(u, lca, 0, ans1);
                tr_query(v, lca, 1, ans2);
                info anss = ans1 + ans2;
                int rett = (ans1.ret2 + ans2.ret1 + 1ll * ans1.sumy * ans2.sumf) % mod;
                printf("%d\n", int((1ll * anss.sumf * x - rett + mod) % mod));
            }
            else
            {
                int c, v; scanf("%d%d", &c, &v); v %= mod;
                ql = dfn[c]; qv = v;
                modify(1, 1, n);
            }
        }
    }
    return 0;
}
