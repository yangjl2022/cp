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


struct Data0 {
    int mn,mx,ok;
    template<class T>
    void init(int i,const T& a) {
        add(a[i]);
    }
    // add(const T& args... )
    void add(int val) {
        mn = mx = val;
        ok = 1;
    }
    friend Data0 operator+(const Data0 &lhs,const Data0 & rhs) {
        Data0 re;
        re.mn = min(lhs.mn, rhs.mn);
        re.mx = max(lhs.mx, rhs.mx);
        re.ok = lhs.ok and rhs.ok and (lhs.mx <= rhs.mn);
        return re;
    }
};
struct Segtree {
    #define u1 (u<<1)
    #define u2 (u<<1|1)
    vector<Data0> tr;
    vector<int> mp;
    int Lpoint,Rpoint;
    template<class ...T>
    Segtree(int L,int R,const T&...args):Lpoint(L),Rpoint(R)
    ,tr(4<<__lg(R-L+1)),mp(R-L+1) {// a[L~R]建树
        build(1,L,R,args...);
    }
    template<class ...T>
    void build(int u,int l,int r,const T&...args) {
        if(l==r) {
            tr[u].init(l,args...);
            mp[l-Lpoint]=u;
            return;
        }
        int mid=(l+r)>>1;
        build(u1,l,mid,args...);
        build(u2,mid+1,r,args...);
        tr[u]=tr[u1]+tr[u2];
    }
    template<class ...T>
    void change(int pos,const T&...args) {
        int u=mp[pos-Lpoint];
        tr[u].add(args...);
        for (u>>=1; u; u>>=1) tr[u]=tr[u1]+tr[u2];
    }
    auto query0() {
        return query0(1,Lpoint,Rpoint);
    }
    int query0(int u,int l,int r, int bound = 2e9) {
        debug(u,l,r,bound);
        if(l == r) {
            if(tr[u].mx <= bound) {
                return l;
            }
            return l-1;
        }
        int mid=(l+r)>>1;
        int rbound = min(bound, tr[u2].mn);
        if(tr[u1].ok and tr[u1].mx <= rbound) {
            return query0(u2, mid+1, r, bound);
        }
        return query0(u1, l, mid, rbound);
    }
    auto query1() {
        return query1(1,Lpoint,Rpoint);
    }
    int query1(int u,int l,int r, int bound = -2e9) {
        if(l == r) {
            if(tr[u].mx >= bound) {
                return r;
            }
            return r+1;
        }
        int mid=(l+r)>>1;
        int lbound = max(bound, tr[u1].mx);
        if(tr[u2].ok and tr[u2].mn >= lbound) {
            return query1(u1, l, mid, bound);
        }
        return query1(u2, mid+1, r, lbound);
    }
    #undef u1
    #undef u2
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        vector<int> a(n);
        cin>>a;

        Segtree tr(0, n-1, a);

        auto calc = [&]() {
            int l = tr.query0();
            debug(l);
            if(l == n-1) {
                cout<<"-1 -1\n";
                return;
            }
            l+=2;
            int r = tr.query1();
            cout<<l<<" "<<r<<'\n';
        };
        calc();
        
        int q;
        cin>>q;
        vector<pair<int,int>> b(q);
        for(auto &[p, x]:b) {
            cin>>p>>x;
            --p;
            tr.change(p, x);
            // a[p] = x;
            calc();
        }
    }
    return 0;
}
/*
https://codeforces.com/contest/1982/problem/F
题不难，赛时想到二分，哈希，线段树，就直接写了，nlognlogn被卡了
其实多想想就树上二分出来的

*/