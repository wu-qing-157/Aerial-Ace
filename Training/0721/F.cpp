#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <map>

#define maxn 100010
int lst, st[maxn], top, rnum[maxn];
char s[maxn];
std::string name, func[233];
std::map<std::pair<std::string, int>, int> node;
int fnum, bpos[maxn];
struct Edge {
	Edge *next;
	int to;
} *last[maxn], e[maxn * 100], *ecnt = e;
int deg[maxn], q[maxn];
inline void link(int a, int b)
{
	++deg[b];
	*++ecnt = (Edge) {last[a], b}; last[a] = ecnt;
}
int main()
{
	int lst = 0, node_cnt = 0;
	while (1)
	{
		if (scanf("%s", s + lst) == EOF) break;
		lst += strlen(s + lst);
	}
	for (int i = 0; i < lst; ++i)
	{
		name.push_back(s[i]);
		if (s[i] == '{') ++top;
		else if (s[i] == '}')
		{
			--top;
			if (!top) func[++fnum] = name, name = "";
		}
	}
	for (int I = 1; I <= fnum; ++I)
	{
		std::string fun = func[I];
		int pos = 0, small = 0;
		for (; pos < fun.size(); ++pos)
		{
			if (fun[pos] == '{') break;
			if (fun[pos] == '(') small = pos;
			if (fun[pos] == ',') ++rnum[I];
		}
		bpos[I] = pos;
		if (fun[small + 1] == ')') --rnum[I];
		std::string my_name = "";
		for (int i = 0; i < small; ++i) my_name.push_back(fun[i]);
		
		
		for (int S = 0; S < (1 << rnum[I]); ++S) node[make_pair(my_name, S)] = ++node_cnt;
		//std::cout << my_name << std::endl;
	}
	for (int I = 1; I <= fnum; ++I)
	{
		std::map<std::string, int> rid;
		std::string fun = func[I], now = "";
		int rr = 0;
		for (int i = small + 1; ; ++i)
		{
			if (fun[i] == ',' || fun[i] == ')')
			{
				if (now.size()) rid[now] = rr++, now = "";
				if (fun[i] == ')') break;
			}
			else now.push_back(fun[i]);
		}
		for (int S = 0; S < (1 << rnum[I]); ++S)
		{
			top = 0;
			bool val[20];
			for (int i = 0; i < rnum[I]; ++i) val[i] = S >> i & 1;+ 
			for (int i = bpos[I]; i < fun.size(); ++i)
			{
				if (fun[i] == '(') ;
				if ()
			}
		}
	}
	int head = 0, tail = 0;
	for (int i = 1; i <= nodecnt; ++i)
		if (!deg[i]) q[++tail] = i;
	while (head < tail)
	{
		int now = q[++head];
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (--deg[iter -> to] == 0) q[++tail] = iter -> to;
	}
	for (int i = 1; i <= nodecnt; ++i)
		if (deg[i]) {puts("NO"); return 0;}
	puts("YES");
	return 0;
}
