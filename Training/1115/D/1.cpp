#include <iostream>
#include <string>

int n;
std::string s;

int main() {
    static int T;
    std::cin >> T;
    while (T--) {
        std::cin >> s;
        n = int(s.length());
        if (s[n - 1] == 'a' || s[n - 1] == 'o' || s[n - 1] == 'u') s += "s";
        else if (s[n - 1] == 'i') s += "os";
        else if (s[n - 1] == 'y') s.pop_back(), s += "ios";
        else if (s[n - 1] == 'l' || s[n - 1] == 'r' || s[n - 1] == 'v') s += "es";
        else if (s[n - 1] == 'n') s.pop_back(), s += "anes";
        else if (s[n - 1] == 'e' && s[n - 2] == 'n') s.pop_back(), s.pop_back(), s += "anes";
        else if (s[n - 1] == 't' || s[n - 1] == 'w') s += "as";
        else s += "us";
        std::cout << s << std::endl;
    }
    return 0;
}
