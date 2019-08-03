#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0) + clock());
	int T = 5; printf("%d\n", T);
	for (; T; --T)
	{
		int n = 500000, m = 2000; printf("%d %d\n", n, m);
		for (int i = 1; i < n; ++i)
			printf("%d %d\n", rand() % i + 1, i + 1);
		for (; m; --m)
		{
			int opt = rand() % 7 + 1, v = rand() % n + 1, u = rand() % n + 1;
			printf("%d %d %d", opt, u, v);
			if (opt <= 3 || opt == 7) printf(" %d", rand() % 1000 + 1); puts("");
		}
	}
	return 0;
}
