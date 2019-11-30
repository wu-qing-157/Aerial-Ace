#include <cstdio>
#include <random>
#include <vector>
#include <set>
#include <ctime>
 
typedef long long ll;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
const int maxn = 100010;
const int maxm = 200010;
const ll MOD = 1000000000000000003ll;
ll ra[maxn];
inline void init()
{
	std::mt19937_64 mt(time(0));
	std::uniform_int_distribution<long long> uid(0, MOD - 1);
	for (int i = 0; i < maxn; ++i) ra[i] = uid(mt);
}
inline ll mul_mod(ll x, ll y, ll p)
{
	ll t = (x * y - (ll) ((long double) x / p * y + 1e-3) * p) % p;
	return t < 0  ? t + p : t;
}
inline ll qpow(ll base, ll power, ll mod)
{
	ll ret = 1;
	for (; power; power >>= 1, base = mul_mod(base, base, mod))
		power & 1 ? ret = mul_mod(ret, base, mod) : 0;
	return ret;
}
inline ll inverse(ll x, ll p)
{
	return qpow(x, p - 2, p);
}
struct node {
	std::vector<ll> s;
	int d1, d2;
	ll h1, h2;
	node() {d1 = d2 = 0;}
	void add(int d, ll v)
	{
		s.push_back(v);
		if (d > d1) d2 = d1, d1 = d;
		else if (d > d2) d2 = d;
	}
	ll hash() {
		h1 = h2 = 1;
		for (ll i : s)
		{
			h1 = mul_mod(h1, ra[d1] + i, MOD);
			h2 = mul_mod(h2, ra[d2] + i, MOD);
		}
		return h1;
	}
	std::pair<int, ll> del(int d, ll v)
	{
		if (d == d1) return {d2 + 1, mul_mod(h2, inverse(ra[d2] + v, MOD), MOD)};
		return {d1 + 1, mul_mod(h1, inverse(ra[d1] + v, MOD), MOD)};
	}
} ;
std::pair<int, ll> u[maxn];
std::vector<int> e[maxn];
node tree[maxn];
ll A[maxn], B[maxn];
ll st;
int del;
void dfs1(int x, int p = -1) {
	tree[x] = node();
	for (int to : e[x])
		if (to != p && to != del)
		{
			dfs1(to, x);
			tree[x].add(tree[to].d1 + 1, tree[to].h1);
		}
	A[x] = tree[x].hash();
}
ll sum; bool flag;
void dfs2(int x, int p = -1)
{
	if (~p) tree[x].add(u[x].first, u[x].second);
	B[x] = tree[x].hash();
    sum ^= B[x];
	for (int to : e[x])
		if (to != p && to != del)
		{
			u[to] = tree[x].del(tree[to].d1 + 1, tree[to].h1);
			dfs2(to, x);
		}
}
int n, deg[maxn];
void solve(int root)
{
	for (int i = 1; i <= n; ++i) u[i] = {0, 0};
	dfs1(root); sum = 0;
	dfs2(root);
	if (st == -1) st = sum;
	else flag |= sum != st;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
	{
		int a, b; scanf("%d%d", &a, &b);
		e[a].push_back(b);
		e[b].push_back(a);
		++deg[a]; ++deg[b];
	}
	int ans = -1;
	for (int i = 1; i <= n; ++i)
		if (deg[i] >= 2)
		{
			del = i; st = -1; flag = 0;
			for (int to : e[i])
				solve(to);
			if (!flag) cmax(ans, deg[i]);
		}
	printf("%d\n", ans);
	return 0;
}
