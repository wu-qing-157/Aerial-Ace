from random import randint
print(12)
for i in range(0, 12):
    for j in range(0, 12):
        print('B' if randint(1, 2) == 1 else 'W' if randint(1, 5) <= 4 else '.', end='')
    print()
for i in range(0, 12):
    for j in range(0, 12):
        print(randint(1, 1000000), end=' ')
    print()
