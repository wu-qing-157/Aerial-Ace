from os import system

for cas in range(0, 1000000):
    if system('pypy3 gen.py > in && ./1 < in > out && ./brute < in > ans && diff out ans'):
        print('WA')
