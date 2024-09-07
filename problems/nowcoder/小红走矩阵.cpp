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

constexpr int inf = 1e9;
vector<int> bfs(vector<vector<int>> const& g, int s) {
    const int n = g.size();
    vector<int> dis(n, inf), q{s};
    dis[s] = 0;
    for(int i=0; i<q.size(); ++i) {
        int u = q[i];
        for(auto v:g[u]) {
            if(dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push_back(v);
            }
        }
    }
    return dis;
}
template<class T>
void chMin(T &a, T b) {
    a=min(a,b);
}
template<class T>
void chMax(T &a, T b) {
    a=max(a,b);
}

int solve(vector<vector<char>> const& a) {
    const int n = a.size(), m = a[0].size();

    vector<vector<array<int,2>>> dp(n, vector<array<int,2>>(m, array<int,2>{inf, inf}));
    dp[0][0][0] = 0;
    for(int i=0; i<n; ++i) {
        for(int j=1; j<m; ++j) {
            if(a[i][j] == '.') {
                chMin(dp[i][j][0], dp[i][j-1][0] + 1);
                chMin(dp[i][j][1], dp[i][j-1][1] + 1);
            }
            chMin(dp[i][j][1], dp[i][j-1][0] + 1);
        }
        for(int j=m-2; j>=0; --j) {
            if( a[i][j] == '.') {
                chMin(dp[i][j][0], dp[i][j+1][0] + 1);
                chMin(dp[i][j][1], dp[i][j+1][1] + 1);
            }
            chMin(dp[i][j][1], dp[i][j+1][0] + 1);
        }

        if(i >= n-1) break;
        for(int j=0; j<m; ++j) {
            if(a[i+1][j] == '.') {
                chMin(dp[i+1][j][0], dp[i][j][0] + 1);
                chMin(dp[i+1][j][1], dp[i][j][1] + 1);
            }
            chMin(dp[i+1][j][1], dp[i][j][0] + 1);
        }
    }
    return min(dp[n-1][m-1][0], dp[n-1][m-1][1]);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<char>> a(n,vector<char>(m));
    vector<vector<int>> g0(n*m);    
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin>>a[i][j];
            if(a[i][j] == '.') {
                if(i > 0 and a[i-1][j] == '.') {
                    g0[i*m+j].push_back((i-1)*m+j);
                    g0[(i-1)*m+j].push_back(i*m+j);
                }
                if(j > 0 and a[i][j-1] == '.') {
                    g0[i*m+j].push_back(i*m+j-1);
                    g0[i*m+j-1].push_back(i*m+j);
                }
            }
        }
    }

    auto dis = bfs(g0, 0);
    int ans = dis.back();
    
    ans = min(ans, solve(a));

    vector<vector<char>> b(m ,vector<char>(n));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            b[j][i] = a[i][j];
        }
    }
    ans = min(ans, solve(b));

    if(ans >= inf) ans = -1;
    cout<<ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/86387/F

分层图，bfs即可
我写复杂了，用了之前一个题目只能走“下左右”的最短路，使用 dp 来求解

*/