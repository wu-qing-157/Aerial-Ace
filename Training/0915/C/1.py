from random import randint as rd
print(1)
print(100000)
for i in range(0, 3):
    for j in range(0, 10000):
        print(rd(1, 100000), end=" ")
    print()
