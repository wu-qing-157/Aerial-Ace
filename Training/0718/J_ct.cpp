#include <cstdio>
#include <vector>

typedef double db;
struct Poi
{
	db x, y;
	Poi() = default;
	Poi(const db &_x, const db &_y) : x(_x), y(_y) {}
};
std::vector<Poi> f, g, ans;
int main()
{
	int n, m; scanf("%d", &n); --n;
	if (n == 0)
	{
		n = 1; db y;
		scanf("%lf", &y);
		f.push_back(Poi(-oo, y));
		f.push_back(Poi(oo, y));
	}
	else
	{
		for (int i = 1; i <= n; ++i)
	}
	scanf("%d", &m); --m;
	if (m == 0)
	{
		m = 1; db y; scanf("%lf", &y);
		g.push_back();
	}
	return 0;
}