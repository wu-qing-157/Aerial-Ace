from random import randint

n = 5
LIM = 10
k = randint(1, n)

a = [randint(1, LIM) for i in range(0, n)]
for i in range(1, len(a)):
    a[i] += a[i - 1]

print(n, k)
print(' '.join(map(str, a)))
