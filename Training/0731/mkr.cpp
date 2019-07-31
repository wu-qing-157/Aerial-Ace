#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main()
{
	srand(time(0) + clock());
	int n = 10, m = 100;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= m; ++i) printf("%d ", rand() % 4); puts("");
	int l = 1, r = 1;
	for (int i = 1; i <= n; ++i)
	{
		l = rand() % (n - l) + l; r = rand() % (n - r) + r;
		if (l > r) std::swap(l, r);
		printf("%d %d %d\n", l, r, rand() % 100 + 1);
	}
	return 0;
}
