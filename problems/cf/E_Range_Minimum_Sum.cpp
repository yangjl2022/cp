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

int root;
vector<int> lch, rch;
void build(const vector<int> &v) {// index-0
    int n = v.size(), top = 0;
    vector<int> stk(n+1);
    lch.assign(n, -1);
    rch.assign(n, -1);
    for(int i=0; i<n; ++i) {
        int k = top;
        while(k and v[stk[k]] > v[i]) k--;// 小根堆
        // while(k && v[stk[k]] < v[i]) k--;// 大根堆
        if(k) rch[stk[k]] = i;
        else root = i;
        if(k<top) lch[i] = stk[k+1];
        stk[++k] = i;
        top = k;
    }
}

constexpr int N = 1e6 + 10;
int sz[N], a[N];
ll f[N];
// ll d[N];
ll size(int u) {
    return u == -1 ? 0 : sz[u];
}
void dfs(int u) {
    sz[u] = 1;
    if(lch[u] != -1) dfs(lch[u]);
    if(rch[u] != -1) dfs(rch[u]);
    sz[u] += size(lch[u]);
    sz[u] += size(rch[u]);

    f[u] = (size(lch[u])+1) * (size(rch[u])+1) * a[u];
}

ll ans[N], s;
void dfs2(int u, ll pre) {
    debug(u, pre);
    // ans[u] = s + d[u] + pre;
    ans[u] = s + pre-f[u];
    if(lch[u] != -1 and rch[u] != -1) {
        vector<pair<int,int>> ls{{lch[u], 0}}, rs{{rch[u], 1}};
        while(rch[ls.back().first] != -1) {
            ls.emplace_back(rch[ls.back().first], 0);
        }
        while(lch[rs.back().first] != -1) {
            rs.emplace_back(lch[rs.back().first], 1);
        }

        int m = ls.size()+rs.size();
        vector<pair<int,int>> nodes(m);
        merge(ALL(ls), ALL(rs), nodes.begin(), [&](const pair<int,int>& x,const pair<int,int>& y){
            return a[x.first] < a[y.first];
        });

        debug(u, nodes);
        
        vector<ll> nsz(m);
        nsz[m-1] = sz[nodes[m-1].first];
        for(int i=m-2; i>=0; --i) {
            int x = nodes[i].first;
            int init_sz = nodes[i].second ? size(rch[x]) : size(lch[x]);
            nsz[i] = 1 + nsz[i+1] + init_sz;
            ans[u] += -f[x] + (init_sz+1) * (nsz[i+1]+1) * a[x];
        }
    }

    
    ll f1 = (size(lch[u])) * (size(rch[u])+1) * a[u];
    if(lch[u] != -1) dfs2(lch[u], pre-f[u]+f1);
    ll f2 = (size(lch[u])+1) * (size(rch[u])) * a[u];
    if(rch[u] != -1) dfs2(rch[u], pre-f[u]+f2);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        int n;
        cin>>n;
        for(int i=0; i<n; ++i) {
            cin>>a[i];
        }
        build(vector<int>(a,a+n));
        dfs(root);

        debug(lch);
        debug(rch);
        debug(f, n);


        s = accumulate(f, f+n, 0ll);
        dfs2(root, 0);

        for(int i=0; i<n; ++i) {
            cout<<ans[i]<<" \n"[i+1==n];
        }
    }
    return 0;
}
/*
https://codeforces.com/contest/1988/problem/E
笛卡尔树
删除一个点时，只改变了左孩子的右链和右孩子的左链的权值
两条链的重构，可以通过归并排序重新计算权值
暴力遍历两条链即可，因为每个点最多作为上述情况2次。
复杂度 O(n)

*/