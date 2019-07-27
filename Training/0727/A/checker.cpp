#include <cstdio>
#include <cstdlib>

int main() {
    while (true) {
        FILE *f = fopen("in", "w");
        for (int i = 1; i <= 8; i++) {
            int x = rand() % 10 - 20;
            fprintf(f, "%d ", x);
            printf("%d ", x);
        }
        puts("");
        fclose(f);
        if (system("./1 < in") != 0) break;
    }
    return 0;
}
