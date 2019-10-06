#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#define maxn 100010
int fa[maxn], B[maxn];
int main()
{
	srand(time(0) + clock());
	int n = 80000, q = 160000;
	printf("%d %d\n", n, q);
	for (int i = 1; i < n; ++i) fa[i + 1] = rand() % i + 1;
	for (int i = 1; i <= n; ++i) printf("%d ", rand() % 1000000000 + 1); puts("");
	for (int i = 1; i <= n; ++i) printf("%d ", std::min(1000000000, B[i] = rand() % 100000 + 1ll + B[fa[i]])); puts("");
	printf("1000000000");
	for (int i = 2; i <= n; ++i) printf(" %d", rand() % 200000000 + 1); puts("");
	for (int i = 2; i <= n; ++i) printf("%d %d\n", fa[i], i);
	for (int i = 1; i <= q; ++i)
		printf("%d %d\n", rand() % n + 1, rand() % 200000000 + 1);
	return 0;
}
