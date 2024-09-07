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

struct DSU {
    int n;
    vector<int> vis, nxt;
    DSU(int n): n(n), vis(n), nxt(n) {
        iota(nxt.begin(),nxt.end(),1);
    }
    int next(int i) {
        if(nxt[i]>=n)
            return n;
        if(vis[nxt[i]])
            nxt[i]=this->next(nxt[i]);
        return nxt[i];
    }
    void set(int i) {
        vis[i]=1;
    }
    int begin(int i) {
        while(i<n && vis[i])
            i=this->next(i);
        return i;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin>>n>>q;
    vector<array<int,3>> a(q);
    for(auto& [c,l,r]:a) {
        cin>>l>>r>>c;
        --l,--r;
    }
    sort(ALL(a));
    debug(a);

    DSU ds(n);
    int num = 0;
    ll ans = 0;
    for(auto& [c,l,r]:a) {
        for(int i=ds.begin(l); i<r; i = ds.next(i)) {
            ds.set(i);
            num++;
            ans += c;
        }
        num++;
        ans += c;
    }
    if(num < n+q-1) {
        cout<<"-1";
    }else {
        cout<<ans;
    }
    return 0;
}
/*
https://atcoder.jp/contests/abc364/tasks/abc364_f
kruskal 算法的思路，从小到大加边，对于一段区间判断有效加边
使用并查集优化遍历过程

*/