def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

[n, a, b] = map(int, input().split(" "))
for i in range(1, n + 1):
    for j in range(1, i + 1):
        if gcd(i, j) == 1:
            print(i ** gcd(a, b) - j ** gcd(a, b), gcd(i ** a - j ** a, i ** b - j ** b))
