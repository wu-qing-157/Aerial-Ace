#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;

char W1[maxn], W2[maxn], C[maxn], D[maxn];

const int inf = 1e9;
map<string, pair<int, int> >mp;

string ans1, ans2;

void work(int K) {
    scanf("%s%s%s", W1, W2, C);
    int n1 = strlen(W1), n2 = strlen(W2);
    int n = strlen(C);
    ans1.clear();
    int cnt = 0;
    for (int i = 1; i <= K; i++) {
        mp.clear();
        string tmp;
        for (int j = 0; j < n - n1 + 1; j++) {
            for (int k = 0; k < i; k++)
                D[(j + k) % i] = (C[j + k] - W1[k] + 26) % 26 + 'A';
            bool flag = true;
            for (int k = i; k < n1; k++) 
                if (D[(j + k) % i] != (C[j + k] - W1[k] + 26) % 26 + 'A') {
                    flag = false; break;
                }
            if (flag) {
                tmp.clear();
                for (int k = 0; k < i; k++) tmp += D[k];
                if (mp.find(tmp) == mp.end())
                    mp[tmp] = make_pair(inf, -inf);
                mp[tmp].first = min(mp[tmp].first, j);
                mp[tmp].second = max(mp[tmp].second, j);
            }
        }
        for (int j = 0; j < n - n2 + 1; j++) {
            for (int k = 0; k < i; k++) 
                D[(j + k) % i] = (C[j + k] - W2[k] + 26) % 26 + 'A';
            bool flag = true;
            for (int k = i; k < n2; k++)
                if (D[(j + k) % i] != (C[j + k] - W2[k] + 26) % 26 + 'A') {
                    flag = false; break;
                }
            if (flag) {
                tmp.clear();
                for (int k = 0; k < i; k++) tmp += D[k];
                if (mp.find(tmp) != mp.end()) {
                    pair<int, int>now(mp[tmp]);
                    if (!(j + n2 <= now.first || j - n1 >= now.first) && !(j + n2 <= now.second || j - n1 >= now.second)) continue;
                    ans2.clear();
                    for (int k = 0; k < n; k++) 
                        ans2 += ('A' + (C[k] - D[k % i] + 26) % 26);
                    if (ans1 != ans2) {
                        cnt++;
                        if (cnt == 2) 
                            break;
                        ans1 = ans2;
                    }
                }
            }
        }
        if (cnt == 2) break;
    }
    if (cnt == 2) cout << "ambiguous" << endl;
    if (cnt == 1) cout << ans1 << endl;
    if (cnt == 0) cout << "impossible" << endl;
    
}

int main() {
    int n; 
    while (true) {
        scanf("%d", &n); 
        if (n == 0)
            break;
        else 
            work(n);
        putchar('\n');
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