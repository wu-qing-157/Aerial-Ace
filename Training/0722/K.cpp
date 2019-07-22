#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 100010
#define maxm 110
typedef long long ll;
char s[maxn], t[maxm];
int fail[maxm];
ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
struct Frac {
	ll a, b;
	void simply()
	{
		ll gcc = gcd(a, b);
		a /= gcc; b /= gcc;
	}
	inline void operator += (const Frac &that) {
		ll gcc = gcd(b, that.b);
		a = a * that.b + b * that.a;
		b = b * that.b;
		simply();
	}
} ans;
ll prenum[maxn][maxm], preval[maxn][maxm], suf[maxn][maxm];
int main()
{
//freopen("string.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%s%s", s + 1, t + 1);
		int q; scanf("%d", &q);
		int n = strlen(s + 1), m = strlen(t + 1);
		for (int i = 2, j = 0; i <= m; ++i)
		{
			for (; j && t[j + 1] != t[i]; j = fail[j]) ;
			t[i] == t[j + 1] ? ++j : 0;
			fail[i] = j;
		}
		
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= m; ++j)
				prenum[i][j] = preval[i][j] = suf[i][j] = 0;
		for (int i = 1, j = 0, num = 0; i <= n; ++i)
		{
			while (j && s[i] != t[j + 1]) j = fail[j];
			s[i] == t[j + 1] ? ++j : 0;
			if (j == m) j = fail[j], ++num;
			++prenum[i][j]; preval[i][j] += num;
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 0; j < m; ++j)
			{
				prenum[i][j] += prenum[i - 1][j],
				preval[i][j] += preval[i - 1][j];
				//printf("%d %d\n", prenum[i][j], preval[i][j]);
			}
		for (int i = n; i; --i)
		{
			for (int j = 0, nj; j < m; ++j)
			{
				nj = j;
				while (nj && s[i] != t[nj + 1]) nj = fail[nj];
				s[i] == t[nj + 1] ? ++nj : 0;
				if (nj == m) suf[i][j] = suf[i + 1][fail[nj]] + 1;
				else suf[i][j] = suf[i + 1][nj];
			}
		}
		for (int i = n; i; --i)
			for (int j = 0; j < m; ++j)
				suf[i][j] += suf[i + 1][j];
		for (; q; --q)
		{
			int l, r; scanf("%d%d", &l, &r); ans = (Frac) {0, 1};
			ll sum = 0;
			for (int j = 0; j < m; ++j)
				if (prenum[l][j])
					sum += 1ll * suf[r][j] * prenum[l][j] + 1ll * preval[l][j] * (n - r + 1);
			ans = (Frac) {sum, 1ll * l * (n - r + 1)}; ans.simply();
			printf("%lld/%lld\n", ans.a, ans.b);
		}
	}
	return 0;
}
/*
4
abaabaxbba
aba
4
2 7
1 5
6 9
4 5
abbaabxabba
aba
4
2 7
1 5
6 9
4 5
abbababbxaabaxabababxxa
abba
5
10 20
11 12
5 21
12 20
15 18
aaaaaaaaaa
aa
4
1 2
2 5
2 9
5 8
*/
