from random import *
from os import system

n = 600
m = 100
lim = 100
T = 10

for test in range(0, 100000000):

    print(test)

    s = '{}\n'.format(T)

    for cas in range(0, T):
        s += '{} {}\n'.format(n, m)
        for i in range(0, n):
            l = randint(1, lim)
            r = randint(1, lim)
            if l > r:
                [l, r] = [r, l]
            s += '{} {}\n'.format(l, r)
        s += ' '.join(map(lambda x : str(randint(1, lim)), range(0, m)))
        s += '\n'

    inFile = open("in", "w")
    inFile.write(s)
    inFile.close()
    system('./E < in > out')
    system('./1 < in > ans')
    if system('diff out ans') != 0:
        break
