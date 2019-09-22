#include <bits/stdc++.h>
using namespace std;

#define maxn 100010
const int moha1 = 19260817;
const int moha2 = 998244353;
struct Query {
	int len, id;
	string name;
	inline bool operator < (const Query &that) const {return len < that.len;}
} qs[maxn];
string s;
int ls[maxn], ans[maxn];
std::vector<std::pair<int, int>> v[26][26];
std::pair<int, int> val[26];
int main()
{
	srand(19260817);
	int T; scanf("%d", &T);
	for (int i = 0; i < 26; ++i) val[i] = std::make_pair(rand() % moha1, rand() % moha2);
	for (; T; --T)
	{
		cin >> s;
		int q, n = s.size(); cin >> q;
		for (int i = 1; i <= q; ++i)
			cin >> qs[i].name, ls[i] = qs[i].len = qs[i].name.size(), qs[i].id = i;
		sort(qs + 1, qs + q + 1);
		sort(ls + 1, ls + q + 1);
		int nq = unique(ls + 1, ls + q + 1) - ls - 1;
		for (int i = 1, ii = 1; i <= nq; ++i)
		{
			std::pair<int, int> ha = std::make_pair(0, 0);
			for (int j = 1; j < ls[i] - 1; ++j)
				(ha.first += val[s[j] - 'a'].first) %= moha1,
				(ha.second += val[s[j] - 'a'].second) %= moha2;
			for (int l = 0, r = ls[i] - 1; r < n; ++l, ++r)
			{
				v[s[l] - 'a'][s[r] - 'a'].push_back(ha);
				(ha.first += moha1 - val[s[l + 1] - 'a'].first) %= moha1;
				(ha.first += val[s[r] - 'a'].first) %= moha1;
				
				(ha.second += moha2 - val[s[l + 1] - 'a'].second) %= moha2;
				(ha.second += val[s[r] - 'a'].second) %= moha2;
			}
			for (int _ = 0; _ < 26; ++_)
				for (int __ = 0; __ < 26; ++__)
					sort(v[_][__].begin(), v[_][__].end());
			while (ii <= q && qs[ii].len == ls[i])
			{
				int hd = qs[ii].name[0] - 'a', tl = qs[ii].name[qs[ii].len - 1] - 'a';
				ha = std::make_pair(0, 0);
				for (auto it : qs[ii].name)
					(ha.first += val[it - 'a'].first) %= moha1,
					(ha.second += val[it - 'a'].second) %= moha2;
				(ha.first += moha1 - val[hd].first) %= moha1;
				(ha.first += moha1 - val[tl].first) %= moha1;
				
				(ha.second += moha2 - val[hd].second) %= moha2;
				(ha.second += moha2 - val[tl].second) %= moha2;
				
				ans[qs[ii].id] = upper_bound(v[hd][tl].begin(), v[hd][tl].end(), ha) - lower_bound(v[hd][tl].begin(), v[hd][tl].end(), ha);
				++ii;
			}
			for (int i = 0; i < 26; ++i)
				for (int j = 0; j < 26; ++j)
					v[i][j].clear();
		}
		for (int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
