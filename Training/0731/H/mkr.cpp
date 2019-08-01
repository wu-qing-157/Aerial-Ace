#include <cstdio>
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(0) + clock());
	int n = rand() % 20 + 1, S = 1 << n;
	printf("%d %d\n", n, rand() % S);
	return 0;
}
