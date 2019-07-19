#include <cstdio>

#define maxn 1000010
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
typedef long long ll;
ll pw[110];
int pr[maxn], prcnt, mp[maxn];
bool vis[maxn];
int main()
{
	//freopen("halfnice.in", "r", stdin);
	int T; scanf("%d", &T);
	pw[0] = 1;
	for (int i = 1; i <= 15; ++i) pw[i] = pw[i - 1] * 10ll;
	for (int i = 2; i < maxn; ++i)
	{
		if (!vis[i]) mp[pr[++prcnt] = i] = i;
		for (int j = 1; j <= prcnt && i * pr[j] < maxn; ++j)
		{
			vis[i * pr[j]] = 1;
			mp[i * pr[j]] = pr[j];
			if (i % pr[j] == 0) break;
		}
	}
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		ll A, B, tA, tB; scanf("%lld%lld", &A, &B);
		ll ans = -1;
		if (B >= 99) ans = 99;
		int len = 0; tB = B;
		while (tB) tB /= 10, ++len;
		tB = B / pw[len - len / 2]; tA = B % pw[len - len / 2];
		int tmp = tB;
		while (tmp != 1)
		{
			int now = mp[tmp];
			while (tmp % now == 0) tmp /= now;
			int p = tA / now * now;
//			printf("%lld %d\n", tB, p);
			if (p != 0) cmax(ans, tB * pw[len - len / 2] + p);
//			printf("%lld\n", ans);
		}
		bool flag = 0;
		for (int i = 0; i <= 6; ++i)
			if (tB == pw[i]) flag = 1;
		if (flag) cmax(ans, pw[len - 1] - 1);
		else
		{
			--tB;
			tmp = tB; tA = pw[len - len / 2] - 1;
			while (tmp != 1)
			{
				int now = mp[tmp];
				while (tmp % now == 0) tmp /= now;
				int p = tA / now * now;
				if (p != 0)
					cmax(ans, tB * pw[len - len / 2] + p);
			}
		}
		printf("Case %d: ", Cas);
		if (ans < A) puts("impossible");
		else printf("%lld\n", ans);
	}
	return 0;
}
