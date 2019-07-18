#include <cstdio>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <iostream>

#define maxn 100010
std::string tans;
char ss1[110], ss2[110];
char t[maxn], as[110], ans[110];
bool ambi;
const int m1 = 19260817;
const int m2 = 1e9 + 7;
inline int qpow(int base, int power, int mod)
{
	int ret = 1;
	for (; power; power >>= 1, base = 1ll * base * base % mod)
		power & 1 ? ret = 1ll * ret * base % mod : 0;
	return ret;
}
int pw1[110], pw2[110], inv1[110], inv2[110];
struct Hash {
	int h1, h2;
	inline Hash operator + (const char &that) const
	{return (Hash) {int((h1 * 29ll + that - 'A') % m1), int((h2 * 33ll + that - 'A') % m2)};}
	inline Hash operator + (const Hash &that) const
	{return (Hash) {(h1 + that.h1) % m1, (h2 + that.h2) % m2};}
	inline Hash operator - (const Hash &that) const
	{return (Hash) {(h1 - that.h1 + m1) % m1, (h2 - that.h2 + m2) % m2};}
	inline Hash operator << (const int that) const
	{return (Hash) {int(1ll * h1 * pw1[that] % m1), int(1ll * h2 * pw2[that] % m2)};}
	inline Hash operator >> (const int that) const
	{return (Hash) {int(1ll * h1 * inv1[that] % m1), int(1ll * h2 * inv2[that] % m2)};}
	inline bool operator == (const Hash &that) const
	{return h1 == that.h1 && h2 == that.h2;}
} pre1[maxn][110], pre2[maxn][110];
struct hashhh {
	size_t operator () (const Hash &a) const {return a.h1 * 233u + a.h2;}
} ;
inline Hash query(Hash *p, int l, int r)
{
	return p[r + 1] - (p[l] << (r - l + 1));
}
std::unordered_map<Hash, int, hashhh> mp;
template<class T>
void work(char *s1, char *s2, int n, T p1, T p2, int l1, int l2)
{
	// printf("n = %d\n", n );
	mp.clear();
	int lt = strlen(t), num = 0;
	for (int i = 0; i + l1 - 1 < lt; ++i)
	{
		if (query(p1[i], 0, l1 - n - 1) == query(p1[i], n, l1 - 1))
		{
			// printf("%d\n", i );
			Hash h = (query(p1[i], (n - i % n) % n, n - 1) << ((n - i % n) % n)) + (query(p1[i], 0, (n - i % n) % n - 1));
			// printf("%d %d\n", h.h1, h.h2);
			if (!mp.count(h))
				mp[h] = i;
		}
	}
	int fir = 0;
	for (int i = 0; i + l2 - 1 < lt; ++i)
	{
		if (query(p2[i], 0, l2 - n - 1) == query(p2[i], n, l2 - 1))
		{
			Hash h = (query(p2[i], (n - i % n) % n, n - 1) << ((n - i % n) % n)) + (query(p2[i], 0, (n - i % n) % n - 1));
			if (mp.count(h) && mp[h] + l1 <= i)
			{
				if (num) {ambi = 1; return ;}
				++num;
				fir = i;
				mp.erase(h);
			}
		}
	}
	if (num >= 2) ambi = 1;
	else if (num)
	{
		for (int i = 0; i < l2; ++i)
			ans[(i + fir) % n] = (t[fir + i] - s2[i] + 25) % 26 + 'A';
		std::string ta = "";
		for (int i = 0; i < lt; ++i) ta.push_back((t[i] - ans[i % n] + 25) % 26 + 'A');
		//std::cout << ta << std::endl;
		if (tans.size() && tans != ta) ambi = 1;
		else tans = ta;
	}
}
int main()
{
	int nn;
	pw1[0] = pw2[0] = inv1[0] = inv2[0] = 1;
	int inv29 = qpow(29, m1 - 2, m1), inv33 = qpow(33, m2 - 2, m2);
	for (int i = 1; i <= 100; ++i)
	{
		pw1[i] = pw1[i - 1] * 29ll % m1;
		inv1[i] = 1ll * inv1[i - 1] * inv29 % m1;
		pw2[i] = pw2[i - 1] * 33ll % m2;
		inv2[i] = 1ll * inv2[i - 1] * inv33 % m2;
	}
	while (scanf("%d", &nn) != EOF)
	{
		if (!nn) return 0;
		scanf("%s", ss1); scanf("%s", ss2);
		scanf("%s", t);
		int num = 0; tans.clear();
		ambi = 0;
		int lt = strlen(t), l1 = strlen(ss1), l2 = strlen(ss2);
		for (int i = 0; i < lt; ++i)
		{
			for (int j = 0; j < l1; ++j)
				pre1[i][j + 1] = pre1[i][j] + ((t[i + j] - ss1[j] + 25) % 26 + 'A');

			for (int j = 0; j < l2; ++j)
				pre2[i][j + 1] = pre2[i][j] + ((t[i + j] - ss2[j] + 25) % 26 + 'A');
		}
		for (int n = 1; n <= nn && !ambi; ++n)
		{
			work(ss1, ss2, n, pre1, pre2, l1, l2);
			work(ss2, ss1, n, pre2, pre1, l2, l1);
		}
		if (ambi) puts("ambiguous");
		else if (!tans.size()) puts("impossible");
		else
		{
			std::cout << tans << std::endl;
		}
	}
	return 0;
}
/*
4
BANK
MONEY
FTAGUAVMKILCKPRIJCHRJZIYUAXFNBSLNNXMVDVPXLERWDSL
5
SECOND
PARSEC
SUKCTZHYYES
3
ACM
IBM
JDNCOFBEN
4
ABCD
EFGH
OPQRHKLMN
0
*/
