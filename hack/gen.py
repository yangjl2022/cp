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
    if not os.access("d:/CPPCODE/hack/data", os.F_OK):
        os.makedirs("d:/CPPCODE/hack/data")
    with open('d:/CPPCODE/hack/data/1.in', 'w') as fo:
        writeln(fo, 1)
        n = 2
        m = 100000
        h = 1000000
        writeln(fo, n, m, h)
        up = 2147483647

        presum = 0
        tot = 0
        for i in range(m):
            writeln(fo, 1, end=' ')
            presum += 1
            tot += presum
            temp = up-tot-presum+1
            if temp >= 1 and temp <= 1000000 and presum+temp <= h:
                writeln(fo, 1000000)
                break
        presum = 0
        tot = 0
        for i in range(m):
            writeln(fo, 1, end=' ')
            presum += 1
            tot += presum
            temp = up-tot-presum+1
            if temp >= 1 and temp <= 1000000 and presum+temp <= h:
                writeln(fo, temp)
                break


if __name__ == '__main__':
    main()
