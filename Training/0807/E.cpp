#include <cstdio>
#include <cstring>

#define maxn 1010
char s[maxn];
int pw[maxn];
bool dp[maxn][maxn];
int main()
{
	int m;
	scanf("%s%d", s + 1, &m);
	int n = strlen(s + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * 10 % m;
	dp[n + 1][0] = 1;
	for (int i = n; i; --i)
		if (s[i] == '?')
		{
			for (int j = (i == 1); j <= 9; ++j)
				for (int k = 0; k < m; ++k)
					dp[i][(k + j * pw[n - i]) % m] |= dp[i + 1][k];
		}
		else
		{
			for (int k = 0; k < m; ++k)
				dp[i][(k + (s[i] - '0') * pw[n - i]) % m] |= dp[i + 1][k];
		}
	if (!dp[1][0]) puts("*");
	else
	{
		int now = 0;
		for (int i = 1; i <= n; ++i)
			if (s[i] == '?')
			{
				for (int j = (i == 1); j <= 9; ++j)
					if (dp[i + 1][(now - j * pw[n - i] % m + m) % m])
					{
						(now += m - j * pw[n - i] % m) %= m;
						printf("%c", j + '0');
						break;
					}
			}
			else
			{
				printf("%c", s[i]);
				(now += m - (s[i] - '0') * pw[n - i] % m) %= m;
			}
		puts("");
	}
	return 0;
}
