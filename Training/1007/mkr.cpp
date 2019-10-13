#include <cstdio>
#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0) + clock());
	int T = 10; printf("%d\n", T);
	for (; T; --T)
	{
		int n = 10, m = 20;
		printf("%d %d\n", n, m);
		for (int i = 1; i <= n; ++i) printf("%d ", rand() % n + 1); puts("");
		for (int i = 1; i <= m; ++i)
			printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10 + 1);
		int q = 10; printf("%d\n", q);
		for (; q; --q)
		{
			printf("%d %d\n", rand() % n + 1, rand() % 10 + 1);
		}
	}
	return 0;
}
