#include <cstdio>

#define maxn 100010
char op[maxn];
int num[maxn], tr[maxn], fl[maxn], sum[maxn];
bool ans[maxn];
int main()
{
freopen("truth.in", "r", stdin);
freopen("truth.out", "w", stdout);
	int n; scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		char s[3]; scanf("%s", s); op[i] = s[0];
		if (s[0] == '$') scanf("%d", num + i);
	}
	bool find = 0;
	int tot = 0;
	for (int i = 0; i < n; ++i)
		if (op[i] == '$')
		{
			find = 1; bool lst = 1; ++tr[num[i]];
			for (int j = (i + n - 1) % n; op[j] != '$'; j = (j + n - 1) % n)
				lst = op[j] == '+' ? lst : !lst, tr[num[i]] += lst, fl[num[i]] += !lst, tot += !lst;
		}
	if (find)
	{
		for (int i = 0; i <= n; ++i)
		{
			int x = tot - fl[i] + tr[i];
			if (i == x)
			{
				for (int j = 0; j < n; ++j)
					if (op[j] == '$')
					{
						ans[j] = num[j] == i;
						for (int kk = j, k = (j + n - 1) % n; op[k] != '$'; k = ((kk = k) + n - 1) % n)
							ans[k] = op[k] == '+' ? ans[kk] : !ans[kk];
					}
				puts("consistent");
				for (int j = 0; j < n; ++j) printf("%c", ans[j] ? 't' : 'f'); puts("");
				return 0;
			}
		}
	}
	else
	{
	for (int i = 0; i < 2; ++i)
	{
		ans[0] = i;
		for (int j = 0; j < n - 1; ++j)
			if (op[j] == '+')
				ans[j + 1] = ans[j];
			else ans[j + 1] = !ans[j];
		bool next = op[n - 1] == '+' ? ans[n - 1] : !ans[n - 1];
		if (next != ans[0]) continue;
		puts("consistent");
		for (int j = 0; j < n; ++j) printf("%c", ans[j] ? 't' : 'f'); puts("");
		return 0;
	}
	}
	puts("inconsistent");
	return 0;
}
