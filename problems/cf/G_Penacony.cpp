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

struct Tag {
    int d;
    void init() {
        d = 0;
    }
    void unite(const Tag &val) {
        d += val.d;
    }
};
struct Data {
    int mn, c;
    int ans;
    void init(int i) {
        mn = ans = 0;
        c = 1;
    }
    void add(const Tag &val,int l,int r) {
        if(val.d == 0) return;
        if(val.d < 0) {
            if((mn += val.d) == 0) {
                ans -= c;
            }
        }else {
            if(mn == 0) {
                ans += c;
            }
            mn += val.d;
        }
    }
    friend Data operator+(const Data &lhs,const Data & rhs) {
        Data re{};
        re.mn = min(lhs.mn, rhs.mn);
        if(lhs.mn == re.mn) re.c += lhs.c;
        if(rhs.mn == re.mn) re.c += rhs.c;
        re.ans = lhs.ans + rhs.ans;
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
    void change(int l,int r,int d) {
        if(Lpoint<=l&&l<=r&&r<=Rpoint)
            change(1,Lpoint,Rpoint,l,r,{d});
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n,m;
        cin>>n>>m;
        vector<vector<int>> p(n);
        Segtree tr(0, n-1);

        for(int i=0,a,b; i<m; ++i) {
            cin>>a>>b;
            --a,--b;
            p[a].push_back(b);
            tr.change(a, b-1, 1);
        }

        int ans = tr.query(0, n-1).ans;
        for(int i=0; i<n; ++i) {
            for(int j:p[i]) {
                if(i < j) {
                    tr.change(i, j-1, -1);
                    tr.change(j, n-1, 1);
                    if(i-1>=0) {
                        tr.change(0, i-1, 1);
                    }
                    p[j].push_back(i);
                }else {// j<i
                    tr.change(i, n-1, -1);
                    if(j-1>=0) {
                        tr.change(0, j-1, -1);
                    }
                    tr.change(j, i-1, 1);
                }
            }
            p[i].clear();
            ans = min(ans, tr.query(0, n-1).ans);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
/*
https://codeforces.com/contest/1996/problem/G
差点写线段树优化建图跑 2-SAT了（其实思路不对）
之前cf有个题我这么写，超内存了，这个题估计也够呛

肯定有简单的方法
首先考虑不成环的情况下，改题怎么做
- 发现不成环，每对点的路径唯一，那么答案就是路径并集长度

如果成环，可以断边转化为上述问题：
1. 枚举每一条边，断开它
2. 使用线段树动态维护所有路径并集

*/