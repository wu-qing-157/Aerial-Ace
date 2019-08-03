#include <cstdio>

int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n; scanf("%d", &n);
		int maxx = 0;
		for (int i = 1; i <= n; ++i)
		{
			int x; scanf("%d", &x);
			if (i == 1) maxx < 3 * x ? maxx = 3 * x : 0;
			else maxx < x + 1 ? maxx = x + 1 : 0;
		}
		maxx % 2 == 1 ? ++maxx : 0;
		printf("%d\n", maxx);
	}
}
