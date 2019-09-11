#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int oo = 1e7;
int main()
{
	srand(time(0) + clock());
	int T = 1; printf("%d\n", T);
	for (; T; --T)
	{
		int n = 1e5, q = 1e5;
		printf("%d %d\n", n, q);
		for (int i = 1; i <= n; ++i) printf("%d ", rand() % oo + 1); puts("");
		for (int i = 1; i <= q; ++i)
		{
			int l = rand() % n + 1, r = rand() % n + 1;
			if (l > r) std::swap(l, r);
			printf("%d %d\n", l, r);
		}
	}
	return 0;
}
