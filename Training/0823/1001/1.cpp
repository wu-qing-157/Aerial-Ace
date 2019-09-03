#include <cstdio>
#include <cstdint>

uint32_t a, b, c;

int main() {
    static int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%u%u", &a, &b);
        for (int i = 0; i < 32; i++) {
            bool ta = a & (1u << i);
            bool tb = b & (1u << i);
            if (ta && tb)
                c |= 1u << i;
        }
        printf("%u\n", c);
    }
}
