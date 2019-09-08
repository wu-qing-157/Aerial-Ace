#include <cstdio>
#include <cstring>

#define maxn 200010
char s[maxn];
int next[maxn][10], s8[maxn], s9[maxn];
int main()
{
	int n, q; scanf("%d%d", &n, &q);
	scanf("%s", s + 1);
	for (int i = 1; i <= n; ++i)
	{
		memcpy(next[i + 1], next[i], sizeof (next[i]));
		next[i + 1][s[i] - '0'] = i;
	}
	for (int i = 1; i <= n; ++i)
	{
		s8[i] = s8[i - 1] + (s[i] == '8');
		s9[i] = s9[i - 1] + (s[i] == '9');
	}
	for (; q; --q)
	{
		int l, r; scanf("%d%d", &l, &r);
		int now = r + 1;
		now = next[now][2];
		now = next[now][0];
		now = next[now][1];
		if (now <= l) puts("-1");
		else
		{
			if (s9[now] - s9[l - 1] == 0) puts("-1");
			else printf("%d\n", s8[now] - s8[l - 1]);
		}
	}
	return 0;
}
/*
4 1
9012
1 4
*/
