#include <cstdio>
#include <cstring>

#define maxn 110
char s[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%s", s + 1);
		int p = 1, n = strlen(s + 1);
		for (; p <= n && s[p] == 'y'; ++p) ;
		if (p <= n && s[p] == 'z') s[p] = 'b';
		puts(s + 1);
	}
	return 0;
}
