#include "bits/stdc++.h"
#ifndef YJL
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

struct Dsu {
    vector<int> fa;
    Dsu(int n): fa(n) {
        iota(fa.begin(), fa.end(), 0);
    }
    bool unite(int x, int y) {
       x=get(x), y=get(y);
       if(x==y) return false;
       fa[x]=y;
       return true;
    }
    int get(int x) {
        return fa[x]==x ? x: fa[x]=get(fa[x]);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin>>n>>m>>q;
    vector<array<int,3>> e(m);
    for(auto& [w,u,v]:e) {
        cin>>u>>v>>w;
        --u,--v;
    }

    sort(ALL(e),[&](const array<int,3>& x,const array<int,3>& y){
        return x[0]>y[0];
    });

    vector<int> f;
    Dsu ds(n);
    int num = n;
    for(auto [w,u,v]:e) {
        num -= ds.unite(u,v);
        f.push_back(num);
    }

    while(q--) {
        int l,r;
        cin>>l>>r;
        int i = lower_bound(ALL(f), r, greater())-f.begin();
        if(i >= f.size()) {
            cout<<"NO ANSWER\n";
            continue;
        }
        cout<<e[i][0]<<"\n";
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/85350/C
二分答案，判断>=mid的边能形成几个连通块，若小于 R 个，那么通过断开边 L~R的目标都能达成。
也可以预先记录连通块数量为x时，加的边权是多少，做到O(n)

*/