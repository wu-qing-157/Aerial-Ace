#include <cstdio>
#include <cstring>
#include <unordered_set>

#define maxn 10010
const int m1 = 19260817;
const int m2 = 1e9 + 7;
int pw1[maxn], pw2[maxn];
struct Hash {
	int h1, h2;
	inline Hash operator + (const char &that) const {return (Hash) {int((29ll * h1 + (that - 'a' + 1)) % m1), int((33ll * h2 + (that - 'a' + 1)) % m2)};}
	inline Hash operator << (const int &that) const {return (Hash) {int(1ll * h1 * pw1[that] % m1), int(1ll * h2 * pw2[that] % m2)};}
	inline Hash operator - (const Hash &that) const {return (Hash) {(h1 - that.h1 + m1) % m1, (h2 - that.h2 + m2) % m2};}
	inline bool operator == (const Hash &that) const {return h1 == that.h1 && h2 == that.h2;}
} pre[maxn];
struct hhh {
	size_t operator () (const Hash &that) const {return that.h1 * 233u + that.h2;}
} ;
inline Hash query(int l, int r)
{
	return pre[r] - (pre[l - 1] << (r - l + 1));
}
std::unordered_set<Hash, hhh> s, ans;
char str[maxn];
int main()
{
//	freopen("seti.in", "r", stdin);
//	freopen("seti.out", "w", stdout);
	scanf("%s", str + 1);
	int n = strlen(str + 1);
	for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + str[i];
	pw1[0] = pw2[0] = 1;
	int num = 0;
	for (int i = 1; i <= n; ++i)
		pw1[i] = 29ll * pw1[i - 1] % m1,
		pw2[i] = 33ll * pw2[i - 1] % m2;
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 1; j < i; ++j)
		{
			Hash hh = query(j, i - 1);
			s.insert(hh);
		}
		for (int j = i; j <= n; ++j)
		{
			Hash hh = query(i, j);
			if (s.count(hh)) ans.insert(hh);
		}
	}
	printf("%d\n", (int) ans.size());
	return 0;
}
/*
abacabacaba
*/
