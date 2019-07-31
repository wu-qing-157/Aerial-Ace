#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0) + clock());
	int T = 1; puts("1");
	for (; T; --T)
	{
		int n = rand() % 10 + 1, m = rand() % 10 + 1;
		printf("%d %d\n", n, m);
		for (int i = 1; i <= n; ++i) printf("%d ", rand() % 10); puts("");
	}
	return 0;
}
