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
    for(auto& x : v) is >> x;
    return is;
}

struct Dsu {
    vector<int> fa;
    Dsu(int n) : fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if(x == y) return false;
        fa[x] = y;
        return true;
    }
    int get(int x) {
        return fa[x] == x ? x : fa[x] = get(fa[x]);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    assert(2 <= n and n <= 1000);
    assert(2 <= m and m <= 1000);
    vector a(n, vector<char>(m));
    Dsu ds(n * m);
    int s = -1, t = -1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if(a[i][j] == '#') continue;
            if(a[i][j] == 'S') {
                assert(s == -1);
                s = i * m + j;
            } else if(a[i][j] == 'E') {
                assert(t == -1);
                t = i * m + j;
            } else {
                assert(a[i][j] == '.');
            }

            if(i and a[i - 1][j] != '#') {
                ds.unite(i * m + j, (i - 1) * m + j);
            }
            if(j and a[i][j - 1] != '#') {
                ds.unite(i * m + j, i * m + j - 1);
            }
        }
    }
    assert(s != -1);
    assert(t != -1);

    for(int i = 0; i < n; ++i) {
        int fs = 0, ft = 0;
        for(int j = 0; j < m; ++j) {
            if(ds.get(i * m + j) == ds.get(s)) {
                fs = 1;
            }
            if(ds.get(i * m + j) == ds.get(t)) {
                ft = 1;
            }
            if(i > 0 and ds.get((i - 1) * m + j) == ds.get(t)) {
                ft = 1;
            }
            if(i + 1 < n and ds.get((i + 1) * m + j) == ds.get(t)) {
                ft = 1;
            }
        }
        if(fs and ft) {
            cout << "YES\n";
            exit(0);
        }
    }

    for(int j = 0; j < m; ++j) {
        int fs = 0, ft = 0;
        for(int i = 0; i < n; ++i) {
            if(ds.get(i * m + j) == ds.get(s)) {
                fs = 1;
            }
            if(ds.get(i * m + j) == ds.get(t)) {
                ft = 1;
            }
            if(j > 0 and ds.get((i)*m + j - 1) == ds.get(t)) {
                ft = 1;
            }
            if(j + 1 < m and ds.get((i)*m + j + 1) == ds.get(t)) {
                ft = 1;
            }
        }
        if(fs and ft) {
            cout << "YES\n";
            exit(0);
        }
    }
    cout << "NO";
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/88455/C
并查集或者bfs
设s为起点某个能到的位置
1. 如果 s 所在行及其相邻两行有终点能到的位置
2. 如果 s 所在列及其相邻两列有终点能到的位置
那么就能成功通过

*/