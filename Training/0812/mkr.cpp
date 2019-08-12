#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0) + clock());
	int n = 400000; printf("%d\n", n);
	for (int i = 1; i <= n; ++i)
		printf("%d %d\n", 1, rand() % n + 1);
	return 0;
}
