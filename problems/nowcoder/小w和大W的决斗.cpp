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
    for(auto& x:v) is>>x;
    return is;
}

int mex(const vector<int>& a) {
    vector<int> vis(a.size()+1);
    for(int x:a)
        if(x<(int)a.size())
            vis[x]=1;
    int p=0;
    while(vis[p]) p++;
    return p;
}

constexpr int N = 110;
int g[N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1; i<N; ++i) {
        vector<int> nxt;
        for(int j=0; j<i; ++j) {
            nxt.push_back(g[j]);
        }
        for(int i0=1; i0<i; ++i0) {
            for(int i1=i0; i1+i0<i; ++i1) {
                int i2 = i-i0-i1;
                if(i2 < i1) continue;
                nxt.push_back(g[i0]^g[i1]^g[i2]);
            }
        }
        g[i] = mex(nxt);
        if(i<=10) {
            debug(i, g[i], nxt);
        }
    }
    
    int n;
    cin>>n;
    int ans = 0;
    for(int i=0,x; i<n; ++i) {
        cin>>x;
        ans ^= g[x];
    }
    cout<<(ans ? "w win":"W win");
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/87255/C
经典图游戏的组合
按题意进行SG函数打表

*/