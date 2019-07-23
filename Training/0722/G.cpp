#include <cstdio>
#include <map>
#include <cstring>
#include <algorithm>

#define maxn 200010
std::map<std::pair<int, int>, int> id, ed;
struct edge {
	int a, b, w, fa, fb;
	inline bool operator < (const edge &that) const {return w < that.w;}
} e[maxn];
int fa[maxn], Fa[maxn], size[maxn];
int Find(int x) {return Fa[x] == x ? x : Fa[x] = Find(Fa[x]);}
int st[maxn], top, opst[maxn];
int main()
{
//freopen("robot.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int n, m, q, ecnt = 0, idcnt = 0; scanf("%d%d%d", &n, &m, &q);
		id.clear(); ed.clear(); top = 0;
		for (int i = 1; i <= n; ++i) Fa[i] = i;
		for (int i = 1; i <= m; ++i)
		{
			int a, b, w; scanf("%d%d%d", &a, &b, &w);
			e[++ecnt] = (edge) {a, b, w};
		}
		std::sort(e + 1, e + ecnt + 1);
		for (int i = 1, j = 1; i <= m; i = j)
		{
			while (j <= m && e[i].w == e[j].w) ++j;
			for (int k = i; k < j; ++k)
				if (Find(e[k].a) != Find(e[k].b))
				{
					if (!id[std::make_pair(Find(e[k].a), e[k].w)]) id[std::make_pair(Find(e[k].a), e[k].w)] = ++idcnt;
					if (!id[std::make_pair(Find(e[k].b), e[k].w)]) id[std::make_pair(Find(e[k].b), e[k].w)] = ++idcnt;
					e[k].fa = id[std::make_pair(Find(e[k].a), e[k].w)];
					e[k].fb = id[std::make_pair(Find(e[k].b), e[k].w)];
					ed[std::make_pair(e[k].a, e[k].b)] = ed[std::make_pair(e[k].b, e[k].a)] = k;
				}
			for (int k = i, f1, f2; k < j; ++k)
				if ((f1 = Find(e[k].a)) != (f2 = Find(e[k].b)))
					Fa[f1] = f2;
		}
		memset(fa, 0, (idcnt + 1) << 2);
		memset(opst, 0, (q + 1) << 2);
		for (int i = 1; i <= idcnt; ++i) size[i] = 1;
		int err = 0;
		for (; q; --q)
		{
			int op; scanf("%d", &op);
			if (op == 1)
			{
				while (top)
				{
					if (top > 1)
					{
						if (opst[top - 1])
						{
							int x = opst[top - 1], f = fa[x];
							fa[x] = 0; size[f] -= size[x];
							opst[top - 1] = 0;
						}
						else --err;
					}
					--top;
				}
			}
			else if (op == 2)
			{
				int x; scanf("%d", &x);
				if (top)
				{
					int v = st[top];
					if (ed[std::make_pair(x, v)])
					{
						int a = e[ed[std::make_pair(x, v)]].fa, b = e[ed[std::make_pair(x, v)]].fb;
						for (; fa[a]; a = fa[a]) ;
						for (; fa[b]; b = fa[b]) ;
						if (a == b) ++err;
						else
						{
							if (size[a] > size[b]) std::swap(a, b);
							opst[top] = a;
							fa[a] = b; size[b] += size[a];
						}
					}
					else ++err;
				}
				st[++top] = x;
				puts(err ? "n" : "y");
			}
			else if (op == 3)
			{
				if (!top) continue;
				if (top > 1)
				{
					if (opst[top - 1])
					{
						int x = opst[top - 1], f = fa[x];
						fa[x] = 0; size[f] -= size[x];
						opst[top - 1] = 0;
					}
					else --err;
				}
				--top;
			}
		}
	}
	return 0;
}
