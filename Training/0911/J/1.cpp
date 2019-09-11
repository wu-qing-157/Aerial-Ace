#include <cstdio>
#include <algorithm>

struct data {
    int id, p, t;
    friend bool operator<(const data &a, const data &b) {
        if (a.p == b.p) return a.t < b.t;
        return a.p > b.p;
    }
};

const int N = 1e5 + 10;
int n, d;
data a[N];
char s[N][20];

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &d);
        for (int i = 0; i < n; i++)
            scanf("%s%d%d", s[i], &a[i].p, &a[i].t), a[i].id = i;
        int tar = n * d * 10;
        if (tar % 100 != 50)
            puts("Quailty is very great");
        else
            std::sort(a, a + n), printf("%s\n", s[a[tar / 100].id]);
    }
    return 0;
}
