import math
import calendar
import decimal
import sys
import functools
# list.sort(key=functools.cmp_to_key(lambda a, b: -1 if a<b else 1))
import datetime
from collections import Counter


def input():
    return sys.stdin.readline().rstrip()


def ilist():
    return list(map(int, input().split()))


sys.setrecursionlimit(50000007)  # 递归调用的最大深度，默认只有1000
tt = 1
# tt = int(input())


def replace(a, x, y):
    for i in range(len(a)):
        if a[i] == x:
            a[i] = y


def main():
    n = int(input())
    g = [[] for i in range(n+1)]
    eid = dict()
    for i in range(n):
        u, v = ilist()
        g[u].append(v)
        g[v].append(u)
        eid[(u, v)] = i
        eid[(v, u)] = i

    isc = [0]*(n+1)
    vis = [0]*(n+1)
    st = []
    u0 = -1

    def dfs0(u, fa):
        nonlocal u0
        vis[u] = 1
        st.append(u)
        for v in g[u]:
            if not vis[v]:
                dfs0(v, u)
            elif v != fa and u0 == -1:
                u0 = v
                # print(v,st)
                assert (st)
                while st[-1] != v:
                    isc[st[-1]] = 1
                    st.pop()
                assert (st)
                isc[st[-1]] = 1
        if len(st) and st[-1] == u:
            st.pop()

    dfs0(1, 0)

    col = [0]*(n+1)
    ind = [0]*(n+1)
    a = [0]*(n+1)
    dep = [0]*(n+1)
    sz = 0

    def dfs1(u, c, fa):
        nonlocal sz
        if u == c:
            sz += 1
            ind[u] = sz
        else:
            dep[u] = dep[fa]+1
        col[u] = c
        for v in g[u]:
            if v != fa and ind[v] < 2:
                a[v] = u
            if not col[v]:
                dfs1(v, v if isc[v] else c, u)
    dfs1(u0, u0, 0)

    # print(isc, col, ind, dep)
    # print(a)

    ans = [0]*n
    u, v = 1, n
    if col[1] == col[n]:
        dis = 0
        while u != v:
            dis += 1
            if dep[u] >= dep[v]:
                # print('debug', eid[(u, a[u])])
                ans[eid[(u, a[u])]] = -1
                u = a[u]
            else:
                # print('debug', eid[(v, a[v])])
                ans[eid[(v, a[v])]] = -1
                v = a[v]
        # print('debug', ans)
        # print(dis)
        replace(ans, 0, dis)
    else:
        dis = 0
        fu, fv = col[u], col[v]
        while u != fu:
            ans[eid[(u, a[u])]] = -1
            u = a[u]
            dis += 1
        while v != fv:
            ans[eid[(v, a[v])]] = -1
            v = a[v]
            dis += 1
        if ind[u] < ind[v]:
            u, v = v, u
        d0 = ind[u]-ind[v]
        d1 = sz-d0
        if d0 == d1:
            pass
        elif d0 < d1:
            while u != v:
                ans[eid[(u, a[u])]] = d1+dis
                u = a[u]

        else:
            while v != u:
                ans[eid[(v, a[v])]] = d0+dis
                v = a[v]
        replace(ans, 0, min(d0, d1)+dis)

    print(*ans, sep="\n")


for t in range(tt):
    main()
