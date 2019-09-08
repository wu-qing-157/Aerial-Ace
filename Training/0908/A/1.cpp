#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

int rd() {
    return rand();
}

const int t_size = 5, tc[t_size] = {2, 3, 5, 7, 61};

int64_t pow(int64_t x, int64_t exp, int64_t p) {
    int64_t ret = 1;
    while (exp) {
        if (exp & 1) (ret *= x) %= p;
        (x *= x) %= p;
        exp >>= 1;
    }
    return ret;
}

bool mr_check(int64_t prime, int64_t base) {
    int64_t number = prime - 1;
    for (; ~number & 1; number >>= 1) continue;
    int64_t result = pow(base, number, prime);
    for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
        (result *= result) %= prime;
    return result == prime - 1 || (number & 1) == 1;
}

bool mr(int64_t number) {
    if (number < 2)
        return false;
    if (number < 4)
        return true;
    if (~number & 1)
        return false;
    for (int i = 0; i < t_size && tc[i] < number; i++)
        if (!mr_check(number, tc[i]))
            return false;
    return true;
}

int pr_test(int number, int seed) {
    int64_t x = rd() % (number - 1) + 1, y = x;
    int head = 1, tail = 2;
    while (true) {
        ((x *= x) += seed) %= number;
        if (x == y) return number;
        int answer = std::__gcd(abs((int) (x - y)), number);
        if (answer > 1 && answer < number) return answer;
        if (++head == tail) {
            y = x;
            tail <<= 1;
        }
    }
}

void factor(int number, std::vector<int> &divisor) {
    if (number > 1) {
        if (mr(number)) {
            divisor.push_back(number);
        } else {
            int fact = number;
            while (fact >= number)
                fact = pr_test(number, rd() % (number - 1) + 1);
            factor(number / fact, divisor);
            factor(fact, divisor);
        }
    }
}

int T, a[100];

int phi(int x) {
    std::vector<int> a;
    factor(x, a);
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    for (int i : a) (x /= i) *= i - 1;
    return x;
}

bool check(int delta) {
    if (delta <= 0) return false;
    for (int i = 0; i < 100; i++)
        if (phi(i + delta) != a[i])
            return false;
    return true;
}

int main() {
    srand(20001415);
    /*
    while (true) {
        scanf("%d", &n);
        printf("%s\n", mr(n) ? "prime" : "no");
        std::vector<int> a;
        factor(n, a);
        for (auto i : a)
            printf("%d ", i);
        puts("");
    }
    */
    /*
    while (true) {
        scanf("%d", &T);
        printf("%d\n", phi(T));
    }
    */
    scanf("%d", &T);
    while (T--) {
        for (int i = 0; i < 100; i++) scanf("%d", a + i);
        bool flag = true;
        for (int i = 0; i < 100 && flag; i++) {
            if (mr(a[i] + 1) && check(a[i] + 1 - i)) {
                puts("YES");
                printf("%d\n", a[i] + 1 - i);
                flag = false;
                break;
            }
            if (mr(a[i] + 1) && check((a[i] + 1) * 2 - i)) {
                puts("YES");
                printf("%d\n", (a[i] + 1) * 2 - i);
                flag = false;
                break;
            }
            if (mr(a[i] / 2 + 1) && check((a[i] / 2 + 1) * 3 - i)) {
                puts("YES");
                printf("%d\n", (a[i] / 2 + 1) * 3 - i);
                flag = false;
                break;
            }
            if (mr(a[i] / 4 + 1) && check((a[i] / 4 + 1) * 5 - i)) {
                puts("YES");
                printf("%d\n", (a[i] / 4 + 1) * 5 - i);
                flag = false;
                break;
            }
        }
        if (flag) puts("NO");
    }
    return 0;
}
