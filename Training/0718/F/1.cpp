#include <cstdint>
#include <cstdio>
#include <initializer_list>

const int N = 64;
uint64_t a;
int b[N];
bool v[N];

void output(int i) {
    for (int j : { 8 * i + 4, 8 * i }) {
        int out = 0;
        for (int k : { j + 3, j + 2, j + 1, j })
            (out <<= 1) += b[k];
        printf("%c", out < 10 ? out + '0' : out - 10 + 'a');
    }
}

int main() {
    freopen("packing.in", "r", stdin);
    freopen("packing.out", "w", stdout);
    static int T;
    static int64_t ta;
    scanf("%d", &T);
    while (T--) {
        scanf("%lld", &ta);
        a = ta;
        for (int i = 0; i < 64; i++) {
            b[i] = a & 1;
            a >>= 1;
        }
        v[63] = true;
        for (int i = 62; i >= 0; i--)
            v[i] = v[i + 1] && b[i] == b[i + 1];
        bool flag = true;
        for (int k = 0; k < 8; k++)
            if (v[7 * k + 6]) {
                b[7 * k + 7] = 0;
                for (int i = 7 * k + 8; i < 8 * k + 8; i++) b[i] = 1;
                for (int i = k; i >= 0; i--) output(i);
                puts("");
                flag = false;
                break;
            }
        if (flag) {
            printf("ff");
            for (int i = 7; i >= 0; i--) output(i);
            puts("");
        }
    }
    return 0;
}
