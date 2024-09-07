#include "bits/stdc++.h"
#ifndef YJL
#define debug(...)0
#endif
#define ALL(a) a.begin(),a.end()
using namespace std;
using ll = long long;

int n, m;
template<class T>
struct Dijkstra {
    static constexpr T inf=numeric_limits<T>::max();
    vector<vector<pair<int,T>>> g;
    vector<T> dis;
    Dijkstra(int n):g(n) {}
    void addEdge(int u,int v,T w) {
        g[u].emplace_back(v,w);
        // g[v].emplace_back(u,w);
    }
    struct Node {
        int u;
        T dis;
        bool operator<(const Node& O)const {
            return dis>O.dis;
        }
    };
    void dij(int s) {
        priority_queue<Node> q;
        dis.assign(g.size(),inf);
        dis[s]=0;
        q.push({s, 0});
        while(q.size()) {
            auto [u,tdis]=q.top();
            q.pop();
            if(tdis>dis[u]) continue;

            int c = u>=n*m;
            int t = u-c*n*m;
            int x = t/m, y = t%m;
            debug(c, x, y, tdis);
            
            for(auto [v,w]:g[u]) {
                if(tdis < dis[v]-w) {
                    dis[v]=tdis+w;
                    q.push({v, dis[v]});
                }
            }
        }
    }
};

const vector<int> dx{0,1,0,-1};
const vector<int> dy{1,0,-1,0};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m;
    vector a(n,vector<char>(m));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin>>a[i][j];
        }
    }
    vector<int> c(m);
    for(int i=0; i<m; ++i) {
        cin>>c[i];
    }

    Dijkstra<ll> g(n*m+m);
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            int u = i*m+j;
            g.addEdge(n*m+j, u, 0);
            for(int idx=0; idx<dx.size(); ++idx) {
                int nx=i+dx[idx], ny=j+dy[idx];
                if(nx<0 || nx>=n || ny<0 || ny>=m)
                    continue;
                int v = nx*m+ny;
                if(a[nx][ny]=='.')
                    g.addEdge(u, v, 0);
                g.addEdge(u, n*m+ny, c[ny]);
            }
        }
    }
    g.dij(0);
    cout<<g.dis[n*m-1]<<'\n';
    return 0;
}
/*
牛客周赛47F
https://ac.nowcoder.com/acm/contest/84851/F

思维
建图技巧
最短路

*/