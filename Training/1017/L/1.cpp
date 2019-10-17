#include <cstdio>

int day_in_week(int year, int month, int day) {
    if (month == 1 || month == 2) month += 12, year--;
    int c = year / 100, y = year % 100, m = month, d = day;
    int ret = (y + y / 4 + c / 4 + 5 * c + 13 * (m + 1) / 5 + d + 6) % 7;
    return ret >= 0 ? ret : ret + 7;
}

int Y, M, D, h, m, s;

int main() {
    static int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        printf("Case #%d: ", cas);
        scanf("%d-%d-%d %d:%d:%d", &Y, &M, &D, &h, &m, &s);
        if (M < 3 || M > 11) {
            puts("PST");
        } else if (M > 3 && M < 11) {
            puts("PDT");
        } else if (M == 3) {
            int day = day_in_week(Y, 3, 8), cur = 8;
            while (day) {
                day = (day + 1) % 7;
                cur++;
            }
            if (D < cur) {
                puts("PST");
            } else if (D > cur) {
                puts("PDT");
            } else {
                if (h < 2)
                    puts("PST");
                else if (h > 2)
                    puts("PDT");
                else
                    puts("Neither");
            }
        } else if (M == 11) {
            int day = day_in_week(Y, 11, 1), cur = 1;
            while (day) {
                day = (day + 1) % 7;
                cur++;
            }
            if (D < cur) {
                puts("PDT");
            } else if (D > cur) {
                puts("PST");
            } else {
                if (h < 1)
                    puts("PDT");
                else if (h > 1)
                    puts("PST");
                else
                    puts("Both");
            }
        }
    }
    return 0;
}
