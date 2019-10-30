#include <cstdio>
#include <bitset>

#define maxn 1010
int n, m;
char mp[maxn][maxn];
struct Base {
	std::bitset<maxn> b[maxn];
	int cnt;
	inline void insert(std::bitset<maxn> bb)
	{
		for (int pos; bb.count(); )
		{
			pos = bb._Find_first();
			if (!b[pos].count())
			{
				//b[pos] = bb;
				++cnt;
				
				for (int i = 1; i <= m; i++)
					if (b[i][i] && bb[i]) 
						bb ^= b[i];
				
				for (int i = 1; i <= m; ++i)
					if (i != pos && b[i][pos] != 0)
						b[i] ^= bb;
				b[pos] = bb;
				return ;
			}
			bb ^= b[pos];
		}
	}
} st[20], tt;
std::bitset<maxn> bt[maxn], tmp;
int ans[maxn][maxn];
void solve(int step, int l, int r)
{
	if (l == r)
	{
		tmp = bt[l];
		for (int i = 1; i <= m; ++i)
			if (st[step].b[i][i] != 0 && tmp[i] != 0)
				tmp ^= st[step].b[i];
		
		for (int i = 1; i <= m; ++i)
			if (st[step].b[i][i] != 0)
			{
				tmp.flip(i);
				if (0)
				{
				puts("OK");
				for (int j = 1; j <= m; ++j)
					printf("%d", int(st[step].b[i][j])); puts("");
				for (int j = 1; j <= m; ++j)
					printf("%d", tmp[j] ^ st[step].b[i][j]); puts("");
				}
				if ((tmp ^ st[step].b[i]).count() != 0)
					ans[l][i] = st[step].cnt + 1;
				else ans[l][i] = st[step].cnt;
				tmp.flip(i);
			}
			else
			{
				tmp.flip(i);
				if (tmp.count()) ans[l][i] = st[step].cnt + 1;
				else ans[l][i] = st[step].cnt;
				tmp.flip(i);
			}
		return ;
	}
	int mid = l + r >> 1;
		
	st[step + 1] = st[step];
	for (int i = mid + 1; i <= r; ++i)
		st[step + 1].insert(bt[i]);
	solve(step + 1, l, mid);
	
	st[step + 1] = st[step];
	for (int i = l; i <= mid; ++i)
		st[step + 1].insert(bt[i]);
	solve(step + 1, mid + 1, r);
}
int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%s", mp[i] + 1);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
			bt[i][j] = mp[i][j] - '0';
		tt.insert(bt[i]);
	}
	solve(0, 1, n);
	for (int i = 1; i <= n; ++i, puts(""))
		for (int j = 1; j <= m; ++j)
			printf("%c", ans[i][j] == tt.cnt ? '0' : ans[i][j] < tt.cnt ? '-' : '+');
	return 0;
}
