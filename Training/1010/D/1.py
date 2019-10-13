for cas in range(0, int(input())):
    n = int(input())
    while n % 2 == 0:
        n /= 2
    while n % 5 == 0:
        n /= 5
    print("Yes" if n != 1 else "No")
