#include <cstdio>

#define maxn 2333
struct edge {int a, b;} e[maxn];
int ecnt;
inline void link(int a, int b)
{
	e[++ecnt] = (edge) {a, b};
}
int main()
{
	int n, k; scanf("%d%d", &n, &k);
	for (int i = n - 1, j = 1; ~i; --i, ++j)
	{
		if (!(k & (1 << i)))
		{
			link(j, j);
			j < n ? link(j + 1, j), 1 : 0;
		}
	}
	printf("%d\n", ecnt);
	for (int i = 1; i <= ecnt; ++i) printf("%d %d\n", e[i].a, e[i].b);
	return 0;
}
