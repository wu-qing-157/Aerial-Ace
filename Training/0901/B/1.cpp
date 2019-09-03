#include <cstdio>
#include <cstdint>

const int N = 2e6 + 10;
bool np[N];
int phi[N], pri[N];

void init() {
    phi[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!np[i]) {
            pri[++*pri] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= *pri && 1ll * pri[j] * i < N; j++) {
            np[i * pri[j]] = true;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * (pri[j] - 1);
            }
        }
    }
}

int pow(int a, int exp, int m) {
    int ret = 1 % m;
    a %= m;
    while (exp) {
        if (exp & 1) ret = int(int64_t(ret) * a % m);
        a = int(int64_t(a) * a % m);
        exp >>= 1;
    }
    return ret;
}

int calc(int a, int b, int m) {
    if (m == 1) return 0;
    if (b == 0) return 1 % m;
    if (b == 1) return a % m;
    int c = 0;
    if (a == 2) {
        if (b == 2) c = 2;
        else if (b == 3) c = 4;
        else if (b == 4) c = 16;
        else if (b == 5) c = 256;
    } else if (a <= 7) {
        if (b == 2) c = a;
        else if (b == 3) c = pow(a, a, 2000000);
    }
    if (c == 0 || c >= phi[m])
        return pow(a, calc(a, b - 1, phi[m]) + phi[m], m);
    else
        return pow(a, c, m);
}

int a, b, m;

int main() {
    init();
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &a, &b, &m);
        printf("%d\n", calc(a, b, m));
    }
    return 0;
}
