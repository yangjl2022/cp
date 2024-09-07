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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector a(n,vector<int>(m));
    int V = n*50;
    vector<int> dp(V+1);
    dp[0] = 1;
    for(int i=0; i<n; ++i) {
        vector<int> re(V+1);
        for(int j=0; j<m; ++j) {
            cin>>a[i][j];
        }
        for(int k=V; k>=1; --k) {
            for(int j=0; j<m; ++j) {
                if(k >= a[i][j]) {
                    re[k] |= dp[k-a[i][j]];
                }
            }
        }
        dp = move(re);
    }

    int target, ans = 1e9;
    cin>>target;

    for(int i=0; i<=V; ++i) {
        if(dp[i]) {
            ans = min(ans, abs(i-target));
        }
    }
    cout<<ans;
    return 0;
}
/*
https://ac.nowcoder.com/acm/contest/86387/D
经典背包DP
由于不能不选，所以不能继承上一次的状态

*/