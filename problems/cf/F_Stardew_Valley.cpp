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

struct UndirectEulerGraph {
    int n,en;
    vector<vector<pair<int,int>>> g;
    vector<pair<int,int>> edge;
    UndirectEulerGraph(int n):n(n),g(n),en(0) {}
    void addEdge(int u,int v) {
        edge.emplace_back(u, v);
        edge.emplace_back(v, u);
        g[u].emplace_back(v,en++);
        g[v].emplace_back(u,en++);
    }
    vector<pair<int,int>> path;
    vector<int> idx;
    vector<bool> vis;
    void dfs(int u,int eid=-1) {
        while(idx[u]<g[u].size()) {
            auto [v,i]=g[u][idx[u]++];
            if(vis[i]) continue;
            vis[i]=vis[i^1]=true;
            dfs(v,i);
        }
        if(eid!=-1)
            path.push_back(edge[eid]);
    }
    bool findEulerPath() {
        int s=-1,t=-1,flag=-1;
        for(int i=0; i<n; ++i) {
            if(g[i].size() && !~flag) flag=i;
            if(g[i].size()&1) {
                if(s==-1) s=i;
                else if(t==-1) t=i;
                else return false;
            }
        }
        // if(s!=-1) return false;// 要的是欧拉回路，而不是欧拉通路时
        assert(s == -1);
        if(s==-1) s=flag;
        path.clear();
        idx.assign(n,0);
        vis.assign(en,false);
        fill(idx.begin(),idx.end(),0);
        dfs(s);
        // if(path.size()!=en/2) return false;// 边不连通
        assert(path.size() == en/2);
        reverse(path.begin(),path.end());
        return true;
    }
};

void solve() {
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> e[2];
    vector<int> isPoint(n);
    for(int i=0; i<m; ++i) {
        int u,v,c;
        cin>>u>>v>>c;
        --u,--v;
        e[c].emplace_back(u,v);
        if(c == 1) {
            isPoint[u] ^= 1;
            isPoint[v] ^= 1;
        }
    }

    vector<vector<int>> g2(n);
    for(auto [u,v] : e[0]) {
        g2[u].push_back(v);
        g2[v].push_back(u);
    }

    vector<int> vis(n), fa(n, -1);
    
    auto proc = [&](int u,int lca) {
        while(u != lca) {
            e[1].emplace_back(u, fa[u]);
            u = fa[u];
        }
    };

    vector<int> remain(n);
    function<void(int)> dfs = [&](int u) {
        remain[u] = isPoint[u] ? u : -1;
        vis[u] = 1;
        for(int v:g2[u]) {
            if(vis[v]) continue;
            fa[v] = u;
            dfs(v);
            if(remain[v] != -1) {
                if(remain[u] != -1) {
                    proc(remain[u], u);
                    proc(remain[v], u);
                    remain[u] = -1;
                }else {
                    remain[u] = remain[v];
                }
            }
        }
    };

    for(int i=0; i<n; ++i) {
        if(vis[i]) continue;
        dfs(i);
        if(remain[i] != -1) {
            cout<<"NO\n";
            return;
        }
    }

    UndirectEulerGraph ug(n);
    for(auto [u,v]:e[1]) {
        ug.addEdge(u, v);
    }
    ug.findEulerPath();

    cout<<"YES\n";
    cout<<ug.path.size()<<'\n';
    int first = 1;
    for(auto [u,v]:ug.path) {
        if(first) {
            cout<<u+1<<" "<<v+1<<' ';
            first = 0;
        }else {
            cout<<v+1<<' ';
        }
        // cout<<e[1][i/2].first+1<<" "<<e[1][i/2].second+1<<"\n";
    }
    cout<<'\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int tt;
    cin>>tt;
    while(tt--) {
        solve();
    }
    return 0;
}
/*
https://codeforces.com/contest/1994/problem/F
选择所有1边和部分0边，是的原图具有欧拉回路。
对于所有1边建图，设为图A，图A中度数为1的节点必须通过0边来 fix，我们称这样的节点编号为 key
考虑0边建图，设为图B，对于图B的每个连通块：
1. 如果包含奇数个 key，那么不管如何选取 0 边，都不可能让这一块的点度数满足要求，无解，
因为选边总的度数变化为偶数。
2. 如果包含偶数个 key，那么我们随意求一个生成树，在树上，我们对 key 自下而上配对，
在 lca 处对子树中的节点两两配对，这样可以保证选取的边不重复，成功 fix deg

图 A 的所有边 和图B 的部分边一起组成了欧拉图，使用欧拉图的算法求解即可。
*/