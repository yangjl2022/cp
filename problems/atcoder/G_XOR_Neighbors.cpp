/**
 *    author:  yangjl
 *    created: 2024.10.08 21:10:07
**/
#include <bits/stdc++.h>
#ifdef YJL
#include "debug.h"
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x : v) {
        is >> x;
    }
    return is;
}

constexpr int N = 65;
struct Gauss {// index-0
    bitset<N> A[N];// 第m列A[i][m]是常数列
    int x[N];
    void print(int n, int m) {
        cerr << endl << n << "*" << m << " Matrix:" << endl;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j)
                cerr << A[i][j];
            cerr << A[i][m] << endl;
        }
    }
    bool solve(int n, int m) {
        int c = 0, r = 0;
        for(; r < n && c < m; ++r, ++c) {
            int r1 = -1;
            for(int i = r; i < n; ++i)
                if(A[i][c]) {
                    r1 = i;
                    break;
                }
            if(r1 == -1) {
                --r;
                continue;
            }
            if(r1 != r)
                swap(A[r], A[r1]);
            for(int i = 0; i < n; ++i) {
                if(i == r || !A[i][c]) continue;
                A[i] ^= A[r];
            }
        }
        for(int i = r; i < n; ++i)
            if(A[i][m])
                return false;
        for(int i = 0, j = 0; j < m; ++i, ++j) {
            while(j < m && (i >= n || !A[i][j]))
                x[j++] = 0;// free
            if(j < m)
                x[j] = A[i][m];
        }
        return true;
    }
};

int a[N][N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;

    Gauss e;
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v;
        --u, --v;
        e.A[u][v] = 1;
        e.A[v][u] = 1;
    }

    vector<ll> ans(n);
    for(int i = 0; i < n; ++i) {
        Gauss me(e);
        me.A[n][i] = 1;
        me.A[n][n] = 1;
        if(!me.solve(n + 1, n)) {
            cout << "No\n";
            exit(0);
        }
        for(int j = 0; j < n; ++j) {
            if(me.x[j]) {
                ans[j] |= 1ll << i;
            }
        }
    }

    cout << "Yes\n";
    for(int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
/*
https://atcoder.jp/contests/abc366/tasks/abc366_g
高斯消元，构造

1）
考虑一个退化的问题，如果点权只有 0,1 如何构造能满足条件呢？
设点的权值依次为 x1,x2,..,xn
对于一个节点的邻居，要满足 x[v1]^x[v2]^... = 0
总共 n 个方程，Z2下的方程组用bitset优化高斯消元解决即可

2）
注意到值域二进制范围有 60 位，而 n <= 60
所以可以考虑对每个节点在某一位上进行偏袒性的构造
- 对于节点 u，我们在第 i 位上，让它为 1，只要在1）中的方程组再加一条方程 x[u] = 1即可
- 如果此方程无解，说明无论找到一组 x1,...,xn 是的 u 的邻居异或为 0，对于整体 60 位更不可能了，直接输出无解
- 否则，这组 01 解就对应了每个节点在这一位上的取值

*/