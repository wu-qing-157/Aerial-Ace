#include <cstdio>

#define maxn 1010
int cnt[maxn];
int main()
{
	int K, n; scanf("%d%d", &K, &n);
	for (int i = 1; i <= n; ++i)
	{
		int x; scanf("%d", &x);
		if (x <= K) ++cnt[x];
		else {puts("*"); return 0;}
	}
	for (int Num = (n - 1) / K; Num <= (n + 1) / K; ++Num)
	{
		int plus = 0, minus = 0;
		for (int i = 1; i <= K; ++i)
			if (cnt[i] < Num)
				plus += Num - cnt[i];
			else if (cnt[i] > Num)
				minus += cnt[i] - Num;
		if (plus == 1 && minus == 0)
		{
			for (int i = 1; i <= K; ++i)
				if (cnt[i] < Num)
					return !printf("+%d\n", i);
		}
		if (minus == 1 && plus == 0)
		{
			for (int i = 1; i <= K; ++i)
				if (cnt[i] > Num)
					return !printf("-%d\n", i);
		}
		if (minus == 1 && plus == 1)
		{
			int p1, p2;
			for (int i = 1; i <= K; ++i)
				if (cnt[i] < Num) p2 = i;
				else if (cnt[i] > Num) p1 = i;
			return !printf("-%d +%d\n", p1, p2);
		}
	}
	puts("*");
	return 0;
}
