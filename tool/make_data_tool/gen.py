# 使用指南：https://github.com/luogu-dev/cyaron/wiki/%E5%9B%BE-Graph
from cyaron import *
import os


def writeln(fo, *args, sep=' ', end='\n'):
    ans = ''
    flag = 0
    for x in args:
        if flag:
            ans += sep
        else:
            flag = 1
        ans += str(x)
    ans += end
    fo.write(ans)


def main():
    if not os.access("./data/", os.F_OK):
        os.makedirs("./data/")
    for i in range(21, 25):
        with open('./data/'+str(i)+'.in', 'w') as fo:
            n = randint(100, 100001)
            writeln(fo, n)
            for i in range(n):
                writeln(fo, i, i)

    return
    for i in range(11, 21):
        with open('./data/'+str(i)+'.in', 'w') as fo:
            n = 100000
            low = n//2
            high = n*3//4
            m = rd.randint(low, high)  # l=r的数
            writeln(fo, n)
            for x in rd.choice(high, m, replace=False):
                writeln(fo, x, x)

            for i in range(n-m):
                l = rd.randint(0, 1e9)
                r = rd.randint(l, 1e9)
                writeln(fo, l, r)


main()
