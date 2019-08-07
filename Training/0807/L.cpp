#include <bits/stdc++.h>
using namespace std;

int dx[maxn], px[maxn];
int dy[maxn], py[maxn];
int prex[maxn], nxtx[maxn];
int prey[maxn], nxty[maxn];

int calc2(int Ax, int Ay, int Bx, int By) {
	return abs(px[Ax] - px[Bx]) + abs(py[Ay] - py[By]);	
}

int workx(int Ax, int Ay, int Bx, int By, int x) {
	int x1 = abs(Ax - x), x2 = abs(Bx - x);
	if (Ay > By) swap(Ax, Bx), swap(Ay, By);
	int y1 = Ay + x1 - 1;
	int y2 = Ay + x1;
	int y3 = By - x2 + 1;
	int y4 = By - x2;
	if (y2 < y3 && (y3 - y2) & 1) 
		return calc2(Ax, Ay, x, y2) + calc2(Bx, By, x, y3) + (py[y3] - py[y2]) + (y3 - y2 - 1) * dx[x];
	if (y1 < y3 && (y3 - y1) & 1) 
		return calc2(Ax, Ay, x, y1) + calc2(Bx, By, x, y3) + (py[y3] - py[y1]) + (y3 - y1 - 1) * dx[x];
	
}

int calc(int Ax, int Ay, int Bx, int By) {
	int Dx = abs(Ax - Bx);
	int Dy = abs(Ay - By);
	if (abs(Dx - Dy) <= 1) 
		return abs(px[Ax] - px[Bx]) + abs(py[Ay] - py[By]);
	int ans = 1e9;
	if (Dx < Dy) {
		if (nxtx[Ax] != -1) {
			ans = min(ans, 
			workx(Ax, Ay, Bx, By, nxtx[Ax]));
		}
		if (nxtx[Bx] != -1) {
			ans = min(ans, 
			workx(Ax, Ay, Bx, By, nxtx[Bx]));
		}
		if (prex[Ax] != -1) {
			ans = min(ans, 
			workx(Ax, Ay, Bx, By, prex[Ax]));			
		}
		if (prex[Bx] != -1)	{
			ans = min(ans, 
			workx(Ax, Ay, Bx, By, prex[Bx]));			
		}
	} else {
		if (nxty[Ay] != -1) {
			ans = min(ans, 
			worky(Ax, Ay, Bx, By, nxty[Ay]));
		}
		if (nxty[By] != -1) {
			ans = min(ans, 
			worky(Ax, Ay, Bx, By, nxty[By]));
		}
		if (prey[Ay] != -1) {
			ans = min(ans, 
			worky(Ax, Ay, Bx, By, prey[Ay]));			
		}
		if (prey[By] != -1)	{
			ans = min(ans, 
			worky(Ax, Ay, Bx, By, prey[By]));			
		}
	}
}

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i < n; i++) scanf("%d", &dx[i]);
	for (int i = 1; i < n; i++) scanf("%d", &dy[i]);
	
	px[1] = 0;
	for (int i = 2; i <= n; i++) px[i] = px[i - 1] + dx[i - 1];
	
	py[1] = 0;
	for (int i = 2; i <= n; i++) py[i] = py[i - 1] + dy[i - 1];
	
	prex[0] = -1;
	prey[0] = -1;
	
	for (int i = 1; i <= n; i++) {
		if (dx[i - 1] == 1) prex[i] = i - 1;
		else prex[i] = prex[i - 1];
		if (dy[i - 1] == 1) prey[i] = i - 1;
		else prey[i] = prey[i - 1];
	}
	
	nxtx[n + 1] = -1;
	nxty[n + 1] = -1;
	for (int i = n; i >= 1; i--) {
		if (dx[i] == 1) nxtx[i] = i;
		else nxtx[i] = nxtx[i + 1];
		if (dy[i] == 1) nxty[i] = i;
		else nxty[i] = nxty[i + 1];
	}
	
	int q; scanf("%d", &q);
	while (q--) {
		int Ax, Ay, Bx, By;
		scanf("%d%d%d%d", &Ax, &Ay, &Bx, &By);
		printf("%d\n", calc(Ax, Ay, Bx, By));
	}
	
	return 0;
}
