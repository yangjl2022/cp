/**
 *    author:  yangjl
 *    created: 2024.17.08 20:25:32
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
constexpr int N = 2e5 + 10, LOG = 60;
int n;
ll k;
int a[N];
int f[N][LOG + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> f[i][0];
    }
    for(int j = 1; j <= LOG; ++j) {
        for(int i = 1; i <= n; ++i) {
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }

    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for(int i = 1; i <= n; ++i) {
        int p = i;
        for(int j = 0; j <= LOG; ++j) {
            if(k >> j & 1) {
                p = f[p][j];
            }
        }
        cout << a[p] << " ";
    }
    return 0;
}
/*
https://atcoder.jp/contests/abc367/tasks/abc367_E
基环树，倍增

*/