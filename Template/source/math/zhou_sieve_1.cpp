typedef long long ll;
int pr[maxn / 10], prcnt, N, lim, fp[maxn];
bool vis[maxn];
const int moha = 333331;
struct Hash {
	int next, ans; ll key;
} mem[moha * 21], *tot = mem;
int last[moha];
/*
inline int qpow(R int power)
{
	R int ret = 1;
	for (R int i = 1; i <= power; ++i) ret <<= 1;
	return ret;
}
*/
int S(R int n, R int k)
{
	if (!k) return 1;
	if (n <= pr[k]) return n;
	if (n < 1ll * pr[k] * pr[k])
	{
//		R int nk = fp[(int) sqrt(n)];
		return S(n, k - 1) + n / pr[k];
	}
	R int ret;
	R ll key = 1ll * n * prcnt + k - 1; R int pos = key % moha;
	for (R int iter = last[pos]; iter; iter = mem[iter].next) if (mem[iter].key == key) return mem[iter].ans;
	ret = S(n, k - 1) + S(n / pr[k], k);
	*++tot = (Hash) {last[pos], ret, key}; last[pos] = tot - mem;
	return ret;
}
inline int calc(R int x)
{
	N = x; lim = (int) sqrt(x);
	memset(last, 0, sizeof last);
	tot = mem;
	return S(x, prcnt);
}
int main()
{
//	printf("%d\n", (sizeof (last) + sizeof (mem) + sizeof (pr)) >> 20);
	R int p, a, b; scanf("%d%d%d", &p, &a, &b);
	if (p == 1) {printf("%d\n", b - a + 1 - (a <= 1 && 1 <= b)); return 0;}
	for (R int i = 2; i <= p; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i;
		fp[i] = fp[i - 1] + !vis[i];
		for (R int j = 1; j <= prcnt && i * pr[j] <= p; ++j)
		{
			vis[i * pr[j]] = 1;
			if (i % pr[j] == 0) break;
		}
	}
//	printf("%d\n", prcnt);
//	printf("%d\n", S(b, prcnt));
	printf("%d\n", b - a + 1 - calc(b) + calc(a - 1));
//	printf("%d\n", tot - mem);
	return 0;
}