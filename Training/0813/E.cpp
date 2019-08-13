#include <cstdio>
#include <algorithm>
#include <vector>

#define maxn 30
int p[maxn], n, k;
std::vector<std::vector<int> > v;
bool find;
void dfs(int step, int S)
{
	if (step == n + 1)
	{
		--k;
		if (k == 0)
		{
			for (int i = 1; i <= n; ++i) printf("%d%c", p[i], " \n"[i == n]);
			find = 1;
		}
		return ;
	}
	for (int x, tS = S; tS; tS -= 1 << x)
	{
		x = __builtin_ctz(tS);
		p[step] = x + 1;
		dfs(step + 1, S - (1 << x));
		if (find) return ;
	}
}
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		scanf("%d%d", &n, &k);
		if (n <= 8)
		{
			v.clear();
			for (int i = 1; i <= n; ++i) p[i] = i;
			do {
				std::vector<int> vv;
				for (int i = 2; i <= n; ++i) vv.push_back(p[i] - p[i - 1]);
				vv.push_back(p[1]);
				v.push_back(vv);
			} while (std::next_permutation(p + 1, p + n + 1));
			std::sort(v.begin(), v.end());

			/*printf("%d\n", k);
			for (int it : v[k - 1]) printf("%d ", it); puts("");*/
			p[1] = v[k - 1][n - 1];
			printf("%d", p[1]);
			for (int i = 0; i < n - 1; ++i)
				printf(" %d", p[i + 2] = p[i + 1] + v[k - 1][i]);puts("");
		}
		else
		{
			find = 0;
			p[1] = n;
			dfs(2, (1 << (n - 1)) - 1);
		}
	}
	return 0;
}
