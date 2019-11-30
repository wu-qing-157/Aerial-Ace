#include <cstdio>
#include <cstring>
#include <stack>

#define error() { puts("error"); return 0; }
#define improper() { puts("improper"); return 0; }
#define proper() { puts("proper"); return 0; }

const int N = 1e3 + 10;
int n, to[N], bcnt, opcnt;
char s[N];
std::stack<int> stack;

enum TYPE {LB, RB, NUM, OP};

TYPE type(char s) {
    if (s == '(') return LB;
    else if (s == ')') return RB;
    else if (s >= 'a' && s <= 'z') return NUM;
    else return OP;
}

int main() {
    fgets(s, N, stdin);
    n = int(strlen(s)) - 1;
    for (int i = 0, j = 0; i < n || (s[n = j] = '\0'); i++)
        if (s[i] != ' ')
            s[j++] = s[i];
    for (int i = 0, nxt = NUM; i < n; i++) {
        switch (type(s[i])) {
            case OP:
                if (nxt != OP) error();
                nxt = NUM;
                opcnt++;
                break;
            case NUM:
                if (nxt != NUM) error();
                nxt = OP;
                break;
            case LB:
                if (nxt != NUM) error();
                break;
            case RB:
                if (nxt != OP) error();
                break;
        }
        if (i == n - 1 && nxt == NUM) error();
    }
    for (int i = 0; i < n; i++) {
        if (type(s[i]) == LB) stack.push(i), bcnt++;
        if (type(s[i]) == RB) {
            if (stack.empty()) error();
            to[stack.top()] = i;
            stack.pop();
        }
    }
    if (!stack.empty()) error();
    if (to[0] == n - 1) improper();
    for (int i = 0; i < n; i++) {
        if (to[i] == i + 1)
            improper();
        if (to[i + 1] && to[i] - to[i + 1] == 1)
            improper();
        if (to[i] == i + 2)
            improper();
    }
    if (opcnt != bcnt + 1) improper();
    proper();
}
