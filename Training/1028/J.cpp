#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#define maxn 20
const int inf = 0x7fffffff;
std::string str[maxn];
std::vector<std::string> s[maxn];
int f[maxn][1 << 16], g[maxn][1 << 16];
inline bool cmp(std::string a, std::string b)
{
	int n = a.size(), m = b.size();
	for (int i = 0; i < n || i < m; ++i)
	{
		if (i == n) return 1;
		if (i == m) return 0;
		if (a[i] != b[i]) return a[i] < b[i];
	}
	return 0;
}
int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		std::cin >> str[i];
	for (int i = 1; i <= n; ++i)
	{
		int m = str[i].size();
		for (int S = 1; S < (1 << m); ++S)
		{
			std::string tmp = "";
			for (int j = 0; j < m; ++j)
				if (S & (1 << j))
					tmp += str[i][j];
			s[i].push_back(tmp);
		}
		std::sort(s[i].begin(), s[i].end(), cmp);
	}
	for (int i = 0; i < s[1].size(); ++i)
	{
		f[1][i] = s[1][i].size();
		if (i > 0) g[1][i] = std::max(f[1][i], g[1][i - 1]);
		else g[1][i] = f[1][i];
	}
	for (int i = 2; i <= n; ++i)
	{
		int j = 0;
		for (auto ss : s[i])
		{
			int pos = std::lower_bound(s[i - 1].begin(), s[i - 1].end(), ss, cmp) - s[i - 1].begin() - 1;
			if (pos >= 0) f[i][j] = g[i - 1][pos] + ss.size();
			else f[i][j] = -inf;
			++j;
		}
		g[i][0] = f[i][0];
		for (j = 1; j < s[i].size(); ++j)
			g[i][j] = std::max(g[i][j - 1], f[i][j]);
	}
	printf("%d\n", g[n][s[n].size() - 1] < 0 ? -1 : g[n][s[n].size() - 1]);
	return 0;
}
