#include <cstdio>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cstring>
#include <iostream>

#define maxn 100010
std::unordered_set<std::string> tans;
std::unordered_map<std::string, int> mp;
char ss1[110], ss2[110];
char t[maxn], as[110], ans[110];
bool ambi;
void work(char s1[], char s2[], int n)
{
	mp.clear();
	int lt = strlen(t), l1 = strlen(s1), l2 = strlen(s2), num = 0;
	for (int i = 0; i + l1 - 1 < lt; ++i)
	{
		bool flag = 0;
		memset(as, 0, n);
		for (int j = 0; j < l1 && !flag; ++j)
		{
			char ch = (t[i + j] - s1[j] + 25) % 26 + 'A';
			if (as[(i + j) % n] && as[(i + j) % n] != ch) flag = 1;
			as[(i + j) % n] = ch;
		}
		if (!flag)
		{
			std::string str; str = "";
			for (int j = 0; j < n; ++j) str.push_back(as[j]);
			if (!mp.count(str)) mp[str] = i;
		}
	}
	for (int i = 0; i + l2 - 1 < lt; ++i)
	{
		bool flag = 0;
		memset(as, 0, n);
		for (int j = 0; j < l2 && !flag; ++j)
		{
			char ch = (t[i + j] - s2[j] + 25) % 26 + 'A';
			if (as[(i + j) % n] && as[(i + j) % n] != ch) flag = 1;
			as[(i + j) % n] = ch;
		}
		if (!flag)
		{
			std::string str; str = "";
			for (int j = 0; j < n; ++j) str.push_back(as[j]);
			if (mp.count(str) && mp[str] + l1 <= i)
			{
				++num;
				memcpy(ans, as, n);
				mp.erase(str);
			}
		}
	}
	if (num >= 2) ambi = 1;
	else if (num)
	{
		std::string ta = "";
		for (int i = 0; i < lt; ++i) ta.push_back((t[i] - ans[i % n] + 25) % 26 + 'A');
		tans.insert(ta);
	}
}
int main()
{
	int nn;
	while (scanf("%d", &nn) != EOF)
	{
		if (!nn) return 0;
		scanf("%s", ss1); scanf("%s", ss2);
		scanf("%s", t);
		int num = 0; tans.clear();
		ambi = 0;
		for (int n = 1; n <= nn && !ambi && tans.size() <= 1; ++n)
		{
			work(ss1, ss2, n);
			work(ss2, ss1, n);
		}
		if (ambi || tans.size() > 1) puts("ambiguous");
		else if (!tans.size()) puts("impossible");
		else
		{
			std::cout << *tans.begin() << std::endl;
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
