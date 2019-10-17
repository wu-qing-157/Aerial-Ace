#include <cstdio>
#include <iostream>
#include <set>

using namespace std;
string ranklist[10][30], ec[30];
set<string> s;
int main()
{
	int T; cin >> T;
	for (int Cas = 1; Cas <= T; ++Cas)
	{
		int n; cin >> n;
		string name; cin >> name;
		for (int i = 0; i < 5; ++i)
			for (int j = 1; j <= 20; ++j)
				cin >> ranklist[i][j];
		for (int i = 1; i <= 20; ++i) cin >> ec[i];
		int rk = 1, site = 0;
		s.clear();
		bool find = 0;
		printf("Case #%d: ", Cas);
		int ans = -1;
		for (int ii = 0; ii <= n; ++ii)
		{
			int num = 0;
			find = s.count(name);
			for (int j = 1; j <= 20 && num < n - ii; ++j)
				if (!s.count(ec[j]))
				{
					++num;
					if (ec[j] == name) find = 1;
				}
			while (rk <= 20 && s.count(ranklist[site][rk]))
			{
				rk += (site + 1) / 5;
				site = (site + 1) % 5;
			}
			if (rk <= 20)
			{
				s.insert(ranklist[site][rk]);
				rk += (site + 1) / 5;
				site = (site + 1) % 5;
			}
			if (!find) {ans = n - ii;}
		}
		if (ans < 0) puts("ADVANCED!");
		else printf("%d\n", ans);
	}
	return 0;
}
/*
1
10 IJU
UIV GEV LJTV UKV QLV TZTV AKOV TKUV
GAV DVIL TDBV ILVTU AKV VTUD IJU IEV
HVDBT YKUV ATUV TDOV
TKUV UIV GEV AKV AKOV GAV DOV TZTV
AVDD IEV LJTV CVQU HVDBT AKVU XIV TDVU
OVEU OVBB KMV OFV
QLV OCV TDVU COV EMVU TEV XIV
VFTUD OVBB OFV DVHC ISCTU VTUD OVEU DTV
HEVU TEOV TDV TDBV CKVU
CVBB IJU QLV LDDLQ TZTV GEV GAV KMV
OFV AVGF TXVTU VFTUD IEV OVEU OKV DVIL
TEV XIV TDVU TKUV
UIV DVIL VFTUD GEV ATUV AKV TZTV QLV
TIV OVEU TKUV UKV IEV OKV CVQU COV
OFOV CVBB TDVU IOV
UIV TKUV CVBB AKV TZTV VFTUD UKV GEV
QLV OVEU OVQU AKOV TDBV ATUV LDDLQ AKVU
GAV SVD TDVU UPOHK
*/
