#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>	

#define maxn 110
typedef double db;
const db eps = 1e-9;
struct Trie {
	Trie *next[6], *fail;
	bool end;
} mem[maxn], *tot = mem, *end[maxn], *q[maxn];
inline void build()
{
	int head = 0, tail = 0;
	for (int i = 0; i < 6; ++i)
		if (!mem -> next[i]) mem -> next[i] = mem;
		else (q[++tail] = mem -> next[i]) -> fail = mem;
	while (head < tail)
	{
		Trie *now = q[++head];
		for (int i = 0; i < 6; ++i)
			if (!now -> next[i])
				now -> next[i] = now -> fail -> next[i];
			else (q[++tail] = now -> next[i]) -> fail = now -> fail -> next[i];
	}
}
db b[maxn][maxn], x[maxn];
int main()
{
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, L; scanf("%d%d", &n, &L);
		memset(mem -> next, 0, sizeof (mem -> next)); tot = mem; tot -> end = 0;
		memset(b, 0, sizeof (b));
		for (int i = 1; i <= n; ++i)
		{
			Trie *now = mem;
			for (int j = 1; j <= L; ++j)
			{
				int x; scanf("%d", &x); --x;
				if (!now -> next[x])
				{
					now -> next[x] = ++tot;
					memset(tot -> next, 0, sizeof tot -> next); tot -> end = 0;
				}
				now = now -> next[x];
			}
			end[i] = now;
			now -> end = 1;
		}
		build();
		
		
		/*for (Trie *it = mem; it <= tot; ++it)
			for (int i = 0; i < 6; ++i)
				printf("(%d -> %d) = %d\n", it - mem, i, it -> next[i] - mem);*/
		
		int num = tot - mem;
		for (int i = 1; i <= n; ++i) b[0][end[i] - mem] = 1;
		b[0][num + 1] = 1;
		for (int i = 1; i <= num; ++i) b[i][i] = -1;
		for (Trie *it = mem; it <= tot; ++it)
			for (int i = 0; i < 6; ++i)
				if (it -> next[i] != mem && !it -> end)
					b[it -> next[i] - mem][it - mem] += 1. / 6.;

		/*for (int i = 0; i <= num + 1; ++i, puts(""))
			for (int j = 0; j <= num + 1; ++j)
				printf("%.3lf ", b[i][j]);*/

		for (int i = 0; i <= num; ++i)
		{
			if (fabs(b[i][i]) < eps)
			{
				int maxx = i;
				for (int j = i + 1; j <= num; ++j)
					if (fabs(b[j][i]) > fabs(b[maxx][i])) maxx = j;
				for (int j = i; j <= num + 1; ++j)
					std::swap(b[i][j], b[maxx][j]);
			}
			for (int j = i + 1; j <= num; ++j)
			{
				db tmp = b[j][i] / b[i][i];
				for (int k = i; k <= num + 1; ++k)
					b[j][k] -= b[i][k] * tmp;
			}
		}
		x[num] = b[num][num + 1] / b[num][num];
		for (int i = num - 1; ~i; --i)
		{
			for (int j = i + 1; j <= num; ++j)
				b[i][num + 1] -= x[j] * b[i][j];
			x[i] = b[i][num + 1] / b[i][i];
		}
		/*for (int i = 1; i <= num; ++i)
			printf("%.6lf%c", x[i], " \n"[i == num]);*/
		for (int i = 1; i <= n; ++i)
			printf("%.6lf%c", x[end[i] - mem], " \n"[i == n]);
	}
	return 0;
}
/*
3
5 1
1
2
3
4
5
6 2
1 1
2 1
3 1
4 1
5 1
6 1
4 3
1 2 3
2 3 4
3 4 5
4 5 6
*/
