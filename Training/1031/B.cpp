#include <bits/stdc++.h>
using namespace std;

int a[6][2][2], b[2][8];
bool s[6];

void reverse(int x) {
	for (int i = 0; i < 2; i++)
		swap(a[x][0][i], a[x][1][i]);
}

void rotate(int x) {
	swap(a[x][0][0], a[x][0][1]);
	swap(a[x][1][0], a[x][0][0]);
	swap(a[x][1][1], a[x][1][0]);
}

void work() {
	int cnt = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				scanf("%d", &a[i][j][k]);
		int c = a[i][0][0]; s[i] = true;
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
				s[i] &= (c == a[i][j][k]);
		if (s[i]) cnt++;
	}
	
	if (cnt == 6) return void(puts("YES"));
	else if (cnt == 2) {
		int x = -1, y = -1;
		for (int i = 0; i < 6; i++) {
			if (s[i] && x == -1) x = i;
			else if (s[i] && x != -1) y = i;	
		}
		//cout << x << ' ' << y << endl;	
		if (x > y) swap(x, y);
		if (x == 0 && y == 2) {
			reverse(3); 
			rotate(4);
			rotate(4);
			rotate(4);			
			rotate(5);
			
			for (int i = 0; i < 6; i++) if (i != x && i != y) 
				for (int j = 0; j < 2; j++)
					if (a[i][j][0] != a[i][j][1])
						return void(puts("NO"));
			
			for (int i = 0; i < 2; i++) {
				b[i][0] = a[1][i][0];
				b[i][1] = a[1][i][1];
				b[i][2] = a[5][i][0];
				b[i][3] = a[5][i][1];
				b[i][4] = a[3][i][0];
				b[i][5] = a[3][i][1];
				b[i][6] = a[4][i][0];
				b[i][7] = a[4][i][1];
			}
			
			bool ok1 = true, ok2 = true;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 2) % 8]) ok1 = false;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 6) % 8]) ok2 = false;
			
			if (ok1 || ok2) return void(puts("YES"));
			else return void(puts("NO"));
		} 
		if (x == 1 && y == 3) {
			reverse(2); 
			
			for (int i = 0; i < 6; i++) if (i != x && i != y) 
				for (int j = 0; j < 2; j++)
					if (a[i][j][0] != a[i][j][1])
						return void(puts("NO"));
			
			for (int i = 0; i < 2; i++) {
				b[i][0] = a[0][i][0];
				b[i][1] = a[0][i][1];
				b[i][2] = a[5][i][0];
				b[i][3] = a[5][i][1];
				b[i][4] = a[2][i][0];
				b[i][5] = a[2][i][1];
				b[i][6] = a[4][i][0];
				b[i][7] = a[4][i][1];
			}
			
			bool ok1 = true, ok2 = true;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 2) % 8]) ok1 = false;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 6) % 8]) ok2 = false;
			
			if (ok1 || ok2) return void(puts("YES"));
			else return void(puts("NO"));
		}
		if (x == 4 && y == 5) {
		
			//cout << "ok" << endl;
		
			rotate(0);
			rotate(1);
			rotate(2);
			rotate(3);
			
			for (int i = 0; i < 6; i++) if (i != x && i != y) {
				for (int j = 0; j < 2; j++)
					if (a[i][j][0] != a[i][j][1])
						return void(puts("NO"));
				/*
				for (int j = 0; j < 2; j++, puts(""))		
					for (int k = 0; k < 2; k++)
						printf("%d ", a[i][j][k]);
				*/
			}
			
			for (int i = 0; i < 2; i++) {
				b[i][0] = a[0][i][0];
				b[i][1] = a[0][i][1];
				b[i][2] = a[1][i][0];
				b[i][3] = a[1][i][1];
				b[i][4] = a[2][i][0];
				b[i][5] = a[2][i][1];
				b[i][6] = a[3][i][0];
				b[i][7] = a[3][i][1];
			}
			
			bool ok1 = true, ok2 = true;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 2) % 8]) ok1 = false;
			for (int i = 0; i < 8; i++)
				if (b[0][i] != b[1][(i + 6) % 8]) ok2 = false;
			
			if (ok1 || ok2) return void(puts("YES"));
			else return void(puts("NO"));
		}
		return void(puts("NO"));
	} else return void(puts("NO"));
}


int main() {
	int T; scanf("%d", &T);
	while (T--)
		work();
	return 0;
}
