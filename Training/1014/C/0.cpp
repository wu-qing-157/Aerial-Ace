#include <cstdio>
#include <vector>
#include <initializer_list>

const std::initializer_list<int> list = {0, 1, 2, 3};
int a[6][6][6][6][6], b[6][6][6][6][6];

#define i [i1][i2][i3][i4][i5]

int main() {
    for (int i1 : list) for (int i2 : list) for (int i3 : list) for (int i4 : list) for (int i5 : {0}) {
        switch ((i1 > 0) + (i2 > 0) + (i3 > 0) + (i4 > 0) + (i5 > 0)) {
            case 0:
                a i = b i = false;
                break;
            case 1:
                a i = b i = true;
                break;
            case 2:
                a i = true, b i = false;
                break;
            default:
                {
                    bool ret = false;
                    for (int *op : {&i1, &i2, &i3, &i4, &i5})
                        for (int delta = 2; delta <= *op; delta++) {
                            *op -= delta;
                            ret |= !b i;
                            *op += delta;
                        }
                    for (int *op1 : {&i1, &i2, &i3, &i4, &i5})
                        for (int *op2 : {&i1, &i2, &i3, &i4, &i5})
                            if (op1 != op2)
                                for (int d1 = 1; d1 <= *op1; d1++)
                                    for (int d2 = 1; d2 <= *op2; d2++) {
                                        *op1 -= d1, *op2 -= d2;
                                        ret |= !b i;
                                        *op1 += d1, *op2 += d2;
                                    }
                    a i = ret;
                }
                {
                    bool ret = false;
                    for (int *op : {&i1, &i2, &i3, &i4, &i5})
                        for (int delta = 1; delta <= *op; delta++) {
                            *op -= delta;
                            ret |= !a i;
                            *op += delta;
                        }
                    b i = ret;
                }
        }
        printf("%d%d%d%d%d    %s  %s\n", i1, i2, i3, i4, i5, a i ? "win " : "lose", b i ? "win " : "lose");
    }
    return 0;
}
