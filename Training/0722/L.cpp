#include <cstdio>

#define maxn 100010
const int oo = 1e5;
int k[maxn << 2], b[maxn << 2], tagk[maxn << 2], tagb[maxn << 2];
void build(int o, int l, int r)
{
	k[o] = 1; b[o] = 0;
	tagk[o] = 1; tagb[o] = 0;
	if (l == r) return ;
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
}
int ql, qr, qv;
void set_tag(int o, int kk, int bb)
{
	tagk[o] *= kk;
	k[o] *= kk;
	tagb[o] = tagb[o] * kk + bb;
	b[o] = b[o] * kk + bb;
}
void pushdown(int o)
{
	set_tag(o << 1, tagk[o], tagb[o]);
	set_tag(o << 1 | 1, tagk[o], tagb[o]);
	tagk[o] = 1; tagb[o] = 0;
}
int query(int o, int l, int r)
{
	//printf("%d %d %d %d\n", l, r, k[o], b[o]);
	if (l == r)
		return k[o] * l + b[o];
	pushdown(o);
	int mid = l + r >> 1;
	if (ql <= mid) return query(o << 1, l, mid);
	else return query(o << 1 | 1, mid + 1, r);
}
void modify(int o, int l, int r)
{
	if (ql <= l && r <= qr)
	{
		set_tag(o, -1, 2 * qv);
		return ;
	}
	int mid = l + r >> 1;
	pushdown(o);
	if (ql <= mid) modify(o << 1, l, mid);
	if (mid < qr) modify(o << 1 | 1, mid + 1, r);
}
int main()
{
	freoepn("reflection.in", "r", stdin);
	int T; scanf("%d", &T);
	for (; T; --T)
	{
		int Q; scanf("%d", &Q);
		build(1, 0, oo);
		for (int i = 1; i <= Q; ++i)
		{
			int x, y; scanf("%d", &x); ql = x;
			y = query(1, 0, oo);
			printf("%d\n", y);
			ql = x; qr = oo; qv = y;
			modify(1, 0, oo);
		}
	}
	return 0;
}
/*
1
5
1
2
1
3
4
*/
