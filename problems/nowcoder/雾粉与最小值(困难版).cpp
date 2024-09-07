#include<iostream>
#include<cmath>
#include<cstring>
#include<cassert>
#include<string>
#include<queue>
#include<deque>
#include<stack>
#include<algorithm>
#include<unordered_map>
#include<map>
#include<vector>
#include<set>
#include<unordered_set>
#include<bitset>
#include<climits>
#include<numeric>
#include<functional>
#include<iomanip>
#ifdef YJL
#include<debug.h>
#else
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

struct Tag {
    ll k,b;
    void init() {
        k = 0;
        b = 0;
    }
    void unite(const Tag &val) {
        k += val.k;
        b += val.b;
    }
};
struct Data {
    ll x;
    void init(int i) {
        x = 0;
    }
    void add(const Tag &val,int l,int r) {
        // k*l+b, k*(l+1)+b, ...
        x += val.k*(r-l+1)*(l+r)/2 + val.b*(r-l+1);
    }
    friend Data operator+(const Data &lhs,const Data & rhs) {
        Data re;
        re.x=lhs.x+rhs.x;
        return re;
    }
};
struct Segtree {
    #define u1 (u<<1)
    #define u2 (u<<1|1)
    vector<Data> tr;
    vector<Tag> lz;
    int Lpoint,Rpoint;
    template<class ...T>
    Segtree(int L,int R,const T&...args):Lpoint(L),Rpoint(R)
    ,tr(4<<__lg(R-L+1)),lz(tr.size()) {// a[L~R]建树
        build(1,L,R,args...);
    }
    template<class ...T>
    void build(int u,int l,int r,const T&...args) {
        lz[u].init();
        if(l==r) return tr[u].init(l,args...);
        int mid=(l+r)>>1;
        build(u1,l,mid,args...);
        build(u2,mid+1,r,args...);
        tr[u]=tr[u1]+tr[u2];
    }
    void push_lazy(int u,int l,int r) {
        tr[u].add(lz[u],l,r);
        if(l!=r) lz[u1].unite(lz[u]),lz[u2].unite(lz[u]);
        lz[u].init();
    }
    void change(int l,int r,const Tag &val) {
        if(Lpoint<=l&&l<=r&&r<=Rpoint)
            change(1,Lpoint,Rpoint,l,r,val);
    }
    void change(int u,int l,int r,int ql,int qr,const Tag &val) {
        push_lazy(u,l,r);
        if(l==ql&&r==qr) lz[u]=val;
        else {
            int mid=(l+r)>>1;
            if(qr<=mid) change(u1,l,mid,ql,qr,val);
            else if(ql>mid) change(u2,mid+1,r,ql,qr,val);
            else change(u1,l,mid,ql,mid,val),change(u2,mid+1,r,mid+1,qr,val);
            push_lazy(u1,l,mid),push_lazy(u2,mid+1,r);
            tr[u]=tr[u1]+tr[u2];
        }
    }
    Data query(int l,int r) {
        return query(1,Lpoint,Rpoint,l,r);
    }
    Data query(int u,int l,int r,int ql,int qr) {
        push_lazy(u,l,r);
        if(l==ql&&r==qr) return tr[u];
        int mid=(l+r)>>1;
        if(qr<=mid) return query(u1,l,mid,ql,qr);
        if(ql>mid) return query(u2,mid+1,r,ql,qr);
        return query(u1,l,mid,ql,mid)+query(u2,mid+1,r,mid+1,qr);
    }
    #undef u1
    #undef u2
};


struct Node {
    int v, s, t;
    int id;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    vector<int> a(n);
    vector<pair<int,int>> b;
    for(int i=0; i<n; ++i) {
        cin>>a[i];
        b.emplace_back(a[i], i);
    }
    sort(ALL(b), greater());

    int m;
    cin>>m;
    vector<Node> qry(m);
    for(int i=0; i<m; ++i) {
        int v,s,t;
        cin>>v>>s>>t;
        qry[i] = {v, s, t, i};
    }
    sort(ALL(qry),[&](const Node& x,const Node& y){
        return x.v > y.v;
    });

    vector<int> lp(n),rp(n),vis(n);
    for(int i=0; i<n; ++i)
        lp[i] = rp[i] = i;
    Segtree tr(1, n);
    auto add = [&](int i) {
        vis[i] = 1;
        int l = i, r = i;
        if(i-1>=0 and vis[i-1]) {
            l = lp[i-1];
            tr.change(1, i-l, {1, -1-(i-l)});
        }
        if(i+1<n and vis[i+1]) {
            r = rp[i+1];
            tr.change(1, r-i, {1, -1-(r-i)});
        }
        int t = r-l+1;
        tr.change(1, t, {-1, t+1});
        rp[l] = r;
        lp[r] = l;
    };

    int i = 0;
    vector<ll> ans(m);
    for(auto [v, s, t, id]:qry) {
        while(i<n and b[i].first>=v) {
            add(b[i].second);
            i++;
        }
        ans[id] = tr.query(s, t).x;
    }

    for(int i=0; i<m; ++i) {
        cout<<ans[i]<<'\n';
    }
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/84527/D

线段树区间加等差数列



*/