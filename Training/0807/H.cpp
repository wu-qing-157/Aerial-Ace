#include <cstdio>

int main()
{
	int a, b, c; scanf("%d%d%d", &a, &b, &c);
	int ta, tb, tc, ans = 0;
	scanf("%d%d%d", &ta, &tb, &tc);
	if (ta > a) ans += ta - a;
	if (tb > b) ans += tb - b;
	if (tc > c) ans += tc - c;
	printf("%d\n", ans);
	return 0;
}
