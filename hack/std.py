import sys
import decimal
import functools
# list.sort(key=functools.cmp_to_key(lambda a, b: -1 if a<b else 1))
from bisect import bisect
from collections import Counter
import math
import datetime
import calendar


def input():
    return sys.stdin.readline().rstrip()


def ilist():
    return list(map(int, input().split()))


sys.setrecursionlimit(5000006)  # 递归调用的最大深度，默认只有1000
tt = 1
tt = int(input())


def main():
    a,b=ilist()
    print(a*b)


for t in range(tt):
    main()