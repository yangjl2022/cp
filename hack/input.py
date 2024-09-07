from numpy import random as rd
# 使用指南：https://github.com/luogu-dev/cyaron/wiki/%E5%9B%BE-Graph
from cyaron import *


def toBinary(a: int, n: int) -> str:
    s = str(bin(a))[2:]
    if len(s) > n:
        return s[len(s)-n:]
    else:
        return '0'*(n-len(s))+s


def main():
    n = randint(2, 5)
    print(n)
    for i in range(n):
        if i == 0:
            print(n-1)
            for j in range(2, n+1):
                print(j, randint(0, 1))
            continue
        s = randint(0, n-1-i)
        print(s)
        L = rd.choice(n-1-i, s, replace=False)
        for x in L:
            print(i+1+x+1, randint(0, 1))


if __name__ == '__main__':
    main()
