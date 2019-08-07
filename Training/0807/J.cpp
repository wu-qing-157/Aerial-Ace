#include <cstdio>
#include <cstring>

#define maxn 100010
char s[maxn];
bool c[maxn];
int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
int main()
{
	int n, ans = 0;
	scanf("%s", s);
	n = strlen(s);
	for (int i = 1; i <= n; ++i)
		if (n % i == 0)
		{
			for (int j = 0; j < i; ++j)
				if (s[j] == 'R')
				{
					bool flag = 1;
					for (int k = j + i; k != j; (k += i) %= n)
						flag &= s[k] == 'R';
					if (flag)
					{
						c[i] = 1;
						break;
					}
				}
		}
	for (int i = 1; i < n; ++i)
		ans += c[gcd(i, n)];
	printf("%d\n", ans);
	return 0;
}
