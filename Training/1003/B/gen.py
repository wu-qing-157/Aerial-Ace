from random import randint as rd

print(100)

for s in [16, 17, 18, 19, 20]:
    for cas in range(0, 10):
        l = rd(1, s - 1)
        r = s - l
        print(l, r, 1, 100)
for s in [16, 17, 18, 19, 20]:
    for cas in range(0, 10):
        l = rd(1, s - 1)
        r = s - l
        print(l, r, 100, 1)
