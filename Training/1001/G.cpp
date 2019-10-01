#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define maxn 300010
const int mod = 998244353;
struct SAM {
	SAM *next[26], *fa;
	int val, size, ans;
	int len() {
		if (fa) return val - fa -> val;
		else return val;
	}
} mem[maxn << 1], *last = mem, *tot = mem;
void extend(int c)
{
	SAM *p = last, *np;
	last = np = ++tot; np -> val = p -> val + 1; np -> size = 1;
	for (; p && !p -> next[c]; p = p -> fa) p -> next[c] = np;
	if (!p) np -> fa = mem;
	else
	{
		SAM *q = p -> next[c];
		if (q -> val == p -> val + 1) np -> fa = q;
		else
		{
			SAM *nq = ++tot;
			memcpy(nq -> next, q -> next, sizeof nq -> next);
			nq -> val = p -> val + 1;
			nq -> fa = q -> fa;
			q -> fa = np -> fa = nq;
			for (; p && p -> next[c] == q; p = p -> fa) p -> next[c] = nq;
		}
	}
}
int sr[maxn];
inline bool cmp(int a, int b) {return mem[a].val > mem[b].val;}
char s[maxn];

std::vector<int>rG[maxn];

int main()
{
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	for (int i = 1; i <= n; ++i)
		extend(s[i] - 'a');
	for (int i = 1; i <= (tot - mem); ++i)
		sr[i] = i;
	int ans = 0;
	std::sort(sr + 1, sr + (tot - mem) + 1, cmp);
	
	for (int i = 1; i <= (tot - mem); ++i) 
		for (int c = 0; c < 26; c++) {
			int j = mem[i].next[c] - mem;
			if (j <= 0) continue;
			rG[j].push_back(i);
		}
		
	mem[sr[1]].ans = 1;
	for (int i = 1; i <= (tot - mem); ++i)
	{
		mem[sr[i]].fa -> size += mem[sr[i]].size;
		//ans = (ans + 1ll * (mem[sr[i]].val - mem[sr[i]].fa -> val) * mem[sr[i]].size) % mod;
		
		(mem[sr[i]].fa ->ans += 1ll * mem[sr[i]].ans * mem[sr[i]].fa -> len() % mod) %= mod;
		for (auto f : rG[sr[i]])
			(mem[f].ans += mem[sr[i]].ans) %= mod;
		(ans += mem[sr[i]].ans) %= mod;
		//printf("i %d fa %d len %d size %d\n", sr[i], (int) (mem[sr[i]].fa - mem), mem[sr[i]].val, mem[sr[i]].size);
	}
	printf("%d\n", ans);
	return 0;
}
