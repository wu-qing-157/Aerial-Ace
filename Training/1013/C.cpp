#include <bits/stdc++.h>

const int maxn = 2e6 + 10;
int a[maxn], b[maxn];
int A[maxn], B[maxn];
std::map<int, int>lg;

int w[50];

long long calc(int n, int m, int min, int max, int val) {
/*
	puts("");
	for (int i = 0; i < n; i++) printf("%d ", A[i]);
	puts("");
	for (int i = 0; i < m; i++) printf("%d ", B[i]);
	puts("");
*/
	long long ans = 0;
	int p1 = 0, p2 = 0;
	
	p1 = int(std::upper_bound(B, B + m, max - A[0]) - B);
	p2 = int(std::upper_bound(B, B + m, min - A[0]) - B);
	
	for (int i = 0; i < n; i++) {
		int mx = max - A[i];
		int mi = min - A[i];
		while (p1 < m && B[p1] <= mx) p1++;
		while (p1 > 0 && B[p1 - 1] > mx) p1--;
		while (p2 < m && B[p2] < mi) p2++;
		while (p2 > 0 && B[p2 - 1] >= mi) p2--;
		ans += p1 - p2; 
		//std::upper_bound(B, B + m, mx) - std::lower_bound(B, B + m, mi);
		//std::cout << "ans = " << ans << ' ' << mx << ' ' << mi << std::endl;
	}
	
	min += val;
	max += val;
	
	p1 = int(std::upper_bound(B, B + m, max - A[0]) - B);
	p2 = int(std::upper_bound(B, B + m, min - A[0]) - B);
	
	for (int i = 0; i < n; i++) {
		int mx = max - A[i];
		int mi = min - A[i];
		while (p1 < m && B[p1] <= mx) p1++;
		while (p1 > 0 && B[p1 - 1] > mx) p1--;
		while (p2 < m && B[p2] < mi) p2++;
		while (p2 > 0 && B[p2 - 1] >= mi) p2--;
		ans += p1 - p2; 
		//std::upper_bound(B, B + m, mx) - std::lower_bound(B, B + m, mi);
		//std::cout << "ans = " << ans << ' ' << mx << ' ' << mi << std::endl;
	}
	return ans;
}
int cnt[2098];
namespace Sorting {
	int cnt1[256], cnt2[256], cnt3[256], cnt4[256];
	int b[maxn];
	void sort(int *a, int n)
	{
		memset(cnt1, 0, sizeof (cnt1));
		memset(cnt2, 0, sizeof (cnt1));
		memset(cnt3, 0, sizeof (cnt1));
		memset(cnt4, 0, sizeof (cnt1));
		for (int i = 0; i < n; ++i)
		{
			++cnt1[a[i] & 255];
			++cnt2[a[i] >> 8 & 255];
			++cnt3[a[i] >> 16 & 255];
			++cnt4[a[i] >> 24 & 255];
		}
		for (int i = 1; i < 256; ++i)
		{
			cnt1[i] += cnt1[i - 1];
			cnt2[i] += cnt2[i - 1];
			cnt3[i] += cnt3[i - 1];
			cnt4[i] += cnt4[i - 1];
		}
		for (int i = n; i--; ) b[--cnt1[a[i] & 255]] = a[i];
		for (int i = n; i--; ) a[--cnt2[b[i] >> 8 & 255]] = b[i];
		for (int i = n; i--; ) b[--cnt3[a[i] >> 16 & 255]] = a[i];
		for (int i = n; i--; ) a[--cnt4[b[i] >> 24 & 255]] = b[i];
		
	}
}
void work() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &w[i]);
	int s1 = n / 2;
	int s2 = n - n / 2;
	for (int s = 1; s < 1 << s1; s++) {
		int t = s - (s & -s);
		a[s] = a[t] + w[lg[s & -s]];
	}
	for (int s = 1; s < 1 << s2; s++) {
		int t = s - (s & -s);
		b[s] = b[t] + w[lg[s & -s] + s1];
	}
	
	n = 1 << s1;
	int m = 1 << s2;
	
	long long ans = 0;
		
	for (int j = 1, v = 10; j <= 9; j++) {
		for (int i = 0; i < n; i++) A[i] = a[i] % v;
		for (int i = 0; i < m; i++) B[i] = b[i] % v;
		Sorting::sort(A, n);
		Sorting::sort(B, m);
		ans += calc(n, m, v / 10 * 4, v / 10 * 5 - 1, v);
		if (v < int(1e9)) v = v * 10;
	}
	printf("%lld\n", ans);
}

int main() {
	for (int i = 0; i < 30; i++) lg[1 << i] = i;
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
