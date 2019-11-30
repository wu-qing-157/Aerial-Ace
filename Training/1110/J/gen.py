from random import randint

[n, m] = map(int, input().split(' '))

s = ['.' for i in range(0, n)]
b = [randint(0, n - 1) for i in range(0, m)]
for i in b:
    s[i] = '#'
print(''.join(s))
