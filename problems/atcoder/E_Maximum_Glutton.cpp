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

template<class T>
void chMin(T &a, T b) {
    a=min(a,b);
}
template<class T>
void chMax(T &a, T b) {
    a=max(a,b);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,X,Y;
    cin>>n>>X>>Y;
    const int inf = Y+1;
    vector dp(n+1, vector<int>(X+1, inf));
    dp[0][0] = 0;
    for(int i=0; i<n; ++i) {
        vector re(dp);
        int a,b;
        cin>>a>>b;
        for(int j=1; j<=i+1; ++j) {
            for(int k=a; k<=X; ++k) {
                chMin(re[j][k], dp[j-1][k-a] + b);
            }
        }
        dp = move(re);
    }

    int ans = 0;
    for(int j=n; j>=1; --j) {
        for(int k=0; k<=X; ++k) {
            if(dp[j][k] <= Y) {
                chMax(ans, j);
            }
        }
    }

    cout<<min(n, ans+1);
    return 0;
}
/*
https://atcoder.jp/contests/abc364/tasks/abc364_e
dp[i][j][k]: 前i个选j个，sumA = k, 得到的 sumB 最小值是多少
dp[i][j][k] = min(dp[i-1][j][k], dp[i-1][j-1][k-a[i]]+b[i])
O(n^2 * X)

*/