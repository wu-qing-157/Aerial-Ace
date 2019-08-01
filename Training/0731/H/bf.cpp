#include <cstdio>
#include <cstdlib>

#define maxn 10
int Sta[maxn];
const int n = 4, k = 6;
void dfs(int step)
{
	if (step == n)
	{
		int ccnt = 0;
		for (int S = 0; S < (1 << n); ++S)
		{
			int St = 0, cnt = 0;
			for (int i = 0; i < n; ++i)
				if (S & (1 << i)) ++cnt, St |= Sta[i];
			if (__builtin_popcount(St) < cnt) ++ccnt;
		}
		if (ccnt == k)
		{
			int eecnt = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (Sta[i] & (1 << j)) ++eecnt;
			//if (eecnt != 2) return;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (Sta[i] & (1 << j))
						printf("%d %d\n", i + 1, j + 1);
			puts("----");
			//exit(0);
		}
		return ;
	}
	for (int S = 0; S < (1 << n); ++S)
	{
		Sta[step] = S;
		dfs(step + 1);
	}
}
int main()
{
	dfs(0);
	return 0;
}
