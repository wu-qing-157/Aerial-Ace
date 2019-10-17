const int moha = 3102331;
int lim;
int pr[maxn / 10], prcnt, fp[maxn], K, pkk[maxn / 10], cnt2[110], N;
uint phi[maxn], ksum[maxn / 10], kpw[maxn], kpow[maxn], dif[110], y[110], inv[110];
bool vis[maxn];
inline uint qpow(R uint base, R uint power)
{
	R uint ret = 1;
	for (; power; power >>= 1, base *= base)
		power & 1 ? ret *= base : 0;
	return ret;
}
uint phi1[maxn];
uint Phi(R int x)
{
	if (x <= lim) return phi[x];
	if (phi1[N / x]) return phi1[N / x];
	R uint ret = 1ll * x * (x + 1) / 2;
	for (R int i = 2, j; i <= x; i = j + 1)
	{
		j = x / (x / i);
		ret -= (j - i + 1) * Phi(x / i);
	}
	return phi1[N / x] = ret;
}
std::vector<uint> p1[maxn / 10], p2[maxn / 10], f1[maxn / 10], f2[maxn / 10], s1[maxn / 10], s2[maxn / 10];
uint P(R int x, R int k)
{
	if (!k || !x) return 0;
	if (pr[k] * pr[k] > x) return P(x, fp[(int) sqrt(x)]);
	
	if (x <= N / x)
	{
		if (p1[x].size() > k && p1[x][k]) return p1[x][k];
		while (p1[x].size() <= k) p1[x].push_back(0);
		uint ans = P(x, k - 1) + (x / pr[k]) - P(x / pr[k], k - 1) - k;
		return p1[x][k] = ans;
	}
	else
	{
		if (p2[N / x].size() > k && p2[N / x][k]) return p2[N / x][k];
		while (p2[N / x].size() <= k) p2[N / x].push_back(0);
		uint ans = P(x, k - 1) + (x / pr[k]) - P(x / pr[k], k - 1) - k;
		return p2[N / x][k] = ans;
	}
}
inline uint getinv(R uint x)
{
	return qpow(x, ~0u >> 1);
}
inline uint C(R int a, R int b)
{
	R uint num = 0;
	if (b > a) return 0;

	R uint ret = 1;
	for (R int i = 1; i <= b; ++i)
	{
		R int tmp = a - i + 1;
		while (tmp % 2 == 0) ++num, tmp >>= 1;
		ret *= tmp;
	}
//	printf("C(%d, %d) = %u\n", a, b, ret * qpow(2, num) * inv[b]);
	return ret * qpow(2, num - cnt2[b]) * inv[b];
}
std::map<int, int> Sky;
inline uint Sk(R int x)
{
	uint ret = 0;
	if (x <= lim) return kpw[x];
	if (Sky[x]) return Sky[x];
	for (R int i = 1; i <= K + 1; ++i) ret += dif[i] * C(x, i);
	return Sky[x] = ret;
}
uint F(R int x, R int k)
{
	if (!k || !x) return 0;
	if (pr[k] * pr[k] > x) return F(x, fp[(int) sqrt(x)]);
	if (x <= N / x)
	{
		if (f1[x].size() > k && f1[x][k]) return f1[x][k];
		while (f1[x].size() <= k) f1[x].push_back(0);
		uint ans = F(x, k - 1) + (Sk(x / pr[k]) - 1 - ksum[k - 1] - F(x / pr[k], k - 1)) * pkk[k];
		return f1[x][k] = ans;
	}
	else
	{
		if (f2[N / x].size() > k && f2[N / x][k]) return f2[N / x][k];
		while (f2[N / x].size() <= k) f2[N / x].push_back(0);
		uint ans = F(x, k - 1) + (Sk(x / pr[k]) - 1 - ksum[k - 1] - F(x / pr[k], k - 1)) * pkk[k];
		return f2[N / x][k] = ans;
	}
}
uint S(R int x, R int k)
{
	if (!k || !x) return 0;
	if (pr[k] * pr[k] > x) return S(x, fp[(int) sqrt(x)]);
	
	if (x <= N / x)
	{
		if (s1[x].size() > k && s1[x][k]) return s1[x][k];
		while (s1[x].size() <= k) s1[x].push_back(0);
		uint ans = S(x, k - 1) + Sk(x / pr[k]) - 1 - ksum[k - 1] - F(x / pr[k], k - 1);
		return s1[x][k] = ans;
	}
	else
	{
		if (s2[N / x].size() > k && s2[N / x][k]) return s2[N / x][k];
		while (s2[N / x].size() <= k) s2[N / x].push_back(0);
		uint ans = S(x, k - 1) + Sk(x / pr[k]) - 1 - ksum[k - 1] - F(x / pr[k], k - 1);
		return s2[N / x][k] = ans;
	}
}
inline uint Sum(R int x)
{
	uint pp = S(x, fp[(int) sqrt(x)]);
	return x - 1 - P(x, fp[(int) sqrt(x)]) + S(x, fp[(int) sqrt(x)]);
}
int main()
{
//	printf("%d\n", (sizeof (phi) * 5 + sizeof (last1) * 4 + sizeof (mem)) >> 20);
	scanf("%d%d", &N, &K);
	lim = (int) pow(N, 2.0 / 3.0);
//	printf("%d\n", lim);
	phi[1] = 1; kpw[1] = 1;
	for (R int i = 2; i <= lim; ++i)
	{
		if (!vis[i]) pr[++prcnt] = i, phi[i] = i - 1, ksum[prcnt] = ksum[prcnt - 1] + (pkk[prcnt] = kpow[i] = qpow(i, K));
		fp[i] = fp[i - 1] + !vis[i];
		kpw[i] = kpw[i - 1] + kpow[i];
		for (R int j = 1; j <= prcnt && 1ll * i * pr[j] <= lim; ++j)
		{
			vis[i * pr[j]] = 1;
			kpow[i * pr[j]] = kpow[i] * kpow[pr[j]];
			if (i % pr[j]) phi[i * pr[j]] = phi[i] * (pr[j] - 1);
			else {phi[i * pr[j]] = phi[i] * pr[j]; break;}
		}
	}
	for (R int i = 2; i <= lim; ++i) phi[i] += phi[i - 1];
	R uint last = 0, ans = 0;
	for (R int i = 1; i <= K + 1; ++i) y[i] = kpw[i];
	uint ppw = 1; R int ccnt = 0;
	for (R int i = 1; i <= K + 1; ++i)
	{
		R int tmp = i;
		while (tmp % 2 == 0) tmp >>= 1, ++ccnt;
		ppw *= getinv(tmp); inv[i] = ppw; cnt2[i] = ccnt;
//		printf("inv[%d] = %u\n", i, inv[i]);
	}
	for (R int i = 1; i <= K + 1; ++i)
	{
		for (R int j = K + 1; j >= i; --j)
			y[j] -= y[j - 1];
		dif[i] = y[i];
//		printf("%d\n", dif[i]);
	}
//	for (R int i = 1; i <= 5; ++i) printf("kpow[%d] = %u\n", i, Sk(i));
	for (R int i = 2, j; i <= N; i = j + 1)
	{
		j = N / (N / i);
		R uint Phi2 = 2 * Phi(N / i) - 1, dk = Sum(j);
		ans += (dk - last) * Phi2;
		last = dk;
	}
	printf("%u\n", ans);
	return 0;
}