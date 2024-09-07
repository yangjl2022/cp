#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;
template<class T>
void chMin(T &a, T b) {
    a=min(a,b);
}
template<class T>
void chMax(T &a, T b) {
    a=max(a,b);
}

constexpr int N = 2e5 + 10;
int n;
vector<int> g[N];
int dp[N][2][2];// dp[u][0/1: 选不选u][0/1: 当前子树下是否选了deg=1的节点]
int re[2][2];

void dfs(int u,int fa) {
    memset(dp[u], 0x3f, sizeof dp[u]);
    dp[u][0][0] = 0;
    dp[u][1][g[u].size()==1] = 1;
    for(int v:g[u]) {
        if(v == fa) continue;
        dfs(v, u);

        memset(re, 0x3f, sizeof re);
        for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
                for(int i1=0; i1<2; ++i1) {
                    for(int j1=0; j1<2; ++j1) {
                        if(!i and !i1) continue;
                        chMin(re[i][j|j1], dp[u][i][j]+dp[v][i1][j1]);
                    }
                }
            }
        }
        memcpy(dp[u], re, sizeof re);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        cin>>n;
        for(int i=1; i<=n; ++i) {
            g[i].clear();
        }

        for(int i=1; i<n; ++i) {
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        dfs(1, 0);
        int ans = 0;
        for(int i=0; i<2; ++i) {
            for(int j=0; j<2; ++j) {
                chMax(ans, n-dp[1][i][j]+(j==1));
            }
        }
        cout<< ans <<"\n";
    }
    return 0;
}
/*
最后重构的树看作一颗有根树，定义孩子数等于1的节点为叶节点，其他的为分支节点。
答案为：叶节点数 + [根节点孩子数为1]
两相邻节点不可能同时成为叶节点
每条边上至少一个点作为分支节点 -> 点覆盖
每种点覆盖 -> 对应一种重构方式，其中分支节点一定是覆盖点

最多叶节点 -> 最少分支点 -> 最小点覆盖

答案为最小点覆盖，并且如果存在一种最小点覆盖包含deg=1的节点，那么答案+1
https://codeforces.com/contest/1984/problem/E
*/