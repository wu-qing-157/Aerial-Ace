#include <cstdio>
#include <algorithm>

#define maxn 300010
typedef long long ll;
const int mod = 998244353;
inline int qpow(int base, int power)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
struct Node {
	Node *ch[2];
	int size;
} mem[maxn * 60], *tot = mem, *rt;
inline Node *new_node()
{
	*++tot = (Node) {mem, mem, 0};
	return tot;
}
int p;
inline void insert(ll x)
{
	Node *now = rt;
	for (int i = p - 1; ~i; --i)
	{
		int d = x >> i & 1;
		if (now -> ch[d] == mem) now -> ch[d] = new_node();
		now = now -> ch[d];
		++now -> size;
	}
}
ll a[maxn], k;
int sum;
void dfs(int step, Node *a, Node *b)
{
	if (step < 0)
	{
		sum = (sum + 1ll * a -> size * b -> size) % mod;
		return ;
	}
	if (a == mem || b == mem) return ;
	if (k >> step & 1)
	{
		dfs(step - 1, a -> ch[0], b -> ch[1]);
		dfs(step - 1, a -> ch[1], b -> ch[0]);
	}
	else
	{
		sum = (sum + 1ll * a -> ch[0] -> size * b -> ch[1] -> size) % mod;
		sum = (sum + 1ll * a -> ch[1] -> size * b -> ch[0] -> size) % mod;
		dfs(step - 1, a -> ch[0], b -> ch[0]);
		dfs(step - 1, a -> ch[1], b -> ch[1]);
	}
}
int main()
{
	mem -> ch[0] = mem -> ch[1] = mem;
	int n; scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	if (k == 0) return !printf("%d\n", (qpow(2, n) - 1 + mod) % mod);
	std::sort(a + 1, a + n + 1);
	p = 64 - __builtin_clzll(k);
	int ans = 1;
	// printf("%d\n", p);
	for (int i = 1, j = 1; i <= n; i = j)
	{
		tot = mem; rt = new_node();
		while (j <= n && (a[i] >> p) == (a[j] >> p))
		{
			insert(a[j]);
			++j;
		}
		sum = 0;
		dfs(p - 2, rt -> ch[0], rt -> ch[1]);
		ans = 1ll * ans * (j - i + 1 + sum) % mod;
	}
	printf("%d\n", (ans + mod - 1) % mod);
	return 0;
}
