#include "bits/stdc++.h"
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

constexpr int N = 3e5 + 10;
constexpr ll inf = 4e18;
ll a[N];
vector<int> g[N];
vector<ll> f[N];
vector<ll> pref[N];
vector<ll> suf[N];
void dfs(int u,int fa) {
    int sz = max<int>(2, g[u].size()+2);
    f[u].resize(sz, inf);
    for(int i=1; i<sz; ++i) {
        f[u][i] = a[u]*i;
    }

    vector<ll> w(sz+1);

    for(int v:g[u]) {
        if(v==fa) continue;
        dfs(v, u);
        for(int i=1; i<f[v].size() and i<sz; ++i) {
            f[u][i] += min(pref[v][i], suf[v][i+1]);
        }
        if(sz > f[v].size()) {
            w[f[v].size()] += pref[v].back();
        }
    }

    pref[u].assign(sz + 1, inf);
    suf[u].assign(sz + 1, inf);
    for(int i=1; i<sz; ++i) {
        w[i] += w[i-1];
        f[u][i] += w[i];
        pref[u][i+1] = min(pref[u][i], f[u][i]);
    }
    for(int i=sz-1;i>=0; --i) {
        suf[u][i] = min(suf[u][i+1], f[u][i]);
    }

    debug(u, f[u]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        for(int i=0; i<n; ++i) {
            g[i].clear();
            cin>>a[i];
        }
        for(int i=1,u,v; i<n; ++i) {
            cin>>u>>v;
            --u,--v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        dfs(0, -1);
        cout<<*min_element(ALL(f[0]))<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1988/problem/D
设monster_i 攻击次数为 b_i
题目限制条件可以转化为 若(u,v) \in E，那么 b_u != b_v

那么 b_u = mex_{(u,v) \in E}(b_v)（贪心反证）
所以 b_u <= deg_u + 1

DP解决
*/