#include <cstdio>

typedef long long ll;
int main()
{
	int n, Cas = 0; ll k;
	while (scanf("%d%lld", &n, &k) != EOF)
	{
		printf("Case #%d: ", ++Cas);
		if (k <= n) printf("%lld\n", k);
		else
		{
			k -= n;
			k %= 2 * (n - 1);
			if (k != 0) printf("%lld\n", k % (n - 1) == 0 ? n - 1 : k % (n - 1));
			else printf("%d\n", n);
		}
	}
	return 0;
}
