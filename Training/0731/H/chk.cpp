#include <cstdio>

int Sta[233];
int main()
{
	FILE *in = fopen("in", "r"), *out = fopen("out", "r");
	int n, m, k;
	fscanf(in, "%d%d", &n, &k);
	fscanf(out, "%d", &m);
	for (int i = 1; i <= m; ++i)
	{
		int a, b; fscanf(out, "%d%d", &a, &b);
		Sta[a - 1] |= 1 << (b - 1);
	}
	int ccnt = 0;
	for (int S = 0; S < (1 << n); ++S)
	{
		int St = 0, cnt = 0;
		for (int i = 0; i < n; ++i)
			if (S & (1 << i)) ++cnt, St |= Sta[i];
		if (__builtin_popcount(St) < cnt) ++ccnt;
	}
	if (ccnt == k) puts("OK");
	else puts("Wrong Answer!");
	printf("Your Answer is %d, And the std is %d\n", ccnt, k);
	return 0;
}
