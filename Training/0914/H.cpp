#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

#define maxn 100010
struct Item {
	int pk[5], type; std::string name;
	std::vector<std::pair<int, int>> v;
	inline bool operator < (const Item &that) const
	{
		if (type != that.type) return type > that.type;
		if (type == 1)
		{
			int sum1 = 0, sum2 = 0;
			for (auto it : v) sum1 -= it.second;
			for (auto it : that.v) sum2 -= it.second;
			if (sum1 != sum2) return sum1 > sum2;
		}
		if (type == 2 || type == 4)
		{
			if (v[0].second != that.v[0].second) return v[0].second < that.v[0].second;
			int sum1 = 0, sum2 = 0;
			for (auto it : v) sum1 -= it.second;
			for (auto it : that.v) sum2 -= it.second;
			if (sum1 != sum2) return sum1 > sum2;
		}
		if (type == 3 || type == 5 || type == 6 || type == 7)
		{
			if (v != that.v) return v < that.v;
		}
		
		return name < that.name;
	}
} a[maxn];
char str[maxn];
int main()
{
	int n; std::cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		std::cin >> a[i].name >> str;
		int n = strlen(str), num = 0;
		for (int j = 0; j < n; ++j)
			if (str[j] == 'A')
				a[i].pk[num++] = 1;
			else if (str[j] == 'J')
				a[i].pk[num++] = 11;
			else if (str[j] == 'Q')
				a[i].pk[num++] = 12;
			else if (str[j] == 'K')
				a[i].pk[num++] = 13;
			else if (str[j] == '1')
				a[i].pk[num++] = 10, ++j;
			else a[i].pk[num++] = str[j] - '0';
		std::sort(a[i].pk, a[i].pk + 5);
		
		num = 1; int ccc = 0;
		for (int j = 1; j < 5; ++j)
			if (a[i].pk[j] != a[i].pk[j - 1])
				a[i].v.emplace_back(-num, -a[i].pk[j - 1]), num = 1;
			else ++num;
		a[i].v.emplace_back(-num, -a[i].pk[4]);
		std::sort(a[i].v.begin(), a[i].v.end());
		
		if (a[i].pk[1] == 10 && a[i].pk[2] == 11 && a[i].pk[3] == 12 && a[i].pk[4] == 13 && a[i].pk[0] == 1)
			a[i].type = 8;
		// Royal s
		else
		{
			bool flag = 1;
			for (int j = 0; j < 4; ++j) if (a[i].pk[j] != a[i].pk[j + 1] - 1) flag = 0;
			if (flag) a[i].type = 7;
			else
			{
				if (a[i].v.size() == 2)
				{
					if (a[i].v[0].first == -4) a[i].type = 6;
					else a[i].type = 5;
				}
				else if (a[i].v.size() == 3)
				{
					if (a[i].v[0].first == -3) a[i].type = 4;
					else a[i].type = 3;
				}
				else if (a[i].v.size() == 4) a[i].type = 2;
				else a[i].type = 1;
			}
		}
	}
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
		std::cout << a[i].name << '\n';
	return 0;
}
