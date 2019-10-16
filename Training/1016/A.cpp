#include <cstdio>

int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int x; scanf("%d", &x);
		printf("Case #%d: %.10lf\n", Cas, double(x - 1));
	}
	return 0;
}
