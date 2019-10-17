from random import randint

a = [[0 for i in range(200)] for j in range(200)]
b = [[0 for i in range(200)] for j in range(200)]
x1 = randint(1, 200)
x2 = randint(x1, 200)
y1 = randint(1, 200)
y2 = randint(y1, 200)

x1 = 1
x2 = 1
y1 = 200
y2 = 200

n = 200
m = 200
q = 1

for i in range(0, 200):
    for j in range(0, 200):
        b[i][j] = randint(1, 40)
        a[i][j] = randint(0, 0)

print(10)


for cas in range(0, 10):
    print(n, m)

    for i in range(0, 200):
        print(' '.join(map(str, a[i])))

    for i in range(0, 200):
        print(' '.join(map(str, b[i])))

    print(1)
    print(x1, y1, x2, y2)
