#include <cstdio>
#include <algorithm>

const int N = 1e6 + 10;
int n, k;
char s[N], t[N];
bool a[N], b[N];

void flip(int l, int r) {
    printf("%d %d\n", l, r);
    b[l] ^= 1;
    b[r] ^= 1;
    if (l == 0 || (l > r && r > 0)) a[0] ^= 1;
}

int main() {
    scanf("%d%d%s%s", &n, &k, s, t);
    for (int i = 0; i < n; i++) a[i] = s[i] != t[i];
    b[0] = a[n - 1] ^ a[0];
    for (int i = 1; i < n; i++) b[i] = a[i - 1] ^ a[i];
    int gcd = std::__gcd(n, k);
    for (int i = 0; i < gcd; i++) {
        if (b[i]) flip(i, (i + k) % n);
        for (int j = (i + k) % n; j != i; (j += k) %= n)
            if (b[j]) flip(j, (j + k) % n);
    }
    if (a[0]) {
        flip(0, k % n);
        for (int j = k % n; j; (j += k) %= n)
            flip(j, (j + k) % n);
    }
    puts(std::all_of(b, b + n, [](int x) { return x == 0; }) && !a[0] ? "Yes" : "No");
    return 0;
}
