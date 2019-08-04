#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 100010
int n, k;
char s[maxn];
int next[maxn][26], size[maxn][26], nw[26], L[26], R[26];;
bool flag;
char st[maxn];
inline bool check(int pos)
{
	int s1 = 0, s2 = 0;
	for (int i = 0; i < 26; ++i)
	{
		if (size[pos][i] + nw[i] < L[i]) return 0;
		if (nw[i] > R[i]) return 0;
		s1 += std::max(nw[i], L[i]);
		s2 += std::min(nw[i] + size[pos][i], R[i]);
	}
	if (s1 > k || s2 < k) return 0;
	return 1;
}
void dfs(int pos, int len)
{
	if (len == k)
	{
		for (int i = 1; i <= k; ++i) printf("%c", st[i]); puts("");
		flag = 1;
		return ;
	}
	for (int i = 0; i < 26; ++i)
		if (next[pos][i])
		{
			++nw[s[next[pos][i]] - 'a'];
			st[len + 1] = i + 'a';
			if (check(next[pos][i]))
			{
				dfs(next[pos][i], len + 1);
				return ;
			}
			--nw[s[next[pos][i]] - 'a'];
		}
}
int main()
{
	while (scanf("%s%d", s + 1, &k) != EOF)
	{
		for (int i = 0; i < 26; ++i) scanf("%d%d", L + i, R + i);
		n = strlen(s + 1);
		memset(next[n], 0, sizeof (next[n]));
		memset(size[n], 0, sizeof (size[n]));
		memset(nw, 0, sizeof (nw));
		flag = 0;
		for (int i = n; i; --i)
		{
			memcpy(next[i - 1], next[i], sizeof (next[i]));
			next[i - 1][s[i] - 'a'] = i;
			
			memcpy(size[i - 1], size[i], sizeof (size[i]));
			size[i - 1][s[i] - 'a']++;
		}
		dfs(0, 0);
		if (!flag) puts("-1");
	}
	return 0;
}
