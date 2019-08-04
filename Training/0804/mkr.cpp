#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int main()
{
	srand(time(0) + clock());
	int n = 100000, k = rand() % n + 1;
	for (int i = 1; i <= n; ++i) printf("%c", rand() % 26 + 'a'); printf(" %d\n", k);
	for (int i = 0; i < 26; ++i)
	{
		int l = rand() % 2000 + 1, r = rand() % n + 1;
		if (l > r) std::swap(l, r);
		printf("%d %d\n", l, r);
	}
	return 0;
}
