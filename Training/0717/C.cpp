#include <cstdio>
#include <algorithm>

#define maxn 100010
struct Opt {
	char s[20];
	int x;
} op[maxn];
int st[maxn];
const int oo = 1e9;
inline bool in_bound(long long x) {return -oo <= x && x <= oo;}
int main()
{
	while (1)
	{
		int num = 0;
		while (1)
		{
			++num;
			scanf("%s", op[num].s);
			if (op[num].s[0] == 'Q') return 0;
			if (op[num].s[0] == 'E') break;
			if (op[num].s[0] == 'N') scanf("%d", &op[num].x);
		}
		int n; scanf("%d", &n);
		int top = 0;
		for (; n; --n)
		{
			int x, top = 0; scanf("%d", &x);
			st[++top] = x;
			bool error = 0;
			for (int i = 1; i < num && !error; ++i)
			{
				if (op[i].s[0] == 'N') st[++top] = op[i].x;
				else if (op[i].s[0] == 'P') top > 0 ? --top : error = 1;
				else if (op[i].s[0] == 'I') top > 0 ? st[top] = -st[top] : error = 1;
				else if (op[i].s[0] == 'D')
				{
					if (op[i].s[1] == 'I') top > 1 && st[top] != 0 ? st[top - 1] /= st[top], --top : error = 1;
					else {top > 0 ? x = st[top], st[++top] = x : error = 1;}
				}
				else if (op[i].s[0] == 'S')
				{
					if (op[i].s[1] == 'W') top > 1 ? std::swap(st[top - 1], st[top]), 1 : error = 1;
					else top > 1 && in_bound(st[top - 1] - st[top]) ? st[top - 1] -= st[top], --top : error = 1;
				}
				else if (op[i].s[0] == 'M')
				{
					if (op[i].s[1] == 'U')
						top > 1 && in_bound(1ll * st[top - 1] * st[top]) ? st[top - 1] *= st[top], --top : error = 1;
					else top > 1 && st[top] != 0 ? st[top - 1] %= st[top], --top : error = 1;
				}
				else if (op[i].s[0] == 'A')
					top > 1 && in_bound(st[top - 1] + st[top]) ? st[top - 1] += st[top], --top : error = 1;
			}
			if (error || top != 1) puts("ERROR");
			else printf("%d\n", st[top]);
		}
		puts("");
	}
	return 0;
}
/*
DUP
MUL
NUM 2
ADD
END
3
1
10
50

NUM 1
NUM 1
ADD
END
2
42
43

NUM 600000000
ADD
END
3
0
600000000
1

QUIT
*/
