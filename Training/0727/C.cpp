#include <bits/stdc++.h>
using namespace std;

#define double long double

typedef pair<double, int> pdi;

const int maxn = 100 + 10;

double C[maxn], S[maxn];
bool vis[maxn];

double _sqrt(double x) {
	return std::sqrt(std::max<double>(x, 0));
}

void work() {
	int n; double A, B;
	#undef double
	double ta, tb;
	#define double long double
	scanf("%d%lf%lf", &n, &ta, &tb);
	A = ta, B = tb;
	memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; i++) 
		scanf("%lf", &ta), C[i] = ta * ta; /**/
	for (int i = 0; i < n; i++)
		scanf("%lf", &ta), S[i] = ta;
    C[n] = C[0], C[0] = 0;
    double SS = 0;
    for (int i = 1; i < n; i++) {
        SS += S[i - 1];
        C[n] = std::min(C[n], C[i] + 2 * B * SS);
    }
    for (int i = 0; i <= n; i++) {
        double min = 1e60;
        int mind = -1;
        for (int j = 0; j <= n; j++) if (!vis[j] && C[j] < min) {
            min = C[j];
            mind = j;
        }
            // printf("%d %Lf\n", mind, C[mind]);
        int cur = mind;
        int nxt = cur + 1;
        if (nxt <= n) C[nxt] = std::min(C[nxt], C[cur] + 2 * A * S[cur]);
        nxt = cur - 1;
        if (nxt >= 0) C[nxt] = std::min(C[nxt], C[cur] + 2 * B * S[nxt]);
        vis[mind] = true;
    }
	
	
	
	//cout << A << ' ' << B << endl;
	
	double ans = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1);
		double midc = (2 * A * B * S[i] + A * C[j] + B * C[i]) / (A + B);
		// printf("%lf %lf ", C[i], C[j]);
		// printf("%lf\n", midc);
		ans += (_sqrt(midc) - _sqrt(C[i])) / A + (_sqrt(midc) - _sqrt(C[j])) / B;
	}
	
	//for (int i = 0; i < n; i++) cout << "C[" << i << "] = " << sqrt(C[i]) << ' '; cout << endl;
	
	#undef double
	printf("%.10f\n", (double) ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) 
		work();
	return 0;
}

/*
1
3 10 10
0 0 0
10 10 10

1
5 2 3
1 3 2 4 5
2 1 2 5 4


*/
