#include <cstdio>
#include <cstring>
#include <algorithm>

#define maxn 300010
char str[maxn];
int next[maxn][26], fail[maxn], len[maxn], cnt[maxn], last, tot, n;
int state[maxn];
inline int new_node(int l)
{
	len[++tot] = l;
	return tot;
}
inline void init()
{
	tot = -1;
	new_node(0);
	new_node(-1);
	str[0] = -1;
	fail[0] = 1;
}
inline int get_fail(int x)
{
	while (str[n - len[x] - 1] != str[n]) x = fail[x];
	return x;
}
inline void extend(int c)
{
	++n;
	int cur = get_fail(last);
	if (!next[cur][c])
	{
		int now = new_node(len[cur] + 2);
		fail[now] = next[get_fail(fail[cur])][c];
		next[cur][c] = now;
		state[now] = state[cur] | (1 << c);
	}
	last = next[cur][c];
	++cnt[last];
}
long long ans;
inline void count()
{
	for (int i = tot; i; --i)
	{
		cnt[fail[i]] += cnt[i];
		ans += 1ll * __builtin_popcount(state[i]) * cnt[i];
	}
}
int main()
{
	scanf("%s", str + 1);
	init();
	for (int i = 1; str[i]; ++i)
		extend(str[i] - 'a');
	count();
	printf("%lld\n", ans);
}
