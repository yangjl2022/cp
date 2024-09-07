/**
 *    author:  yangjl
 *    created: 2024.11.08 00:22:52
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

vector<int> bfs(vector<vector<int>> const& g, int s) {
    const int n = g.size();
    vector<int> dis(n, n), q{s};
    dis[s] = 0;
    for(int i = 0; i < q.size(); ++i) {
        int u = q[i];
        for(auto v : g[u]) {
            if(dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push_back(v);
            }
        }
    }
    return dis;
}

template<class T>
istream& operator>>(istream& is, vector<T>& v) {
    for(auto& x : v) {
        is >> x;
    }
    return is;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin >> tt;
    while(tt--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n);
        for(int i = 0; i < n - 1; ++i) {
            g[i].push_back(i + 1);
        }
        for(int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v;//>>w;
            --u, --v;
            g[u].push_back(v);
        }
        auto f = bfs(g, 0);

        vector<int> d(n + 1);
        for(int i = 0; i < n; ++i) {
            for(int j : g[i]) {
                int p = j - 1 - (f[i] + 1);
                if(p > i) {
                    d[i + 1]++;
                    d[p + 1]--;
                }
            }
        }

        for(int i = 0; i < n - 1; ++i) {
            if(i) {
                d[i] += d[i - 1];
            }
            cout << (d[i] == 0);
        }
        cout << "\n";
    }
    return 0;
}
/*
https://codeforces.com/contest/1998/problem/D
思维，最短路，差分

分析发现，A 能赢当且仅当以下情况出现：
- B 从 s 开始走了一段距离
- A 从 i(i<s) 跳过 B 的位置到达 j
- 此时 B 还在 (i,j) 的某个位置

考虑枚举以上的边 i->j，筛选出 B 输掉的情况：
- 首先 A 肯定会以最短路的方式快速到达 i
- 此后 B 走到了 s+dis[i]+1
- 下一步必须满足 j>s+dis[i]+1，即 s <= j-1-dis[i]-1
- 还要满足 s > i

于是 [i+1, j-2-dis[i]] 范围内的 s 都会输掉
使用差分形式记录答案，得解

*/