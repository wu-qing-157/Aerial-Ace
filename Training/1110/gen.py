from random import randint

n = int(input())

print(n)

for i in range(2, n + 1):
    print(randint(1, i - 1), i)
