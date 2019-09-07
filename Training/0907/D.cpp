#include <cstdio>
#include <cstring>

#define maxn 100010
int fail[maxn];
void build(char *s, int n)
{
	int p = 0;
	for (int i = 2; i <= n; ++i)
	{
		while (p && s[p + 1] == s[i]) p = fail[p];
		if (s[p + 1] == s[i]) ++p;
		fail[i] = p;
	}
}
char s[maxn], t[maxn];
int main()
{
	int q; scanf("%s%d", s + 1, &q);
	int n = strlen(s + 1);
	for (; q; --q)
	{
		scanf("%s", t + 1);
		int m = strlen(t + 1);
		if (n == m)
		{
			bool flag = 1;
			for (int i = 1; i <= m; ++i)
				flag &= s[i] == t[i];
			if (flag) puts("jntm!");
			else puts("friend!");
		}
		else if (n < m)
		{
			build(s, n);
			int p = 0;
			bool flag = 0;
			for (int i = 1; i <= m; ++i)
			{
				while (p && t[i] != s[p + 1]) p = fail[p];
				if (t[i] == s[p + 1]) ++p;
				if (p == n) {flag = 1; break;}
			}
			if (flag) puts("my teacher!");
			else puts("senior!");
		}
		else
		{
			build(t, m);
			int p = 0;
			bool flag = 0;
			for (int i = 1; i <= n; ++i)
			{
				while (p && s[i] != t[p + 1]) p = fail[p];
				if (s[i] == t[p + 1]) ++p;
				if (p == m) {flag = 1; break;}
			}
			if (flag) puts("my child!");
			else puts("oh, child!");
		}
	}
	return 0;
}
