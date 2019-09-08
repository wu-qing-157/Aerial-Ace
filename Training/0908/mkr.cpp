#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

int main()
{
	srand(time(0) + clock());
	int n = 200000, m = 200000;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i) printf("%d ", rand() % n + 1); puts("");
	for (; m; --m)
	{
		int opt = rand() % 2 + 1;
		if (opt == 1) printf("1 %d %d\n", rand() % n + 1, rand() % n + 1);
		else
		{
			int l = rand() % n + 1, r = rand() % n + 1;
			if (l > r) std::swap(l, r);
			int x = rand() % n + 1, y = rand() % n + 1;
			if (x > y) std::swap(x, y);
			printf("2 %d %d %d %d\n", l, r, x, y);
		}
	}
	return 0;
}
