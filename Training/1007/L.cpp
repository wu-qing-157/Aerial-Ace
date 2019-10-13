#include <cstdio>

const int dx[6] = {0, 0, 0, 1, 1, 2}, dy[6] = {1, 2, 3, 2, 3, 3};
int a[4], b[4];
int cnter;
void dfs(int step)
{
	if (step == 6)
	{
		bool flag = 1;
		for (int i = 0; i < 4; ++i)
			flag &= a[i] == b[i];
		cnter += flag;
		return ;
	}
	b[dx[step]] += 3;
	dfs(step + 1);
	b[dx[step]] -= 3;
	
	b[dy[step]] += 3;
	dfs(step + 1);
	b[dy[step]] -= 3;
	
	b[dx[step]] += 1; b[dy[step]] += 1;
	dfs(step + 1);
	b[dx[step]] -= 1; b[dy[step]] -= 1;
}
int main()
{
	int T; scanf("%d", &T);
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		cnter = 0;
		for (int i = 0; i < 4; ++i)
			scanf("%d", a + i);
		dfs(0);
		printf("Case #%d: ", Cas);
		if (cnter == 0) puts("Wrong Scoreboard");
		else if (cnter == 1) puts("Yes");
		else puts("No");
	}
	return 0;
}
