#include <cstdio>
#include <cstring>

#define maxn 100010
char s[maxn], t[maxn];
int main()
{
	while (1)
	{
		scanf("%s", s);
		if (s[0] == '0') break;
		scanf("%s", t);
		int n = strlen(s), m = strlen(t);
		for (int i = 0, j = 0; i < m; ++i, j = (j + 1) % n)
			printf("%c", (t[i] - 'A' + s[j] - 'A' + 1) % 26 + 'A');
		puts("");
	}
	return 0;
}
