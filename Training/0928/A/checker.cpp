#include <cstdio>
#include <cstdlib>

FILE *in, *out;
int n, k, a[1100], v[1100][1100];

int main() {
    for (int n = 3; n <= 1000; n++) {
        bool flag = true;
        printf("check %d: ", n);
        in = fopen("in", "w");
        fprintf(in, "%d\n", n);
        fclose(in);
        system("./1 < in > out");
        out = fopen("out", "r");
        fscanf(out, "%d", &k);
        for (int i = 1; i <= n; i++)
            fscanf(out, "%d", a + i);
        fclose(out);
        a[n + 1] = a[1];
        for (int i = 1; i <= n; i++)
            if (a[i] == a[i + 1]) {
                puts("WA 1");
                flag = false;
            }
        for (int i = 1; i <= k; i++)
            for (int j = 1; j <= k; j++)
                v[i][j] = false;
        for (int i = 1; i <= n; i++)
            v[a[i]][a[i + 1]] = true;
        for (int i = 1; i <= k; i++)
            for (int j = i + 1; j <= k; j++)
                if (!v[i][j] && !v[j][i]) {
                    puts("WA 2");
                    flag = false;
                }
        if (flag)
            puts("AC");
        else
            break;
    }
}
