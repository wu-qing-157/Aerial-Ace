#include <iostream>

double getNum(int s, int D) {
	double v = D; 
	for (int i = 1; i < s; i++)
		v = v * 10 + D;
	return v;
}

bool check(int s, int D, double N) {
	
}

int work(int D, int N) {
	int ans = 1;
	while (!check(ans, D, N))
		ans++;
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int D, N; scanf("%d%d", &D, &N);
		work(D, N);
	}
	return 0;
}

